#pragma once

#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>


#define MAX_CONNECTIONS 64
#define BACKLOG 128
#define BUFFER_SIZE 4096

#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP

/* sockets functions */
int32_t create_ipv4_server(uint16_t server_port, uint8_t protocol, bool set_nonblock);
int32_t create_ipv6_server(uint16_t server_port, uint8_t protocol, bool set_nonblock);
int32_t connect_to_server(const char *host, const char *port);
int32_t accept_connection(int32_t server_sock, struct sockaddr *addr, socklen_t *addr_len);
bool sendall(int32_t sock, void *buffer, int32_t len, struct sockaddr *addr, socklen_t addr_len);
bool recvall(int32_t sock, void *buffer, int32_t len, struct sockaddr *addr, socklen_t *addr_len);

/* encoding functions */
void encode_64bit(uint64_t n, uint8_t *byetarray);
void encode_32bit(uint32_t n, uint8_t *byetarray);
void encode_16bit(uint16_t n, uint8_t *byetarray);
uint64_t decode_64bit(uint8_t *byetarray);
uint32_t decode_32bit(uint8_t *byetarray);
uint16_t decode_16bit(uint8_t *byetarray);

/* extra functions */
void print_bytearray(void *array, uint64_t array_len, const char *mode);
void print_bytearray_rows(void *array, uint64_t array_len, const char *mode, uint8_t row_size);
