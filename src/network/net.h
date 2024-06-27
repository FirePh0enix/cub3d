/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:20:00 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/27 22:28:08 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NET_H
# define NET_H

# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>

# include "../scene.h"

# define SERVER_PORT       25566

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
	PACKET_HIT,
	PACKET_DEAD_PLAYER,
	PACKET_RESPAWN,
	PACKET_DENY,
	PACKET_DOOR_STATE
};

typedef struct s_packet_connect
{
	int			type;
	char		username[MAX_CLIENT_NAME + 1];
	uint32_t	hash;
	uint32_t	map_hash;
	t_skin		skin;
}	t_packet_connect;

typedef struct s_packet_connect_response
{
	int	type;
	int	unique_id;
	int	entity_id;
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

# define PACKET_NE_BUFFER_SIZE 48

typedef struct s_packet_new_entity
{
	int				type;
	int				entity_id;
	int				entity_type;
	t_transform		transform;
	t_skin			skin;
	char			buf[PACKET_NE_BUFFER_SIZE - 4];
}	t_packet_new_entity;

typedef struct s_packet_del_entity
{
	int	type;
	int	entity_id;
}	t_packet_del_entity;

typedef struct s_packet_hit
{
	int		type;
	int		source_id;
	int		entity_id;
	int		damage_taken;
}	t_packet_hit;

typedef struct s_packet_dead
{
	int		type;
	int		entity_id;
}	t_packet_dead;

typedef struct s_packet_respawn
{
	int		type;
	int		entity_id;
}	t_packet_respawn;

typedef enum e_reason
{
	REASON_INVALID_HASH,
	REASON_INVALID_MAP,
	REASON_SERVER_FULL
}	t_reason;

char	*reason_str(t_reason reason);

typedef struct s_packet_deny
{
	int			type;
	t_reason	reason;
	char		map[32];
}	t_packet_deny;

typedef struct s_packet_door_state
{
	int		type;
	int		state;
	t_v2i	pos;
}	t_packet_door_state;

typedef struct s_remote_client
{
	int					present;
	struct sockaddr_in	addr;
	char				username[MAX_CLIENT_NAME + 1];
	t_entity			*entity;
	suseconds_t			last_pulse;
}	t_remote_client;

typedef struct s_server
{
	t_remote_client	clients[MAX_CLIENT];
	int				socket;
	int				player_id;
}	t_server;

void	netserv_init(t_server *server, t_vars *vars, int port);
void	netserv_poll(t_server *server, t_vars *vars);
void	netserv_destroy(t_server *server);

int		netserv_client_from_entity_id(t_server *server, int entity_id);

void	netserv_send(t_server *server, void *packet_addr, size_t size, int i);
void	netserv_deny(t_server *server, struct sockaddr_in addr, t_reason reason,
			t_vars *vars);

void	netserv_broadcast(t_server *server, void *packet_addr, size_t size,
			int mask);

void	netserv_broadcast_pos(t_server *server, t_player *player, int mask);
void	netserv_broadcast_del(t_server *server, int entity_id, int mask);
void	netserv_broadcast_dead_player(t_server *server, int id, int mask);
void	netserv_broadcast_respawn(t_server *server, int entity_id, int mask);
void	netserv_broadcast_door_state(t_server *serv, t_v2i pos, int state,
			int mask);

int		netserv_find_free_client(t_server *server);
void	netserv_connect_client(t_server *server, t_packet_connect *conn,
			struct sockaddr_in addr, t_vars *vars);

void	netserv_disconnect(t_server *server, int i, t_vars *vars);

void	netserv_move_player(t_server *server, t_packet_pos *pos, t_vars *vars);
void	netserv_handle_pulse(t_server *server, t_packet_pulse *pulse);
void	netserv_player_hit(t_server *serv, t_packet_hit *hit, t_vars *vars);
void	netserv_respawn_player(t_server *server, t_packet_respawn *p,
			t_vars *vars);
void	netserv_sync_door_state(t_server *server, t_packet_door_state *p,
			t_vars *vars);

typedef struct s_client
{
	int					socket;
	struct sockaddr_in	server_addr;
	int					unique_id;
	int					entity_id;
	suseconds_t			last_pulse;
	bool				has_send_connect;
}	t_client;

void	netclient_init(t_client *client, char *addr, int port);
void	netclient_poll(t_client *client, t_vars *vars);
void	netclient_connect(t_client *client, char *username, t_vars *vars);

void	netclient_send_pos(t_client *client, t_transform transform);
void	netclient_pulse(t_client *client);
void	netclient_send_hit(t_client *client, t_entity *entity, int damage);
void	netclient_send_respawn(t_client *client);
void	netclient_send_door_state(t_client *client, t_v2i pos, int state);

void	netclient_packet_response(t_client *client, t_vars *vars,
			t_packet_connect_response *p);
void	netclient_deny(t_client *client, t_vars *vars,
			t_packet_deny *p);
void	netclient_packet_pos(t_client *client, t_vars *vars,
			t_packet_pos *p);
void	netclient_new_entity(t_client *client, t_vars *vars,
			t_packet_new_entity *p);
void	netclient_del_entity(t_client *client, t_vars *vars,
			t_packet_del_entity *p);
void	netclient_dead(t_client *client, t_vars *vars,
			t_packet_dead *p);
void	netclient_respawn(t_client *client, t_vars *vars,
			t_packet_respawn *p);
void	netclient_hit(t_client *client, t_vars *vars, t_packet_hit *p);
void	netclient_door_state(t_client *client, t_vars *vars,
			t_packet_door_state *p);

#endif
