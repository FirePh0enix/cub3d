#include "libft.h"
#include "mlx.h"
#include "net.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../cub3d.h"

void    netserv_init(t_server *server, t_vars *vars, int port)
{
    struct sockaddr_in addr;

	ft_bzero(server, sizeof(t_server));
    addr = (struct sockaddr_in) {AF_INET, htons(port), {INADDR_ANY}, {0}};
    server->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (bind(server->socket, (void *) &addr, sizeof(struct sockaddr_in)) == -1)
	{
		ft_printf("Failed to bind address 0.0.0.0 on port %d\n", port);
	}
	server->player_id = vars->map.player->base.id;
}

static int	find_free_client(t_server *server)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (!server->clients[i].present)
			return (i);
		i++;
	}
	return (-1);
}

static void connect_client(t_server *server, t_packet_connect *conn, struct sockaddr_in addr, t_vars *vars)
{
	int	i = find_free_client(server);

	if (i == -1)
	{
		netserv_deny(server, addr, REASON_SERVER_FULL, vars);
		return ;
	}

	// if (conn->hash != vars->exec_hash)
	// {
	// 	netserv_deny(server, addr, REASON_INVALID_HASH, vars);
	// 	return ;
	// }

	if (conn->map_hash != vars->map.hash)
	{
		netserv_deny(server, addr, REASON_INVALID_MAP, vars);
		return ;
	}

	server->clients[i].present = 1;
	ft_memcpy(server->clients[i].username, conn->username, 16);
	server->clients[i].addr = addr;
	server->clients[i].last_pulse = getms();
	ft_printf("info : Client `%s` connected\n", conn->username);

	t_fake_player	*fake_player = fake_player_new(vars, &vars->map, next_entity_id(vars), conn->skin);
	fake_player->base.transform.position = v3(0, 0, 0);
	map_add_entity(&vars->map, fake_player);

	server->clients[i].entity = (void *) fake_player;

	vars->scoreboard.entries[i + 1].present = 1;
	vars->scoreboard.entries[i + 1].kills = 0;
	vars->scoreboard.entries[i + 1].death = 0;
	ft_memcpy(vars->scoreboard.entries[i + 1].username, conn->username, 16);

	// Send response to the client
	t_packet_connect_response	packet;
	packet.type = PACKET_CONNECT_RESPONSE;
	packet.unique_id = i;
	packet.entity_id = server->clients[i].entity->id;
	sendto(server->socket, &packet, sizeof(t_packet_connect_response), 0,
		(void *) &server->clients[i].addr, sizeof(struct sockaddr_in));

	// Add the server entity.
	t_packet_new_entity		new_ent;
	new_ent.type = PACKET_NEW_ENTITY;
	new_ent.entity_type = ENTITY_FAKE_PLAYER;
	new_ent.entity_id = server->player_id;
	new_ent.skin = SKIN_GUNNER;
	new_ent.transform = (t_transform){v3(0, 0, 0), v3(0, 0, 0)};
	netserv_send(server, &new_ent, sizeof(t_packet_new_entity), i);

	new_ent.entity_id = server->clients[i].entity->id;
	netserv_broadcast(server, &new_ent, sizeof(t_packet_new_entity), i);

	int	i2 = 0;
	while (i2 < MAX_CLIENT)
	{
		if (!server->clients[i2].present || i2 == i)
		{
			i2++;
			continue ;
		}
		// printf("new entity\n");
		new_ent.type = PACKET_NEW_ENTITY;
		new_ent.entity_type = ENTITY_FAKE_PLAYER;
		new_ent.entity_id = server->clients[i2].entity->id;
		new_ent.transform = (t_transform){v3(0, 0, 0), v3(0, 0, 0)};
		new_ent.skin = SKIN_GUNNER;
		netserv_send(server, &new_ent, sizeof(t_packet_new_entity), i);
		i2++;
	}
}

static void	move_player(t_server *server, t_packet_pos *pos, t_vars *vars)
{
	t_remote_client	*client;
	int	i;

	(void) vars;
	if (pos->eid < 0 || pos->eid >= 8 || !server->clients[pos->eid].present)
	{
		ft_printf("Error\nInvalid packet received from client.\n");
		return ;
	}
	i = pos->eid;
	client = &server->clients[pos->eid];
	client->entity->transform.position = pos->pos;
	client->entity->transform.rotation = pos->rot;

	pos->eid = client->entity->id;
	netserv_broadcast(server, pos, sizeof(t_packet_pos), i);
}

static void	handle_pulse(t_server *server, t_packet_pulse *pulse)
{
	t_remote_client	*client;

	if (pulse->unique_id < 0 || pulse->unique_id >= MAX_CLIENT || !server->clients[pulse->unique_id].present)
		return ;
	client = &server->clients[pulse->unique_id];
	client->last_pulse = getms();
	netserv_send(server, pulse, sizeof(t_packet_pulse), pulse->unique_id);
}

