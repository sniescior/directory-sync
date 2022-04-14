#include "destination_path.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* file_path(char* dir_name, char* file_name) {
    printf("%s, %s\n", dir_name, file_name);
    char *path;
    char *temp;

    temp = malloc(strlen(dir_name) + strlen("/"));
    strcpy(temp, dir_name);
    strcat(temp, "/");

    path = malloc(strlen(temp) + strlen(file_name));
    strcpy(path, temp);
    strcat(path, file_name);

    free(temp);

    return path;
}