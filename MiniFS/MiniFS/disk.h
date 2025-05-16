// disk.h
#ifndef DISK_H
#define DISK_H

void disk_open();
void disk_close();
void read_block(int block_num, void *buffer);
void write_block(int block_num, void *buffer);

#endif
