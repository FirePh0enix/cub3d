/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:36:18 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 19:57:30 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "net.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../cub3d.h"

static void	handle_packet(t_server *server, t_vars *vars, char *buf,
	struct sockaddr_in addr)
{
	int	type;

	type = *(int *)(buf);
	if (type == PACKET_CONNECT)
		netserv_connect_client(server, (void *) buf, addr, vars);
	else if (type == PACKET_POS)
		netserv_move_player(server, (void *) buf, vars);
	else if (type == PACKET_PULSE)
		netserv_handle_pulse(server, (void *) buf);
	else if (type == PACKET_HIT)
		netserv_player_hit(server, (void *) buf, vars);
	else if (type == PACKET_RESPAWN)
		netserv_respawn_player(server, (void *) buf, vars);
	else if (type == PACKET_DOOR_STATE)
		netserv_sync_door_state(server, (void *) buf, vars);
}

void	netserv_poll(t_server *server, t_vars *vars)
{
	char				buf[MAX_PACKET_SIZE];
	struct sockaddr_in	addr;
	socklen_t			socklen;
	int					i;

	socklen = sizeof(struct sockaddr_in);
	while (recvfrom(server->socket, buf, MAX_PACKET_SIZE, 0, (void *) &addr,
			&socklen) != -1)
		handle_packet(server, vars, buf, addr);
	i = 0;
	while (i < MAX_CLIENT)
	{
		if (server->clients[i].present
			&& getms() - server->clients[i].last_pulse >= 500)
			netserv_disconnect(server, i, vars);
		i++;
	}
}

void	netserv_destroy(t_server *server)
{
	close(server->socket);
}

void	netserv_send(t_server *server, void *packet_addr, size_t size, int i)
{
	sendto(server->socket, packet_addr, size, 0,
		(void *) &server->clients[i].addr, sizeof(struct sockaddr_in));
}

void	netserv_broadcast(t_server *server, void *packet_addr, size_t size,
	int mask)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (i != mask)
		{
			sendto(server->socket, packet_addr, size, 0,
				(void *) &server->clients[i].addr, sizeof(struct sockaddr_in));
		}
		i++;
	}
}
