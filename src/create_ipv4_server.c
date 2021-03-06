#include "../simple_sockets.h"


int32_t create_ipv4_server(uint16_t server_port, uint8_t protocol, 
                                bool set_nonblock)
{
    /* create's a new socket file descriptor and binds it to the
    local IPv4 address of the computer */

    int32_t sock;
    struct sockaddr_in addr = {0};
    uint8_t sock_type = protocol == TCP ? SOCK_STREAM : SOCK_DGRAM;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(server_port);

    if ((sock = socket(PF_INET, sock_type, protocol)) < 0)
        return -1;
    if (set_nonblock == true)
        fcntl(sock, F_SETFL, O_NONBLOCK);
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        return -1;
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return -1;
    return sock;
}
