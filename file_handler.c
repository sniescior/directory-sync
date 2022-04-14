#include "file_handler.h"
#include "destination_path.h"
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

void copy(char *source, char* dest) {
    int fd, fd_copy, sz, sz_copy;
    char *c = (char *) calloc(1, sizeof(char)); 
  
    fd = open(source, O_RDONLY);
    if (fd < 0) { perror("r1"); exit(1); }

    fd_copy = open(
        dest,
        O_WRONLY | O_CREAT | O_TRUNC, 
        0644
    );
    if (fd_copy < 0) { perror("r2"); exit(1); }

    while((sz = read(fd, c, 1)) > 0) { 
        write(fd_copy, c, 1);
    }
}   

void copy_file(char* source, char* path, char* d_reference) {
    // Copies file to the destination path equivalent of source path
    // e.g. katalog/nowy/foo.txt --> katalog-sync/nowy/foo.txt

    // source_file - katalog/nowy/foo.txt
    // temp1 - katalog-sync/nowy/foo.txt

    char *final_path;
    char *source_file = file_path(source, path);

    int i, check = 0;
    for(i = 0; i < strlen(source_file); i++) {
        if(source_file[i] == '/') {
            check = i;
            break;
        }
    }

    char *temp1 = file_path(d_reference, source_file+check+1);

    int fd;
    fd = open(temp1, O_RDONLY);

    // printf("\t (%d) %s <--> %s (%d)\n", fd_original, source_file, temp1, fd);

    if(fd < 0) {
        // File only exists in source path

        copy(source_file, temp1);
        return;
    }
    
    struct stat attr_original;
    struct stat attr_copy;
    stat(source_file, &attr_original);
    stat(temp1, &attr_copy);
    char *date_original, *date_copy;

    date_original = strdup(ctime(&attr_original.st_mtime));
    date_copy = strdup(ctime(&attr_copy.st_mtime));

    if(strcmp(date_original, date_copy) != 0) {
        copy(source_file, temp1);
    } else {
        return;
    }
}