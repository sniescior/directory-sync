#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void compare(char* source, char* destination, char* reference);
char *file_path(char* dir_name, char* file_name);
char *swap(char* source, char* reference);

int main(int argc, char const *argv[])
{
    // Compare two directories side by side
    char* source = "katalog";
    char* destination = "katalog-sync";
    compare(source, destination, destination);

    return 0;
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

    return path;
}

void compare(char* source, char* destination, char* reference) {

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
                printf("F %s/%s", source, s_dir->d_name);

                // If opening this file in destination directory gives an error
                // we need to copy that file from source folder to destination
                // source/hello.py --> cource-copy/hello.py

                int fd;
                char* path = file_path(destination, s_dir->d_name);

                if((fd = open(path, O_RDONLY)) < 0) {
                    printf("\t\t <<-- only in \"%s\"\n", source);
                } else {
                    printf("\t\t <<-- In both directories\n");
                }
            } else {
                // Directory
                printf("D %s/%s", source, s_dir->d_name);

                DIR *t_directory;
                struct dirent *t_dir;

                t_directory = opendir(file_path(destination, s_dir->d_name));
                if(t_directory == NULL) {
                    // printf("\t\t <<-- only in \"%s\"\n", source);
                    printf("\t\t <<-- create dir in \"%s/%s\"\n", swap(source, reference), s_dir->d_name);
                    // mkdir(swap(source, reference), 0700);
                } else {
                    printf("\t\t <<-- In both directories\n");
                }

                compare(file_path(source, s_dir->d_name), destination, reference);
            }
        }
    }
}

char *swap(char* source, char* reference) {
    int i, check = 0;
    for(i = 0; i < strlen(source); i++) {
        if(source[i] == '/') {
            check = i + 1;
            break;
        }
    }
    source += check;

    return file_path(reference, source);
}
