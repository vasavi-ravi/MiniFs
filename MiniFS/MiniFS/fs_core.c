// fs_core.c
#include <stdio.h>
#include <string.h>
#include "fs_core.h"
#include "fs.h"
#include "disk.h"
#include "cache.h"

static SuperBlock super;
static FileMetadata files[MAX_FILES];

void fs_init() {
    disk_open();
    read_block(0, &super);
    if (super.initialized != 1) {
        super.initialized = 1;
        super.num_files = 0;
        write_block(0, &super);
    }
    read_block(1, files);
    cache_init();
}

void fs_shutdown() {
    write_block(1, files); // update file metadata
    cache_flush();
    disk_close();
}

int fs_create(const char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].used) {
            files[i].used = 1;
            strncpy(files[i].filename, filename, MAX_FILENAME);
            files[i].size = 0;
            memset(files[i].blocks, -1, sizeof(files[i].blocks));
            super.num_files++;
            return i;
        }
    }
    return -1;
}

int fs_find(const char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && strcmp(files[i].filename, filename) == 0)
            return i;
    }
    return -1;
}

void fs_write(const char *filename, const char *data) {
    int index = fs_find(filename);
    if (index == -1)
        index = fs_create(filename);

    int len = strlen(data);
    int blocks_needed = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    files[index].size = len;

    for (int i = 0; i < blocks_needed && i < MAX_BLOCKS_PER_FILE; i++) {
        int block_num = 2 + index * MAX_BLOCKS_PER_FILE + i;
        files[index].blocks[i] = block_num;
        char *block = cache_get_block(block_num);
        memcpy(block, data + i * BLOCK_SIZE, BLOCK_SIZE);
        cache_mark_dirty(block_num);
    }
}

void fs_read(const char *filename) {
    int index = fs_find(filename);
    if (index == -1) {
        printf("File not found\n");
        return;
    }

    int bytes_read = 0;
    while (bytes_read < files[index].size) {
        int block_num = files[index].blocks[bytes_read / BLOCK_SIZE];
        char *block = cache_get_block(block_num);
        int to_read = BLOCK_SIZE;
        if (bytes_read + to_read > files[index].size)
            to_read = files[index].size - bytes_read;
        fwrite(block, 1, to_read, stdout);
        bytes_read += to_read;
    }
    printf("\n");
}
