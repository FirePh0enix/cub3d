/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:49:31 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 17:36:03 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "net.h"
#include "../cub3d.h"
#include <sys/socket.h>

void	netclient_connect(t_client *client, char *username, t_vars *vars)
{
	t_packet_connect	packet;

	ft_bzero(&packet, sizeof(t_packet_connect));
	packet.type = PACKET_CONNECT;
	packet.hash = vars->exec_hash;
	packet.map_hash = vars->map.hash;
	packet.skin = SKIN_MARINE;
	ft_memcpy(packet.username, username, ft_strlen(username));
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
