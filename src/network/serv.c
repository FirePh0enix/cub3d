#include "libft.h"
#include "net.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../cub3d.h"

void    netserv_init(t_server *server)
{
    struct sockaddr_in addr;

    addr = (struct sockaddr_in) {AF_INET, htons(SERVER_PORT), {INADDR_ANY}, {0}};
    server->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (bind(server->socket, (void *) &addr, sizeof(struct sockaddr_in)) == -1)
	{
		ft_printf("Failed to bind address 127.0.0.1 on port %d\n", SERVER_PORT);
	}
}

static void connect_client(t_server *server, t_packet_connect *packet, struct sockaddr_in addr, t_vars *vars)
{
	size_t	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (!server->clients[i].present)
		{
			server->clients[i].present = 1;
			ft_memcpy(server->clients[i].username, packet->username, 16);
			server->clients[i].addr = addr;
			ft_printf("info : Client `%s` connected\n", packet->username);

			t_mesh_inst	*mesh = mesh_inst_new(vars, vars->scene, vars->enemy_mesh);
			mesh->base.transform.position = v3(0, 0, 0);
			scene_add_entity(vars->scene, mesh);

			server->clients[i].entity = (void *) mesh;

			// Send response to the client
			t_packet_connect_response	packet;
			packet.type = PACKET_CONNECT_RESPONSE;
			packet.unique_id = i;
			sendto(server->socket, &packet, sizeof(t_packet_connect_response), 0,
				(void *) &server->clients[i].addr, sizeof(struct sockaddr_in));

			return;
		}
		i++;
	}
	ft_printf("error: The server is full, cannot connect the client.\n");
}

static void	move_player(t_server *server, t_packet_pos *pos, t_vars *vars)
{
	t_remote_client	*client;

	(void) vars;
	client = &server->clients[pos->eid];
	client->entity->transform.position = pos->pos;
	client->entity->transform.rotation = pos->rot;
}

void	netserv_poll(t_server *server, t_vars *vars)
{
	char				buf[MAX_PACKET_SIZE];
	struct sockaddr_in addr;
	socklen_t			socklen;
	int					type;

	socklen = sizeof(struct sockaddr_in);
	while (recvfrom(server->socket, buf, MAX_PACKET_SIZE, 0, (void *) &addr, &socklen) != -1)
	{
		type = *(int *)(buf);
		if (type == PACKET_CONNECT)
			connect_client(server, (void *) buf, addr, vars);
		else if (type == PACKET_POS)
			move_player(server, (void *) buf, vars);
	}
}

void    netserv_destroy(t_server *server)
{
    close(server->socket);
}
