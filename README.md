# Simple sockets

A simple C library to make the use of unix sockets easier and more understandable.

## Getting Started

To use this library, simply clone the repository and compile the sources using the makefile.

### Installing

```
git clone https://github.com/Eleveres/simple_sockets
cd simple_sockets
make
```

### Compiling

```
gcc example.c simple_sockets.a
```

## A simple client/server example to send a photo using simple_sockets

**Note:** This example should only be used as a demonstration and not for production since the code
doesn't check for errors and does not supply an efficient way of sending files over sockets. 
(Should read chunks of data not the whole file at once to avoid using up too much space in the RAM)



**Server:**
```C
#include "simple_socket.h"


#define HEADER_LENGTH 8

int main(void) {
	int8_t server_sock, client_sock;
	uint8_t header[HEADER_LENGTH];
	uint8_t *raw_data;
	uint64_t data_len;
	FILE *fp;

	/* Create a tcp4 server, start listening on port 8000
	for incoming connections and accept the first one */
	server_sock = create_ipv4_server(8000, TCP, false);
	listen(server_sock, BACKLOG);
	client_sock = accept_connection(server_sock, NULL, NULL);

	/* Receive the header containing the file's size and 
	allocate a buffer to store the data */ 
	recvall(client_sock, header, HEADER_LENGTH, NULL, NULL);
	data_len = decode_64bit(header);
	raw_data = malloc(data_len);
	
	/* Finally, receive the raw data and write it to a file */
	recvall(client_sock, raw_data, data_len, NULL, NULL);
	fp = fopen("success.JPG", "w");
	fwrite(raw_data, 1, data_len, fp);
	fclose(fp);
}

```


**Client:**
```C
#include "simple_socket.h"
#include <sys/stat.h>


#define HEADER_LENGTH 8

int main(void) {
	FILE *fp;
	struct stat info;
	uint8_t *raw_data;
	int8_t server_sock;

	/* Find out the size of the file to send, allocate the appropriate
	space for it and then load the file into the buffer*/
	fp = fopen("cute_cat.JPG", "r");
	fstat(fileno(fp), &info);
	raw_data = malloc(HEADER_LENGTH + info.st_size);
	fread(raw_data + HEADER_LENGTH, 1, info.st_size, fp);
	fclose(fp);

	/* Encode the size of the file in the 8 first bytes of our buffer
	and then send the total to the server */
	encode_64bit(info.st_size, raw_data);
	server_sock = connect_to_server("127.0.0.1", "8000");
	sendall(server_sock, raw_data, HEADER_LENGTH + info.st_size, NULL, 0);
}
```

## Documentation

### Macros:
```C
#define MAX_CONNECTIONS 64
#define BACKLOG 128
#define BUFFER_SIZE 4096
```
These macros can be redefined to suit the purpose of your project.

**MAX_CONNECTIONS:** 
* This macro defines the maximum number of simultaneous connections you can have at the same time. 
* Having more connections than the specified value of the macro may result in your application trying to
read out of its memory and cause a segmentation fault.

