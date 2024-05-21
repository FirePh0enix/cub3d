#include "libft.h"
#include "net.h"
#include <netinet/in.h>
#include <sys/socket.h>

void    netclient_init(t_client *client, char *addr, int port)
{
    struct sockaddr_in addr_in;

	addr_in = (struct sockaddr_in) {AF_INET, htons(CLIENT_PORT), {inet_addr("127.0.0.1")}, {0}};
    client->server_addr = (struct sockaddr_in) {AF_INET, htons(port), {inet_addr("127.0.0.1")}, {0}};
    client->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);

    if (bind(client->socket, (void *) &addr_in, sizeof(struct sockaddr_in)) == -1)
	{
		ft_printf("Failed to bind address %s on port %d\n", addr, SERVER_PORT);
	}
}

void	netclient_connect(t_client *client, char *username)
{
	t_packet_connect	packet;

	packet.type = PACKET_CONNECT;
	ft_memcpy(packet.username, username, ft_strlen(username) + 1);
	sendto(client->socket, &packet, sizeof(t_packet_connect), 0, (void *) &client->server_addr,
		sizeof(struct sockaddr_in));
}
