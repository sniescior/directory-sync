#include "directory_handler.h"
#include "destination_path.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int create_dir(char* source, char* path) {
    // Creates a directory at given path

    // path - source path to the directory that is being searched
    // final_path - where the directory needs to be duplicated
    char *final_path;
    char *temp;

    int i, check = 0;
    for(i = 0; i < strlen(path); i++) {
        if(path[i] == '/') {
            check = i;
            break;
        }
    }

    final_path = file_path(source, path+check+1);

    DIR *t_directory;
    struct dirent *t_dir;

    t_directory = opendir(final_path);
    if(t_directory == NULL) {
        // Directory only exists in source path

        // printf("\t NULL %s <--> %s\n", path, final_path);
        mkdir(final_path, 0700);
    }

    return check;
}