#include "simple_socket.h"
#include <strings.h>
#include <sys/stat.h>


#define HEADER_LENGTH 8

int main(void) {
	FILE *fp;
	struct stat info;
	uint8_t *raw_data;
	int8_t server_sock;

	/* Finds out the size of the file to send, allocates the appropriate
	space for it and then load our file into the buffer*/
	fp = fopen("cute_cat.JPG", "r");
	fstat(fileno(fp), &info);
	uint8_t *data = malloc(HEADER_LENGTH + info.st_size);
	fread(data + HEADER_LENGTH, 1, info.st_size, fp);
	fclose(fp);

	/* encode the size of the file in the 8 first byte of our buffer
	and then sends the total to the server */
	encode_64bit(info.st_size, data, 0);
	server_sock = connect_to_server("127.0.0.1", "8000");
	sendall(server_sock, data, HEADER_LENGTH + info.st_size, NULL, 0);
}