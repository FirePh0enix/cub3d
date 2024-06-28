/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:13:25 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/28 11:14:35 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "net.h"
#include "../cub3d.h"
#include <netinet/in.h>
#include <sys/socket.h>

void	netclient_init(t_client *client, char *addr, int port)
{
	ft_bzero(client, sizeof(t_client));
	client->server_addr = (struct sockaddr_in){AF_INET, htons(port),
	{inet_addr(addr)}, {0}};
	client->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
	client->unique_id = -1;
	client->has_send_connect = false;
	client->entity_id = -1;
	client->last_pulse = getms();
}

static void	handle_packets(t_client *client, t_vars *vars, char *buf)
{
	int	type;

	type = *(int *)(buf);
	if (type == PACKET_CONNECT_RESPONSE)
		netclient_packet_response(client, vars, (void *) buf);
	else if (type == PACKET_DENY)
		netclient_deny(client, vars, (void *) buf);
	else if (type == PACKET_POS)
		netclient_packet_pos(client, vars, (void *) buf);
	else if (type == PACKET_NEW_ENTITY)
		netclient_new_entity(client, vars, (void *) buf);
	else if (type == PACKET_DEL_ENTITY)
		netclient_del_entity(client, vars, (void *) buf);
	else if (type == PACKET_PULSE)
		client->last_pulse = getms();
	else if (type == PACKET_DEAD_PLAYER)
		netclient_dead(client, vars, (void *) buf);
	else if (type == PACKET_RESPAWN)
		netclient_respawn(client, vars, (void *) buf);
	else if (type == PACKET_HIT)
		netclient_hit(client, vars, (void *) buf);
	else if (type == PACKET_DOOR_STATE)
		netclient_door_state(client, vars, (void *) buf);
}

void	netclient_poll(t_client *client, t_vars *vars)
{
	char				buf[MAX_PACKET_SIZE];
	struct sockaddr_in	addr;
	socklen_t			socklen;

	(void) vars;
	socklen = sizeof(struct sockaddr_in);
	while (recvfrom(client->socket, buf, MAX_PACKET_SIZE, 0, (void *) &addr,
			&socklen) != -1)
		handle_packets(client, vars, buf);
	if (getms() - client->last_pulse >= 500)
	{
		vars->menu_open = true;
		vars->menu.state = STATE_MAIN;
	}
}
