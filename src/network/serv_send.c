/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:25:15 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/29 14:26:39 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"

void	netserv_broadcast_pos(t_server *server, t_player *player, int mask)
{
	t_packet_pos	pos;

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
