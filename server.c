#include "simple_socket.h"
#include <strings.h>


#define HEADER_LENGTH 8

int main(void) {
	int8_t server_sock, client_sock;
	uint8_t header[HEADER_LENGTH];
	uint8_t *raw_data;
	uint64_t data_len;
	FILE *fp;

	/* Create a tcp4 server, starts listening on port 8000
	for incoming connections and accept the first one we get */
	server_sock = create_ipv4_server(8000, TCP);
	listen(server_sock, BACKLOG);
	client_sock = accept_connection(server_sock, NULL, NULL);

	/* Receive the header containing the file's size and 
	allocates a buffer to store the data */ 
	recvall(client_sock, header, HEADER_LENGTH, NULL, NULL);
	data_len = decode_64bit(header, 0);
	raw_data = malloc(data_len);
	
	/* Finally receive the raw data and write it to a file */
	recvall(client_sock, raw_data, data_len, NULL, NULL);
	fp = fopen("success.JPG", "w");
	fwrite(raw_data, 1, data_len, fp);
	fclose(fp);
}