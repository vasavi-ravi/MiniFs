// cache.h
#ifndef CACHE_H
#define CACHE_H

#include "fs.h"

void cache_init();
char *cache_get_block(int block_num);
void cache_mark_dirty(int block_num);
void cache_flush();

#endif
