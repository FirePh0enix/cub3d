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
	server->player_id = vars->scene->player->base.id;
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

static void connect_client(t_server *server, t_packet_connect *conn, struct sockaddr_in addr, t_vars *vars, t_alloc_table *at)
{
	int	i = find_free_client(server);

	if (i == -1)
	{
		ft_printf("Error\nThe server is full, cannot connect the client.\n");
		return ;
	}

	server->clients[i].present = 1;
	ft_memcpy(server->clients[i].username, conn->username, 16);
	server->clients[i].addr = addr;
	server->clients[i].last_pulse = getms();
	ft_printf("info : Client `%s` connected\n", conn->username);

	t_fake_player	*fake_player = fake_player_new(vars, vars->scene, next_entity_id(vars), at);
	fake_player->base.transform.position = v3(0, 0, 0);
	scene_add_entity(vars->scene, fake_player);

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

	(void)server;
	entity = scene_get_entity_by_id(vars->scene, hit->entity_id);
	printf("ENTITY ID: %d\n", hit->entity_id);
	if (!entity)
	{
		printf("NO ENTITY %p\n", entity);
		return ;
	}
	if (entity->type == ENTITY_FAKE_PLAYER)
	{
		fake_player = (t_fake_player *) entity;
		fake_player->health -= hit->damage_taken;
	}
	else if (entity->type == ENTITY_PLAYER)
	{
		((t_player *) entity)->health -= hit->damage_taken;
	}
}

static void	disconnect(t_server *server, int i, t_vars *vars)
{
	t_remote_client	*client;

	client = &server->clients[i];
	client->present = 0;
	netserv_broadcast_del(server, client->entity->id, i);
	scene_remove_entity(vars->scene, client->entity);
	vars->scoreboard.entries[i + 1].present = 0;
	free(client->entity);
	ft_printf("Player %s has timed out\n", client->username);
}

void	netserv_poll(t_server *server, t_vars *vars, t_alloc_table *at)
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
			connect_client(server, (void *) buf, addr, vars, at);
		else if (type == PACKET_POS)
			move_player(server, (void *) buf, vars);
		else if (type == PACKET_PULSE)
			handle_pulse(server, (void *) buf);
		else if (type == PACKET_HIT)
			player_hit(server, (void *) buf, vars);
	}
	int	i = 0;
	while (i < MAX_CLIENT)
	{
		if (server->clients[i].present && getms() - server->clients[i].last_pulse >= 500)
			disconnect(server, i, vars);
		i++;
	}
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
