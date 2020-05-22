#include "../simple_socket.h"


void print_bytearray(void *array, uint64_t array_len) 
{
	uint8_t *bytearray = (uint8_t *)array;

	for (uint64_t i = 0; i < array_len; i++) {
		if (bytearray[i] >= 33 && bytearray[i] <= 127)
			printf("%c ", bytearray[i]);
		else
			printf("%d ", bytearray[i]);
		// if (i != 0 && i % 30 == 0) printf("\n");
	}	
	printf("\n\n\n");
}