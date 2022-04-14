#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void compare(char* source, char* destination);
char *file_path(char* dir_name, char* file_name);

int main(int argc, char const *argv[])
{
    // Compare two directories side by side
    char* source = "katalog";
    char* destination = "katalog-sync";
    compare(source, destination);

    return 0;
}

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

char *file_path(char* dir_name, char* file_name) {
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

void compare(char* source, char* destination) {

    // reference - constant destination path

    // s_[...] - source
    // d_[...] - destination
    // t_[...] - temporary

    DIR *s_directory, *d_directory, *t_directory;
    struct dirent *s_dir, *d_dir, *t_dir;
    struct stat s_attr, d_attr;
    s_directory = opendir(source);
    d_directory = opendir(source);

    if(s_directory) {
        while((s_dir = readdir(s_directory)) != NULL) {
            if(strcmp(".", s_dir->d_name) == 0) { continue; }
            if(strcmp("..", s_dir->d_name) == 0) { continue; }

            stat(file_path(source, s_dir->d_name), &s_attr);

            if(S_ISREG(s_attr.st_mode)) {
                // Regular file

                copy_file(source, s_dir->d_name, destination);
            } else {
                // Directory

                char *temp_path = file_path(source, s_dir->d_name);
                create_dir(destination, temp_path);

                compare(file_path(source, s_dir->d_name), destination);
            }
        }
    }
}
