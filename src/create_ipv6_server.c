#include "../simple_socket.h"


int32_t create_ipv6_server(uint16_t server_port, uint8_t sock_type)
{
	/* create's a new socket file descriptor and binds it to the
	local IPv6 address of the computer */

	int32_t sock;
	struct sockaddr_in6 addr = {0};

	addr.sin6_family = AF_INET;
	addr.sin6_addr = in6addr_any;
	addr.sin6_port = htons(server_port);

	if ((sock = socket(PF_INET, sock_type, IPPROTO_TCP)) < 0)
		return -1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
		return -1;
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return -1;
	return sock;
}