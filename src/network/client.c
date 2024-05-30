#include "libft.h"
#include "mlx.h"
#include "net.h"
#include "../cub3d.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

void    netclient_init(t_client *client, char *addr, int port)
{
    struct sockaddr_in addr_in;

	addr_in = (struct sockaddr_in) {AF_INET, htons(CLIENT_PORT), {INADDR_ANY}, {0}};
    client->server_addr = (struct sockaddr_in) {AF_INET, htons(port), {inet_addr(addr)}, {0}};
    client->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
	client->unique_id = -1;

    if (bind(client->socket, (void *) &addr_in, sizeof(struct sockaddr_in)) == -1)
	{
		ft_printf("Failed to bind on port %d\n", addr, CLIENT_PORT);
	}
}

static t_entity	*new_entity(t_packet_new_entity *p, t_vars *vars)
{
	t_entity	*entity;

	entity = NULL;
	if (p->entity_type == ENTITY_MESH)
		entity = (void *) mesh_inst_new(vars, vars->scene, mesh_load_from_obj(vars, p->buf), p->entity_id);
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
			ft_printf("Response received from the server.\n");
			client->unique_id = ((t_packet_connect_response *) buf)->unique_id;
			client->last_pulse = getms();
		}
		else if (type == PACKET_POS)
		{
			t_packet_pos *packet = (void *)buf;
			t_entity *entity = scene_get_entity_by_id(vars->scene, packet->eid);
			if (entity != NULL)
			{
				entity->transform.position = packet->pos;
				entity->transform.rotation = packet->rot;
			}
		}
		else if (type == PACKET_NEW_ENTITY)
		{
			t_entity *entity = new_entity((void *) buf, vars);
			scene_add_entity(vars->scene, entity);
		}
		else if (type == PACKET_DEL_ENTITY)
		{
			t_packet_del_entity	*packet = (void *)buf;
			t_entity *entity = scene_get_entity_by_id(vars->scene, packet->entity_id);
			if (entity == NULL)
				continue ;
			scene_remove_entity(vars->scene, entity);
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
	}

	if (getms() - client->last_pulse >= 500)
		mlx_loop_end(vars->mlx);
}

void	netclient_connect(t_client *client, char *username)
{
	t_packet_connect	packet;

	packet.type = PACKET_CONNECT;
	ft_memcpy(packet.username, username, ft_strlen(username) + 1);
	sendto(client->socket, &packet, sizeof(t_packet_connect), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
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
	packet.type = PACKET_POS;
	packet.pos = transform.position;
	packet.rot = transform.rotation;
	packet.eid = client->unique_id;
	sendto(client->socket, &packet, sizeof(t_packet_pos), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}
