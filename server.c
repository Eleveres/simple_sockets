#include "simple_socket.h"
#include <strings.h>


#define HEADER_LENGTH 8

int main(void) {
	uint8_t buffer[50] = {0};
	struct sockaddr_in addr;
	socklen_t addr_len;
	
	int8_t serv_sock = create_ipv4_server(8000, TCP);
	listen(serv_sock, BACKLOG);

	while (true) {
		int8_t client_sock = accept_connection(serv_sock, (struct sockaddr *)&addr, &addr_len);
		recvall(client_sock, buffer, 3, NULL, NULL);
		printf("%s\n", buffer);
		char str[INET_ADDRSTRLEN] = {0};
		inet_ntop(AF_INET, &addr.sin_addr, str, INET_ADDRSTRLEN);
		printf("%s\n", str);
		close(client_sock);
	}
}
