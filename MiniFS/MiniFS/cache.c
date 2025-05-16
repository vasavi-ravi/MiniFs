// cache.c

#include "cache.h"
#include <string.h>
#include "disk.h"
#include <stdlib.h>


static CacheBlock cache[CACHE_SIZE];

void cache_init() {
    for (int i = 0; i < CACHE_SIZE; i++)
        cache[i].block_num = -1;
}

char *cache_get_block(int block_num) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].block_num == block_num)
            return cache[i].data;
    }

    // If not found, load from disk
    int replace_index = rand() % CACHE_SIZE;
    CacheBlock *cb = &cache[replace_index];
    
    if (cb->dirty)
        write_block(cb->block_num, cb->data);

    read_block(block_num, cb->data);
    cb->block_num = block_num;
    cb->dirty = 0;
    return cb->data;
}

void cache_mark_dirty(int block_num) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].block_num == block_num)
            cache[i].dirty = 1;
    }
}

void cache_flush() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].dirty && cache[i].block_num != -1) {
            write_block(cache[i].block_num, cache[i].data);
            cache[i].dirty = 0;
        }
    }
}
