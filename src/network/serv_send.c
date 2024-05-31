/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:25:15 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/31 11:53:57 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"
#include "../cub3d.h"

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

void	netserv_broadcast_scoreboard(t_server *server, t_scoreboard *scoreboard)
{
	t_packet_sync_score	p;
	int					i;

	p.type = PACKET_SYNC_SCOREBOARD;
	p.index = 0;
	p.present = 1;
	p.kills = scoreboard->entries[0].kills;
	p.death = scoreboard->entries[0].death;
	netserv_broadcast(server, &p, sizeof(t_packet_sync_score), -1);
	i = 0;
	while (i < MAX_CLIENT + 1)
	{
		p.index = i;
		p.present = scoreboard->entries[i].present;
		p.kills = scoreboard->entries[i].kills;
		p.death = scoreboard->entries[i].death;
		netserv_broadcast(server, &p, sizeof(t_packet_sync_score), -1);
		i++;
	}
}
