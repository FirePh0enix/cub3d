/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_connect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:15:37 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/29 20:17:53 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"
#include "../cub3d.h"

static void	send_all_players(t_server *server, int i)
{
	t_packet_new_entity		new_ent;
	int						i2;

	new_ent.type = PACKET_NEW_ENTITY;
	new_ent.entity_type = ENTITY_FAKE_PLAYER;
	new_ent.entity_id = server->player_id;
	new_ent.skin = SKIN_MARINE;
	new_ent.transform = (t_transform){v3(0, 0, 0), v3(0, 0, 0)};
	netserv_send(server, &new_ent, sizeof(t_packet_new_entity), i);
	new_ent.entity_id = server->clients[i].entity->id;
	netserv_broadcast(server, &new_ent, sizeof(t_packet_new_entity), i);
	i2 = -1;
	while (++i2 < MAX_CLIENT)
	{
		if (!server->clients[i2].present || i2 == i)
			continue ;
		new_ent.type = PACKET_NEW_ENTITY;
		new_ent.entity_type = ENTITY_FAKE_PLAYER;
		new_ent.entity_id = server->clients[i2].entity->id;
		new_ent.transform = (t_transform){v3(0, 0, 0), v3(0, 0, 0)};
		new_ent.skin = SKIN_MARINE;
		netserv_send(server, &new_ent, sizeof(t_packet_new_entity), i);
	}
}

static void	handle_connection(t_server *server, t_packet_connect *conn,
	struct sockaddr_in addr, t_vars *vars)
{
	const int					i = netserv_find_free_client(server);
	t_fake_player				*fp;
	t_packet_connect_response	packet;

	server->clients[i].present = 1;
	ft_memcpy(server->clients[i].username, conn->username, 16);
	server->clients[i].addr = addr;
	server->clients[i].last_pulse = getms();
	ft_printf("info : Client `%s` connected\n", conn->username);
	fp = fake_player_new(vars, &vars->map, next_entity_id(vars), conn->skin);
	fp->base.transform.position = v3(0, 0, 0);
	map_add_entity(&vars->map, fp);
	server->clients[i].entity = (void *) fp;
	packet.type = PACKET_CONNECT_RESPONSE;
	packet.unique_id = i;
	packet.entity_id = server->clients[i].entity->id;
	sendto(server->socket, &packet, sizeof(t_packet_connect_response), 0,
		(void *) &server->clients[i].addr, sizeof(struct sockaddr_in));
}

void	netserv_connect_client(t_server *server, t_packet_connect *conn,
	struct sockaddr_in addr, t_vars *vars)
{
	const int	i = netserv_find_free_client(server);

	if (i == -1)
	{
		netserv_deny(server, addr, REASON_SERVER_FULL, vars);
		return ;
	}
	if (conn->map_hash != vars->map.hash)
	{
		netserv_deny(server, addr, REASON_INVALID_MAP, vars);
		return ;
	}
	handle_connection(server, conn, addr, vars);
	send_all_players(server, i);
}
