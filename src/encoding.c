#include "../simple_sockets.h"


/* encode/decode different integer sizes into/from a bytearray */

void encode_64bit(uint64_t n, uint8_t *byetarray) 
{
    uint8_t shift = 56;
    for (uint16_t i = 0; i < 8; i++) {
        byetarray[i] = (n >> shift) & 255;
        shift -= 8;
    }
}

void encode_32bit(uint32_t n, uint8_t *byetarray) 
{
    uint8_t shift = 24;
    for (uint16_t i = 0; i < 4; i++) {
        byetarray[i] = (n >> shift) & 255;
        shift -= 8;
    }
}

void encode_16bit(uint16_t n, uint8_t *byetarray) 
{
    uint8_t shift = 8;
    for (uint16_t i = 0; i < 2; i++) {
        byetarray[i] = (n >> shift) & 255;
        shift -= 8;
    }
}

uint64_t decode_64bit(uint8_t *byetarray)
{
    uint64_t decoded = 0;
    uint8_t shift = 56;
    for (uint16_t i = 0; i < 8; i++) {
        decoded = decoded | ((uint64_t)byetarray[i] << shift);
        shift -= 8;
    }
    return decoded;
}

uint32_t decode_32bit(uint8_t *byetarray)
{
    uint32_t decoded = 0;
    uint8_t shift = 24;
    for (uint16_t i = 0; i < 4; i++) {
        decoded = decoded | (byetarray[i] << shift);
        shift -= 8;
    }
    return decoded;
}

uint16_t decode_16bit(uint8_t *byetarray)
{
    uint16_t decoded = 0;
    uint8_t shift = 8;
    for (uint16_t i = 0; i < 2; i++) {
        decoded = decoded | (byetarray[i] << shift);
        shift -= 8;
    }
    return decoded;
}