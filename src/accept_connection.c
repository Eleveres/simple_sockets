#include "../simple_socket.h"


int32_t accept_connection(int32_t server_sock, struct sockaddr *addr, 
                            socklen_t *addr_len)
{
    /* if the addr parameter is set to NULL the information about
    the client's address aren't saved. If the accept() call suceeds
    the tmp buffer of the socket file descriptor is flushed to avoid
    collision with previous messages from the previous client that
    used the same file descriptor. */

    int32_t sock;

    if (addr == NULL) {
        struct sockaddr_in addr_lost;
        socklen_t addr_lost_len;
        if ((sock = accept(server_sock, (struct sockaddr *)&addr_lost, 
                &addr_lost_len)) < 0)
            return -1;
    }
    else {
        if ((sock = accept(server_sock, addr, addr_len)) < 0)
            return -1;
    }
    recvall(sock, NULL, 0, NULL, NULL);
    return sock;
}