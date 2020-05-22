#include "../simple_socket.h"


int32_t accept_connection(int32_t server_sock, struct sockaddr *addr, 
								socklen_t *addr_len)
{
	/* flushes the recvall tmp array to avoid unexpected messages */
	/* accepts a new connection and returns the corresponding socket */

	int32_t sock;

	if (addr == NULL) {
		struct addrinfo addr_lost;
		if ((sock = accept(server_sock, (struct sockaddr *)addr_lost.ai_addr, 
				&addr_lost.ai_addrlen)) < 0)
			return -1;
	}
	else {
		if ((sock = accept(server_sock, (struct sockaddr *)addr, addr_len)) < 0)
			return -1;
	}
	recvall(sock, NULL, 0, NULL, NULL);
	return sock;
}