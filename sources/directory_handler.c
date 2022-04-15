#include "../headers/directory_handler.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void create_dir(char *path) {
    mkdir(path, 0700);
}

void dir_handle(char* source, char* destination) {
    // Creates a directory at given path

    DIR *t_directory;

    t_directory = opendir(destination);
    if(t_directory == NULL) {
        // Directory only exists in source path

        create_dir(destination);
        return;
    }
}