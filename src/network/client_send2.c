/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:11:48 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 19:12:12 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"

void	netclient_send_door_state(t_client *client, t_v2i pos, int state)
{
	t_packet_door_state	p;

	if (client->unique_id == -1)
		return ;
	p.type = PACKET_DOOR_STATE;
	p.pos = pos;
	p.state = state;
	sendto(client->socket, &p, sizeof(t_packet_hit), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}
