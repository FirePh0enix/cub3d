/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:37:04 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 19:57:36 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"
#include "../cub3d.h"

void	netserv_init(t_server *server, t_vars *vars, int port)
{
	struct sockaddr_in	addr;

	ft_bzero(server, sizeof(t_server));
	addr = (struct sockaddr_in){AF_INET, htons(port), {INADDR_ANY}, {0}};
	server->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
	if (bind(server->socket, (void *) &addr, sizeof(struct sockaddr_in)) == -1)
	{
		ft_printf("Failed to bind address 0.0.0.0 on port %d\n", port);
	}
	server->player_id = vars->map.player->base.id;
}

int	netserv_find_free_client(t_server *server)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (!server->clients[i].present)
			return (i);
		i++;
	}
	return (-1);
}

int	netserv_client_from_entity_id(t_server *serv, int id)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (serv->clients[i].present && serv->clients[i].entity->id == id)
			return (i);
		i++;
	}
	return (-1);
}

void	netserv_disconnect(t_server *server, int i, t_vars *vars)
{
	t_remote_client	*client;

	client = &server->clients[i];
	client->present = 0;
	netserv_broadcast_del(server, client->entity->id, i);
	map_remove_entity(&vars->map, client->entity);
	free(client->entity);
	ft_printf("info : Player `%s` has timed out\n", client->username);
}
