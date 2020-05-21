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

Server:

```C
#include "simple_socket.h"
#include <strings.h>


#define HEADER_LENGTH 8

int main(void) {
	uint8_t header[HEADER_LENGTH];
	uint8_t *raw_data;
	uint32_t server_sock, client_sock;

	/* Create a tcp4 server, starts listening on port 8000
	for incoming connections and accept the first one we get */
	server_sock = create_ipv4_server(8000, SOCK_STREAM);
	listen(server_sock, BACKLOG);
	client_sock = accept_connection(server_sock);

	/* Receive the header containing the file's size and 
	allocates a buffer to store the data */ 
	recvall(client_sock, header, HEADER_LENGTH, NULL, NULL);
	uint64_t data_length = decode_64bit(header, 0);
	uint8_t *data = malloc(data_length);
	
	/* Finally receive the raw data and write it to a file */
	recvall(client_sock, data, data_length, NULL, NULL);
	FILE *fp = fopen("success.JPG", "w");
	fwrite(data, 1, data_length, fp);
	fclose(fp);
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
