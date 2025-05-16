// fs.h
#ifndef FS_H
#define FS_H

#define BLOCK_SIZE 1024
#define TOTAL_BLOCKS 1024
#define DISK_FILE "disk.img"
#define MAX_FILES 100
#define MAX_FILENAME 32
#define MAX_BLOCKS_PER_FILE 10
#define CACHE_SIZE 10

typedef struct {
    char filename[MAX_FILENAME];
    int size; // in bytes
    int blocks[MAX_BLOCKS_PER_FILE]; // block pointers
    int used; // 1 if file is in use
} FileMetadata;

typedef struct {
    int initialized;
    int num_files;
} SuperBlock;

typedef struct {
    int block_num;
    char data[BLOCK_SIZE];
    int dirty;
} CacheBlock;

#endif
