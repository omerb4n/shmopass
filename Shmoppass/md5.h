#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// These vars will contain the hash
unsigned int h0, h1, h2, h3;

unsigned int * md5(uint8_t *initial_msg, size_t initial_len);