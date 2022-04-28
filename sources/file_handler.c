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
#include <sys/mman.h>

long int get_size(char *path) {
    FILE *fp = fopen(path, "r");
    if(!fp) {
        printf("File not found.\n");
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    long int res = ftell(fp);
    fclose(fp);

    return res;
}

void duplicate_huge_file(char *source, char* destination) {
    int error_code = 0;

    int source_file, destination_file;
    char *source_temp, *destination_temp ;
    struct stat source_stat;
    size_t size;

    source_file = open(source, O_RDONLY);
    if(!source_file) {
        error_code = 1;
        log_copy_file(source, destination, error_code);
        return;
    }
    
    size = lseek(source_file, 0, SEEK_END);
    source_temp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, source_file, 0);

    destination_file = open(destination, O_RDWR | O_CREAT, 0666);
    if(!destination_file) {
        error_code = 2;
        log_copy_file(source, destination, error_code);
        return;
    }

    ftruncate(destination_file, size);
    destination_temp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, destination_file, 0);

    memcpy(destination_temp, source_temp, size);
    munmap(source_temp, size);
    munmap(destination_temp, size);

    close(source_file);
    close(destination_file);

    log_copy_file(source, destination, error_code);
}

void duplicate_file(char *source, char* destination) {
    int error_code = 0;

    int fd, fd_copy, sz;
    char *c = (char *) calloc(1, sizeof(char)); 
  
    fd = open(source, O_RDONLY);
    if (fd < 0) { 
        error_code = -1;
        log_copy_file(source, destination, error_code);
        return; 
    }

    fd_copy = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void file_handle(char* source, char* destination, bool reverse, long int size) {
    int fd;
    fd = open(destination, O_RDONLY);

    if(fd < 0) {
        // File only exists in source path
        if(!reverse) {
            if(get_size(source) > size) {
                duplicate_huge_file(source, destination);
            } else {
                duplicate_file(source, destination);
            }
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
        if(get_size(source) > size) {
            duplicate_huge_file(source, destination);
        } else {
            duplicate_file(source, destination);
        }
    } else {
        return;
    }
}