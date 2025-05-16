// disk.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"

FILE *disk = NULL;

void disk_open() {
    disk = fopen(DISK_FILE, "r+b");
    if (!disk) {
        // Initialize disk if not present
        disk = fopen(DISK_FILE, "w+b");
        char zero[BLOCK_SIZE] = {0};
        for (int i = 0; i < TOTAL_BLOCKS; i++)
            fwrite(zero, BLOCK_SIZE, 1, disk);
    }
}

void disk_close() {
    if (disk) fclose(disk);
}

void read_block(int block_num, void *buffer) {
    fseek(disk, block_num * BLOCK_SIZE, SEEK_SET);
    fread(buffer, BLOCK_SIZE, 1, disk);
}

void write_block(int block_num, void *buffer) {
    fseek(disk, block_num * BLOCK_SIZE, SEEK_SET);
    fwrite(buffer, BLOCK_SIZE, 1, disk);
}