**BACKLOG:**
* Check the man page of the [listen()](http://man7.org/linux/man-pages/man2/listen.2.html) function to find
out which value to set as the backlog.
* If you don't see the purpose of changing the backlog value, don't. Just leave it at 128, which is the maximum 
value used by most systems.

**BUFFER_SIZE:**
* This macro is used by the recvall function to determine how much data your app can read per call of the 
recv function.
* Again, if you don't see the purpose of changing that value, don't. 4K is generally a good buffer size for
apps communicating over the internet.

### create_ipv4_server():
```C
int32_t create_ipv4_server(uint16_t server_port, uint8_t protocol, bool set_nonblock);
```
Parameters:
* server_port: the port which the server will be listening on
* protocol: the protocol of communication to use (TCP or UDP)
* set_nonblock: set the socket in a non blocking mode

Return value:
* a socket file descriptor

Description:
* The function will create the socket, bind it to the computer's local IPv4 address and make sure that
the address can be reused (to avoid bind() errors).

### create_ipv6_server():
```C
int32_t create_ipv6_server(uint16_t server_port, uint8_t protocol, bool set_nonblock);
```
Parameters:
* server_port: the port which the server will be listening on
* protocol: the protocol of communication to use (TCP or UDP)
* set_nonblock: set the socket in a non blocking mode

Return value:
* a socket file descriptor

Description:
* The function will create the socket, bind it to the computer's local IPv6 address and make sure that
the address can be reused (to avoid bind() errors).

### accept_connection():
```C
int32_t accept_connection(int32_t server_sock, struct sockaddr *addr, socklen_t *addr_len);
```
Parameters:
* server_sock: the server's socket file descriptor
* addr: a pointer to a sockaddr struct that will be filled with the information of the address of the new client
* addr_len: a pointer to a socklen_t element that will be replaced with the size of addr

Return value:
* a new socket file descriptor corresponding to the new client connection

Description:
* This function **must** be used to accept new connections if you plan on using the recvall() function. This is
because the accept_connection() function is in charge of flushing the recvall tmp buffer for the new socket file
descriptor.
* If you really wish to use the orginal [accept()](http://man7.org/linux/man-pages/man2/accept.2.html) function,
check how to manually flush the recvall tmp buffer a bit lower in the documentation.

### connect_to_server():
```C
int32_t connect_to_server(const char *host, const char *port);
```
Parameters:
* host: the server's domain or IP address
* port: the port the server is listening on

Return value:
* a socket file descriptor corresponding to the new connection to the server 

Description:
* The function will find out the server's IP addresses using 
[getaddrinfo()](http://man7.org/linux/man-pages/man3/getaddrinfo.3.html)
and will connect to the first one it can.

### recvall():
```C
bool recvall(int32_t sock, void *buffer, int32_t len, struct sockaddr *addr, socklen_t *addr_len);
```
Parameters:
* sock: socket file descriptor to receive from
* buffer: the buffer to fill with the received data
* len: the requested amount of bytes to receive before the function returns
* addr: a pointer to a sockaddr structure that will be filled with the information of the sender;
this parameter will be ignored when using a socket in a connected mode (TCP)
* addr_len: a pointer to a socklen_t element that will be replaced with the size of addr;
this parameter will be ignored when using a socket in a connected mode (TCP)

Return value:
* a boolean value indicating if the operation has succeeded or failed

Description:
* The function will call the [recv()](http://man7.org/linux/man-pages/man2/recv.2.html) function repeatedly 
until the the amount of bytes requested by the len paramter is received. The function uses a fixed buffer size
to increase performance and will save the extra bytes read in a static array.
When using this function on a socket in connection mode (TCP), the last 2 parameters can be set to NULL.

Extra:
* If you wish for some reason to flush the tmp buffer of a socket's file descriptor you can call the recvall
function with a buffer set to NULL and the len parameter to 0.

### sendall():
```C
bool sendall(int32_t sock, void *buffer, int32_t len, struct sockaddr *addr, socklen_t *addr_len);
```
Parameters:
* sock: socket file descriptor to write to
* buffer: the buffer containing the data to send
* len: the size of the buffer in bytes
* addr: a pointer to a sockaddr structure containing the information of the receiver;
this parameter will be ignored when using a socket in a connected mode (TCP)
* addr_len: the size of the addr structure;
this parameter will be ignored when using a socket in a connected mode (TCP)

Return value:
* a boolean value indicating if the operation has succeeded or failed

Description:
* The function will call the [send()](http://man7.org/linux/man-pages/man2/send.2.html) function repeatedly 
until the the amount of bytes specified by the len paramter has been sent.
When using this function on a socket in connection mode (TCP), the last 2 parameters can be set to NULL and 0,
respectively.

### encode_nbit():
```C
void encode_64bit(uint64_t n, uint8_t *buffer);
void encode_32bit(uint32_t n, uint8_t *buffer);
void encode_16bit(uint16_t n, uint8_t *buffer);
```
Parameters:
* bytearray: the bytearray to encode the number to

Return value:
* None

Description:
* These functions allow you to encode 16, 32 and 64 bit integer into byetarrays.
* Useful for creating network headers.

### decode_nbit():
```C
uint64_t decode_64bit(uint8_t *byetarray);
uint32_t decode_32bit(uint8_t *byetarray);
uint16_t decode_16bit(uint8_t *byetarray);
```
Parameters:
* bytearray: the bytearray to decode the number from

Return value:
* The decoded value in a 16, 32 or 64 bit integer, depending on the used function

Description:
* These functions allow you to decode 16, 32 and 64 bit integer from byetarrays.
* Useful for decoding network headers.

### print_bytearray():
```C
void print_bytearray(void *array, uint64_t array_len, const char *mode);
```
Parameters:
* array: the bytearray to print the values of
* array_len: the length in bytes of the array (or the number of bytes you wish to print)
* mode: the printing mode (see below for different modes)

Return value:
* None

Description:
* This is a simple function used to print bytearrays in a nice and clear way.
* Useful for debugging.

Modes:
* x: print all the bytes in a hexadecimal format
* d: print all the bytes in a decimal format
* c or cx: print the printable bytes as characters and the rest as hexadecimal 
* cd: print the printable bytes as characters and the rest as decimals 

## TODO:
* Add polling functions

## Author

* **Ravi Pousseur**

