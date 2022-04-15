#include "../headers/compare.h"
#include "../headers/directory_handler.h"
#include "../headers/file_handler.h"
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char* create_path(char* source, char* temp_path) {
    char* new_str;
    new_str = malloc(strlen(source) + strlen(temp_path) + strlen("/") + 1);
    new_str[0] = '\0';
    strcat(new_str, source);
    strcat(new_str, "/");
    strcat(new_str, temp_path);

    return new_str;
}

void compare(char* source, char* destination, char* temp_path, char* dest_path) {

    DIR *s_directory;
    struct dirent *s_dir;
    struct stat s_attr;
    s_directory = opendir(source);

    if(s_directory) {
        while((s_dir = readdir(s_directory)) != NULL) {
            if(strcmp(".", s_dir->d_name) == 0) { continue; }
            if(strcmp("..", s_dir->d_name) == 0) { continue; }

            stat(create_path(source, s_dir->d_name), &s_attr);
            temp_path = create_path(source, s_dir->d_name);

            dest_path = create_path(destination, s_dir->d_name);

            if(S_ISREG(s_attr.st_mode)) {
                // Regular file
                file_handle(temp_path, dest_path);
                // printf("F: %s \t\t<-->\t\t %s\n", temp_path, dest_path);
            } else {
                // Directory

                // printf("D: %s \t\t<-->\t\t %s\n", temp_path, dest_path);
                create_dir(dest_path);
                compare(temp_path, dest_path, temp_path, dest_path);
            }
        }
    }
}