/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:20:00 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/21 15:47:06 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NET_H
# define NET_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>

# include "../math/vec.h"

# define SERVER_PORT 12345
# define CLIENT_PORT 23456

# define MAX_CLIENT 8
# define MAX_CLIENT_NAME 16

enum e_packet_type
{
	PACKET_CONNECT,
	PACKET_PULSE,
	PACKET_POS
};

typedef struct s_packet_connect
{
	int		type;
	char	username[MAX_CLIENT_NAME];
}	t_packet_connect;

typedef struct s_packet_pulse
{
	int	type;
}	t_packet_pulse;

/*
	s2c : Indicate to a client the new position of an entity.
	c2s : Indicate the client's player has moved.
 */
typedef struct s_packet_pos
{
	int		type;
	t_v3	pos;
	t_v3	rot;
	int		eid;
}	t_packet_pos;

typedef struct s_remote_client
{
	int					present;
	struct sockaddr_in	addr;
	char				username[MAX_CLIENT_NAME];
}	t_remote_client;

typedef struct s_server
{
	t_remote_client clients[MAX_CLIENT];
    int				socket;
}   t_server;

void    netserv_init(t_server *server);
void	netserv_poll(t_server *server);
void    netserv_destroy(t_server *server);

typedef struct s_client
{
    int					socket;
    struct sockaddr_in	server_addr;
}   t_client;

void    netclient_init(t_client *client, char *addr, int port);
void	netclient_connect(t_client *client, char *username);

#endif
