#include "../headers/file_handler.h"
#include "../headers/log_message.h"
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void duplicate_file(char *source, char* destination) {

    // printf("Copy file from \"%s\" to: \"%s\"", source, destination);
    int error_code = 0;

    int fd, fd_copy, sz;
    char *c = (char *) calloc(1, sizeof(char)); 
  
    fd = open(source, O_RDONLY);
    if (fd < 0) { 
        error_code = -1;
        log_copy_file(source, destination, error_code);
        return; 
    }

    fd_copy = open(
        destination,
        O_WRONLY | O_CREAT | O_TRUNC, 
        0644
    );
    
    if (fd_copy < 0) { 
        error_code = -2;
        log_copy_file(source, destination, error_code);
        return; 
    }

    while((sz = read(fd, c, 1)) > 0) { 
        write(fd_copy, c, 1);
    }

    log_copy_file(source, destination, error_code);
    return;
}

void delete_file(char* path) {
    int error_code = 0;
    log_remove_file(path, error_code);
    
    int a;
    if(a = remove(path) == 0) {
        log_remove_file(path, error_code);
        return;
    } else {
        error_code = -1;
        log_remove_file(path, error_code);
        return;
    }
}

void file_handle(char* source, char* destination, bool reverse) {

    int fd;
    fd = open(destination, O_RDONLY);

    if(fd < 0) {
        // File only exists in source path
        if(!reverse) {
            duplicate_file(source, destination);
            return;
        } else {
            delete_file(source);
            return;
        }
    }
    
    struct stat s_attr;
    struct stat d_attr;
    stat(source, &s_attr);
    stat(destination, &d_attr);
    char *source_date, *destination_date;

    source_date = strdup(ctime(&s_attr.st_mtime));
    destination_date = strdup(ctime(&d_attr.st_mtime));

    if(strcmp(source_date, destination_date) != 0) {
        duplicate_file(source, destination);
    } else {
        return;
    }
}