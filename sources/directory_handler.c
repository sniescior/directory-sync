#include "../headers/directory_handler.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void create_dir(char *path) {
    mkdir(path, 0700);
}

void delete_dir(char* path) {
    printf("Remove dir from %s\n", path);

    int a;
    unlink(path);
    if(a = remove(path) == 0) {
        printf("\t\t ^ directory deleted successfully (%d)\n", a);
    } else {
        printf("\t\t ^ there was a proble while deleting a directory (%d)\n", a);
    }
}

void dir_handle(char* source, char* destination, bool reverse) {
    // Creates a directory at given path

    DIR *t_directory;

    t_directory = opendir(destination);
    if(t_directory == NULL) {
        // Directory only exists in source path

        if(!reverse) {
            create_dir(destination);
        } else {
            delete_dir(source);
        }
        return;
    }
}