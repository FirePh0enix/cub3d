/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_send2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:10 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 19:14:24 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"

void	netserv_broadcast_door_state(t_server *server, t_v2i pos, int state,
	int mask)
{
	t_packet_door_state	p;

	p.type = PACKET_DOOR_STATE;
	p.state = state;
	p.pos = pos;
	netserv_broadcast(server, &p, sizeof(t_packet_door_state), mask);
}