static void	player_hit(t_server *server, t_packet_hit *hit, t_vars *vars)
{
	t_entity		*entity;
	t_fake_player	*fake_player;
	int				client_id;

	(void)server;
	client_id = netserv_client_from_entity_id(server, hit->source_id);
	entity = map_get_entity_by_id(&vars->map, hit->entity_id);

	if (entity && entity->type == ENTITY_FAKE_PLAYER)
	{
		fake_player = (t_fake_player *) entity;
		fake_player->health -= hit->damage_taken;
	}
	else if (entity && entity->type == ENTITY_PLAYER)
	{
		((t_player *) entity)->health -= hit->damage_taken;
	}

	if (server->clients[client_id].present)
	{
		fp_reset_shoot_anim((t_fake_player *) server->clients[client_id].entity);
		((t_fake_player *) server->clients[client_id].entity)->is_shooting = true;
	}

	netserv_broadcast(server, hit, sizeof(t_packet_hit), client_id);
}

static void	disconnect(t_server *server, int i, t_vars *vars)
{
	t_remote_client	*client;

	client = &server->clients[i];
	client->present = 0;
	netserv_broadcast_del(server, client->entity->id, i);
	map_remove_entity(&vars->map, client->entity);
	vars->scoreboard.entries[i + 1].present = 0;
	free(client->entity);
	ft_printf("info : Player `%s` has timed out\n", client->username);
}

static void	respawn_player(t_server *server, t_packet_respawn *p, t_vars *vars)
{
	int			i;
	t_entity	*entity;

	(void) vars;
	i = netserv_client_from_entity_id(server, p->entity_id);
	if (i == -1)
		return ;
	entity = map_get_entity_by_id(&vars->map, p->entity_id);
	if (!entity || entity->type != ENTITY_FAKE_PLAYER)
		return ;
	((t_fake_player *) entity)->health = MAX_HEALTH;
	((t_fake_player *) entity)->base.is_dead = false;
	netserv_broadcast(server, p, sizeof(t_packet_respawn), i);
}

static void	sync_door_state(t_server *server, t_packet_door_state *p, t_vars *vars)
{
	(void) server;
	if (p->pos.x < 0 || p->pos.x >= vars->map.width || p->pos.y < 0 || p->pos.y >= vars->map.height)
		return ;
	if (p->state)
		vars->map.tiles[p->pos.x + p->pos.y * vars->map.width] = TILE_DOOR;
	else
		vars->map.tiles[p->pos.x + p->pos.y * vars->map.width] = TILE_DOOR_OPEN;
	netserv_broadcast_door_state(server, p->pos, p->state, -1);
}

void	netserv_poll(t_server *server, t_vars *vars)
{
	char				buf[MAX_PACKET_SIZE];
	struct sockaddr_in addr;
	socklen_t			socklen;
	int					type;

	socklen = sizeof(struct sockaddr_in);
	while (recvfrom(server->socket, buf, MAX_PACKET_SIZE, 0, (void *) &addr, &socklen) != -1)
	{
		type = *(int *)(buf);
		if (type == PACKET_CONNECT)
			connect_client(server, (void *) buf, addr, vars);
		else if (type == PACKET_POS)
			move_player(server, (void *) buf, vars);
		else if (type == PACKET_PULSE)
			handle_pulse(server, (void *) buf);
		else if (type == PACKET_HIT)
			player_hit(server, (void *) buf, vars);
		else if (type == PACKET_RESPAWN)
			respawn_player(server, (void *) buf, vars);
		else if (type == PACKET_DOOR_STATE)
			sync_door_state(server, (void *) buf, vars);
	}
	int	i = 0;
	while (i < MAX_CLIENT)
	{
		if (server->clients[i].present && getms() - server->clients[i].last_pulse >= 500)
			disconnect(server, i, vars);
		i++;
	}
}

int		netserv_client_from_entity_id(t_server *server, int entity_id)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (server->clients[i].present && server->clients[i].entity->id == entity_id)
			return (i);
		i++;
	}
	return (-1);
}

void    netserv_destroy(t_server *server)
{
    close(server->socket);
}

void	netserv_send(t_server *server, void *packet_addr, size_t size, int i)
{
	sendto(server->socket, packet_addr, size, 0,
		(void *) &server->clients[i].addr, sizeof(struct sockaddr_in));
}

void	netserv_broadcast(t_server *server, void *packet_addr, size_t size, int mask)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (i != mask)
		{
			sendto(server->socket, packet_addr, size, 0,
				(void *) &server->clients[i].addr, sizeof(struct sockaddr_in));
		}
		i++;
	}
}
