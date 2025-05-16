// fs_core.h
#ifndef FS_CORE_H
#define FS_CORE_H

void fs_init();
void fs_shutdown();
void fs_write(const char *filename, const char *data);
void fs_read(const char *filename);

#endif
