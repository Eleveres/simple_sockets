#include "../simple_sockets.h"

bool sendall(int32_t sock, void *buffer, int32_t len,
                struct sockaddr *addr, socklen_t addr_len)
{
    /* calls send() until the amount of bytes specified by
    the len parameter has been sent */

    uint8_t *buffer_ptr = (uint8_t *)buffer;
    int32_t sent;
    int32_t total_sent = 0;

    while (total_sent < len) {
        if ((sent = sendto(sock, buffer_ptr, len, 0, addr, addr_len)) < 0)
            return false;
        total_sent += sent;
        buffer_ptr += sent;
    }
    return true;
}