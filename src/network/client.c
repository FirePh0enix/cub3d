#include "libft.h"
#include "net.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

void    netclient_init(t_client *client, char *addr, int port)
{
    struct sockaddr_in addr_in;

	addr_in = (struct sockaddr_in) {AF_INET, htons(CLIENT_PORT), {INADDR_ANY}, {0}};
    client->server_addr = (struct sockaddr_in) {AF_INET, htons(port), {inet_addr(addr)}, {0}};
    client->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);

    if (bind(client->socket, (void *) &addr_in, sizeof(struct sockaddr_in)) == -1)
	{
		ft_printf("Failed to bind address %s on port %d\n", addr, SERVER_PORT);
	}
}

void	netclient_poll(t_client *client, t_vars *vars)
{
	char				buf[MAX_PACKET_SIZE];
	struct sockaddr_in addr;
	socklen_t			socklen;
	int					type;

	(void) vars;
	socklen = sizeof(struct sockaddr_in);
	while (recvfrom(client->socket, buf, MAX_PACKET_SIZE, 0, (void *) &addr, &socklen) != -1)
	{
		type = *(int *)(buf);
		if (type == PACKET_CONNECT_RESPONSE)
		{
			ft_printf("Response received from the server.\n");
			client->unique_id = ((t_packet_connect_response *) buf)->unique_id;
		}
	}
}

void	netclient_connect(t_client *client, char *username)
{
	t_packet_connect	packet;

	packet.type = PACKET_CONNECT;
	ft_memcpy(packet.username, username, ft_strlen(username) + 1);
	sendto(client->socket, &packet, sizeof(t_packet_connect), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}

void	netclient_pulse(t_client *client)
{
	t_packet_pulse	packet;

	packet.type = PACKET_PULSE;
	packet.unique_id = client->unique_id;
	sendto(client->socket, &packet, sizeof(t_packet_pulse), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}

void	netclient_send_pos(t_client *client, t_transform transform)
{
	t_packet_pos	packet;

	packet.type = PACKET_POS;
	packet.pos = transform.position;
	packet.rot = transform.rotation;
	packet.eid = client->unique_id;
	sendto(client->socket, &packet, sizeof(t_packet_pos), 0,
		(void *) &client->server_addr, sizeof(struct sockaddr_in));
}
