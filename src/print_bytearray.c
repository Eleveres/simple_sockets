#include "../simple_sockets.h"


void print_bytearray(void *array, uint64_t array_len, const char *mode) 
{
    /* prints nicely a bytearray in different formats */

    uint8_t *bytearray = (uint8_t *)array;

    for (uint32_t i = 0; i < array_len; i++) {
        if (mode[0] == 'c') {
            if (bytearray[i] >= 33 && bytearray[i] <= 127) {
                printf("%4c", bytearray[i]);
            }
            else if (mode[1] == 'd') {
                printf("%4d", bytearray[i]);
            }
            else {
                printf("%4x", bytearray[i]);
            }
        }
        else if (mode[0] == 'x') {
            printf("%4x", bytearray[i]);
        }
        else {
            printf("%4d", bytearray[i]);
        }
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}