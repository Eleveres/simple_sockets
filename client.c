#include "simple_socket.h"
#include <strings.h>
#include <sys/stat.h>


#define HEADER_LENGTH 8

int main(void) {
	int8_t serv_sock = connect_to_server("127.0.0.1", "8000");
	sendall(serv_sock, "coucou", 6, NULL, 0);
	close(serv_sock);
}