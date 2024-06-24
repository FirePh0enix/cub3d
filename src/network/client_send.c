/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:49:31 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/24 22:53:57 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "net.h"
#include "../cub3d.h"
#include <sys/socket.h>

void	netserv_deny(t_server *server, struct sockaddr_in addr, t_reason reason, t_vars *vars)
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
	sendto(server->socket, &deny, sizeof(t_packet_deny), 0, (void *) &addr, sizeof(struct sockaddr_in));
}
