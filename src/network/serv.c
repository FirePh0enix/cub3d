#include "libft.h"
#include "net.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void    netserv_init(t_server *server)
{
    struct sockaddr_in addr;

    addr = (struct sockaddr_in) {AF_INET, htons(SERVER_PORT), {inet_addr("127.0.0.1")}, {0}};
    server->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (bind(server->socket, (void *) &addr, sizeof(struct sockaddr_in)) == -1)
	{
		ft_printf("Failed to bind address 127.0.0.1 on port %d\n", SERVER_PORT);
	}
}

static void connect_client(t_server *server, t_packet_connect *packet, struct sockaddr_in addr)
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
			return;
		}
		i++;
	}
	ft_printf("error: The server is full, cannot connect the client.\n");
}

void	netserv_poll(t_server *server)
{
	char				buf[64];
	struct sockaddr_in addr;
	socklen_t			socklen;
	int					type;

	socklen = sizeof(struct sockaddr_in);
	while (recvfrom(server->socket, buf, 64, 0, (void *) &addr, &socklen) != -1)
	{
		type = *(int *)(buf);
		if (type == PACKET_CONNECT)
			connect_client(server, (void *) buf, addr);
	}
}

void    netserv_destroy(t_server *server)
{
    close(server->socket);
}
