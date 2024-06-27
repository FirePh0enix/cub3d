/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:25:15 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 19:14:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"
#include "../cub3d.h"

void	netserv_broadcast_pos(t_server *server, t_player *player, int mask)
{
	t_packet_pos	pos;

	ft_bzero(&pos, sizeof(t_packet_pos));
	pos.type = PACKET_POS;
	pos.eid = server->player_id;
	pos.pos = player->base.transform.position;
	pos.rot = player->base.transform.rotation;
	netserv_broadcast(server, &pos, sizeof(t_packet_pos), mask);
}

void	netserv_broadcast_del(t_server *server, int entity_id, int mask)
{
	t_packet_del_entity	del_entity;

	del_entity.type = PACKET_DEL_ENTITY;
	del_entity.entity_id = entity_id;
	netserv_broadcast(server, &del_entity, sizeof(t_packet_del_entity), mask);
}

void	netserv_broadcast_dead_player(t_server *server, int entity_id, int mask)
{
	t_packet_dead	dead_player;

	dead_player.type = PACKET_DEAD_PLAYER;
	dead_player.entity_id = entity_id;
	netserv_broadcast(server, &dead_player, sizeof(t_packet_dead), mask);
}

void	netserv_broadcast_respawn(t_server *server, int entity_id, int mask)
{
	t_packet_respawn	p;

	p.type = PACKET_RESPAWN;
	p.entity_id = entity_id;
	netserv_broadcast(server, &p, sizeof(t_packet_respawn), mask);
}

void	netserv_deny(t_server *server, struct sockaddr_in addr, t_reason reason,
	t_vars *vars)
{
	t_packet_deny	deny;
	size_t			size;

	deny.type = PACKET_DENY;
	deny.reason = reason;
	ft_bzero(deny.map, 32);
	size = ft_strlen(vars->map.name);
	if (size >= 32)
		size = 31;
	ft_memcpy(deny.map, vars->map.name, ft_strlen(vars->map.name) + 1);
	sendto(server->socket, &deny, sizeof(t_packet_deny), 0, (void *) &addr,
		sizeof(struct sockaddr_in));
}
