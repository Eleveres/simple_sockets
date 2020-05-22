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


#define MAX_CONNECTIONS 64
#define BACKLOG 128
#define BUFFER_SIZE 4096

#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM

/* sockets functions */
int32_t create_ipv4_server(uint16_t server_port, uint8_t sock_type);
int32_t create_ipv6_server(uint16_t server_port, uint8_t sock_type);
int32_t connect_to_server(const char *host, const char *port);
int32_t accept_connection(int32_t server_sock, struct sockaddr *addr, socklen_t *addr_len);
bool sendall(int32_t sock, void *buffer, uint32_t len, struct sockaddr *addr, socklen_t addr_len);
bool recvall(int32_t sock, void *buffer, uint32_t len, struct sockaddr *addr, socklen_t *addr_len);

/* encoding functions */
void encode_64bit(uint64_t n, uint8_t *byetarray, uint16_t index);
void encode_32bit(uint32_t n, uint8_t *byetarray, uint16_t index);
void encode_16bit(uint16_t n, uint8_t *byetarray, uint16_t index);
uint64_t decode_64bit(uint8_t *byetarray, uint16_t index);
uint32_t decode_32bit(uint8_t *byetarray, uint16_t index);
uint16_t decode_16bit(uint8_t *byetarray, uint16_t index);

/* extra functions */
void print_bytearray(void *array, uint64_t array_len, const char *mode);
