#include <stdio.h>
#include <string.h>
#include "fs_core.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: minifs <command> [args]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) {
        fs_init();
        printf("MiniFS initialized successfully.\n");
        fs_shutdown();
    } else if (strcmp(argv[1], "write") == 0 && argc == 4) {
        fs_init();
        fs_write(argv[2], argv[3]);
        printf("File '%s' written.\n", argv[2]);
        fs_shutdown();
    } else if (strcmp(argv[1], "read") == 0 && argc == 3) {
        fs_init();
        fs_read(argv[2]);
        fs_shutdown();
    } else if (strcmp(argv[1], "flush") == 0) {
        fs_init();
        fs_shutdown();
        printf("Flushed successfully.\n");
    } else if (strcmp(argv[1], "open") == 0 || strcmp(argv[1], "close") == 0) {
        printf("Note: '%s' is not required in this simplified file system.\n", argv[1]);
    } else if (strcmp(argv[1], "fsck") == 0) {
        printf("Filesystem check not implemented.\n");
    } else {
        printf("Unknown command\n");
    }

    return 0;
}





