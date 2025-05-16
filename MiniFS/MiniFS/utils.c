// utils.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void panic(const char *msg) {
    fprintf(stderr, "FATAL: %s\n", msg);
    exit(1);
}

void zero_block(char *block) {
    memset(block, 0, 1024);  // Assumes BLOCK_SIZE = 1024
}
