#include "libft.h"
#include "net.h"
#include "../cub3d.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

void    netclient_init(t_client *client, char *addr, int port)
{
    client->server_addr = (struct sockaddr_in) {AF_INET, htons(port), {inet_addr(addr)}, {0}};
    client->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
	client->unique_id = -1;
	client->last_pulse = getms();
}

static t_entity	*new_entity(t_packet_new_entity *p, t_vars *vars)
{
	t_entity	*entity;

	entity = NULL;
	if (p->entity_type == ENTITY_FAKE_PLAYER)
		entity = (void *) fake_player_new(vars, &vars->map, p->entity_id, &vars->at);
	return (entity);
}

void	netclient_poll(t_client *client, t_vars *vars)
{
	char				buf[MAX_PACKET_SIZE];
	struct sockaddr_in addr;
	socklen_t			socklen;
	int					type;

	(void) vars;
	socklen = sizeof(struct sockaddr_in);
	while (recvfrom(client->socket, buf, MAX_PACKET_SIZE, 0, (void *) &addr, &socklen) != -1)
	{
		type = *(int *)(buf);
		if (type == PACKET_CONNECT_RESPONSE)
		{
			ft_printf("info : response received from the server!\n");
			client->unique_id = ((t_packet_connect_response *) buf)->unique_id;
			client->entity_id = ((t_packet_connect_response *) buf)->entity_id;
			vars->map.player->base.id = client->entity_id;
			client->last_pulse = getms();
			vars->menu_open = false;
		}
		else if (type == PACKET_DENY)
		{
			t_packet_deny *deny = (void *) buf;
			if (deny->reason != REASON_INVALID_MAP)
				ft_printf("error: Connection denied: %s\n", reason_str(deny->reason));
			else
				ft_printf("error: Connection denied: Invalid map, `%s` was expected but `%s` was loaded\n",
					deny->map, vars->map.name);
		}
		else if (type == PACKET_POS)
		{
			t_packet_pos *packet = (void *)buf;
			t_entity *entity = map_get_entity_by_id(&vars->map, packet->eid);
			if (entity != NULL)
			{
				entity->transform.position = packet->pos;
				entity->transform.rotation = packet->rot;
			}
		}
		else if (type == PACKET_NEW_ENTITY)
		{
			t_entity *entity = new_entity((void *) buf, vars);
			map_add_entity(&vars->map, entity);
		}
		else if (type == PACKET_DEL_ENTITY)
		{
			t_packet_del_entity	*packet = (void *)buf;
			t_entity *entity = map_get_entity_by_id(&vars->map, packet->entity_id);
			if (entity == NULL)
				continue ;
			map_remove_entity(&vars->map, entity);
		} else if (type == PACKET_PULSE)
		{
			client->last_pulse = getms();
		}
		else if (type == PACKET_SYNC_SCOREBOARD)
		{
			t_packet_sync_score *p = (void *) buf;
			vars->scoreboard.entries[p->index].kills = p->kills;
			vars->scoreboard.entries[p->index].death = p->death;
			vars->scoreboard.entries[p->index].present = p->present;
			ft_memcpy(vars->scoreboard.entries[p->index].username, p->username, 16);
		}
		else if (type == PACKET_DEAD_PLAYER)
		{
			t_packet_dead	*packet = (void *)buf;
			t_entity *entity = map_get_entity_by_id(&vars->map, packet->entity_id);
			if (entity == NULL)
				continue ;
			entity->is_dead = true;
			if (entity->type == ENTITY_PLAYER)
			{
				vars->menu_open = true;
				vars->menu.state = STATE_DEAD;
			}
		} else if (type == PACKET_RESPAWN)
		{
			t_packet_respawn *p = (void *) buf;
			t_entity *entity = map_get_entity_by_id(&vars->map, p->entity_id);
			if (entity == NULL)
				continue ;
			entity->is_dead = false;

			if (entity->type == ENTITY_PLAYER)
				((t_player *) entity)->health = MAX_HEALTH;
			else if (entity->type == ENTITY_FAKE_PLAYER)
				((t_fake_player *) entity)->health = MAX_HEALTH;
		} else if (type == PACKET_HIT)
		{
			t_packet_hit	*p = (void *) buf;
			t_entity *entity = map_get_entity_by_id(&vars->map, p->source_id);
			if (!entity || entity->type != ENTITY_FAKE_PLAYER)
				continue ;
			fp_reset_shoot_anim((t_fake_player *) entity);
			((t_fake_player *) entity)->is_shooting = true;
		}
	}

	if (getms() - client->last_pulse >= 500)
	{
		vars->menu_open = true;
		vars->menu.state = STATE_MAIN;
		// TODO: Reset the scene
	}
}

void	netclient_connect(t_client *client, char *username, t_vars *vars)
{
	t_packet_connect	packet;

	packet.type = PACKET_CONNECT;
	packet.hash = vars->exec_hash;
	packet.map_hash = vars->map.hash;
	ft_memset(packet.username, 0, MAX_CLIENT_NAME + 1);
	ft_memcpy(packet.username, username, ft_strlen(username) + 1);
	sendto(client->socket, &packet, sizeof(t_packet_connect), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
	client->has_send_connect = true;
}

void	netclient_pulse(t_client *client)
{
	t_packet_pulse	packet;

	if (client->unique_id == -1)
		return ;
	packet.type = PACKET_PULSE;
	packet.unique_id = client->unique_id;
	sendto(client->socket, &packet, sizeof(t_packet_pulse), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}

void	netclient_send_pos(t_client *client, t_transform transform)
{
	t_packet_pos	packet;

	if (client->unique_id == -1)
		return ;
	// FIXME: Uninitialized bytes when calling `sendto`
	packet.type = PACKET_POS;
	packet.pos = transform.position;
	packet.rot = transform.rotation;
	packet.eid = client->unique_id;
	sendto(client->socket, &packet, sizeof(t_packet_pos), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}

void	netclient_send_hit(t_client *client, t_entity *entity, int damage_taken)
{
	t_packet_hit	packet;

	if (client->unique_id == -1)
		return ;
	packet.type = PACKET_HIT;
	packet.source_id = client->entity_id;
	if (entity)
		packet.entity_id = entity->id;
	else
		packet.entity_id = -1;
	packet.damage_taken = damage_taken;
	sendto(client->socket, &packet, sizeof(t_packet_hit), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}

void	netclient_send_respawn(t_client *client)
{
	t_packet_respawn	packet;

	if (client->unique_id == -1)
		return ;
	packet.type = PACKET_RESPAWN;
	packet.entity_id = client->entity_id;
	sendto(client->socket, &packet, sizeof(t_packet_hit), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}
