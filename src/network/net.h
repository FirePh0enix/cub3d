/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:20:00 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/30 14:31:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NET_H
# define NET_H

#include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>

# include "../math/vec.h"
# include "../scene.h"

# define SERVER_PORT       25566
# define SERVER_LOCAL_PORT 25577
# define CLIENT_PORT       25566

# define MAX_CLIENT 8
# define MAX_CLIENT_NAME 16

# define MAX_PACKET_SIZE 96

typedef struct s_vars	t_vars;

enum e_packet_type
{
	PACKET_CONNECT,
	PACKET_CONNECT_RESPONSE,
	PACKET_PULSE,
	PACKET_POS,
	PACKET_NEW_ENTITY,
	PACKET_DEL_ENTITY,
	PACKET_SYNC_SCOREBOARD,
};

typedef struct s_packet_connect
{
	int		type;
	char	username[MAX_CLIENT_NAME];
}	t_packet_connect;

typedef struct s_packet_connect_response
{
	int	type;
	int	unique_id;
}	t_packet_connect_response;

typedef struct s_packet_pulse
{
	int	type;
	int	unique_id;
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

#define PACKET_NE_BUFFER_SIZE 48

typedef struct s_packet_new_entity
{
	int				type;
	int				entity_id;
	int				entity_type;
	t_transform		transform;
	char			buf[PACKET_NE_BUFFER_SIZE];
}	t_packet_new_entity;

typedef struct s_packet_del_entity
{
	int	type;
	int	entity_id;
}	t_packet_del_entity;

/*
	Send by the server to the client to update the scoreboard.
 */
typedef struct s_packet_sync_score
{
	int	type;
	int	index;
	int	present;
	int	kills;
	int	death;
}	t_packet_sync_score;

typedef struct s_remote_client
{
	int					present;
	struct sockaddr_in	addr;
	char				username[MAX_CLIENT_NAME];
	t_entity			*entity;
	suseconds_t			last_pulse;
}	t_remote_client;

typedef struct s_server
{
	t_remote_client clients[MAX_CLIENT];
    int				socket;
	int				player_id;
}   t_server;

void    netserv_init(t_server *server, t_vars *vars, int port);
void	netserv_poll(t_server *server, t_vars *vars);
void    netserv_destroy(t_server *server);

void	netserv_send(t_server *server, void *packet_addr, size_t size, int i);
void	netserv_broadcast(t_server *server, void *packet_addr, size_t size, int mask);

void	netserv_broadcast_pos(t_server *server, t_player *player, int mask);
void	netserv_broadcast_del(t_server *server, int entity_id, int mask);

typedef struct s_scoreboard	t_scoreboard;

void	netserv_broadcast_scoreboard(t_server *server, t_scoreboard *scoreboard);

typedef struct s_client
{
    int					socket;
    struct sockaddr_in	server_addr;
	int					unique_id;
	suseconds_t			last_pulse;
}   t_client;

void    netclient_init(t_client *client, char *addr, int port);
void	netclient_poll(t_client *client, t_vars *vars);
void	netclient_connect(t_client *client, char *username);
void	netclient_send_pos(t_client *client, t_transform transform);

void	netclient_pulse(t_client *client);

#endif
