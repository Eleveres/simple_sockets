# Simple sockets

A simple C libaray to make the use of unix sockets easier and more understandable.

## Getting Started

To use this library simply clone the repository and compile the sources using the makefile.

### Installing

```
git clone https://github.com/Eleveres/simple_sockets
cd simple_sockets
make
```

### Compiling

```
gcc -o chat_server chat_server.c simple_sockets.a
```

## A simple client/server example to send a photo using sockets

**Note:** This example should only be used as a demonstration and not production since the code
doesn't check for errors and does not supplies an efficient way of sending files over sockets. 
(Should read chunks of data not the hole file at once to avoid using to up to much space in the RAM)



**Server:**
```C
#include "simple_socket.h"
#include <strings.h>


#define HEADER_LENGTH 8

int main(void) {
	uint8_t server_sock, client_sock;
	uint8_t header[HEADER_LENGTH];
	uint8_t *raw_data;
	uint64_t data_len;
	FILE *fp;

	/* Create a tcp4 server, starts listening on port 8000
	for incoming connections and accept the first one we get */
	server_sock = create_ipv4_server(8000, SOCK_STREAM);
	listen(server_sock, BACKLOG);
	client_sock = accept_connection(server_sock);

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

```


**Client:**
```C
#include "simple_socket.h"
#include <strings.h>
#include <sys/stat.h>


#define HEADER_LENGTH 8

int main(void) {
	FILE *fp;
	struct stat info;
	uint8_t *raw_data;
	uint8_t server_sock;

	/* Finds out the size of the file to send, allocates the appropriate
	space and then load sour file into the buffer*/
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
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
