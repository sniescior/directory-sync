#include <dirent.h> 
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

struct File {
    char* name;
    char* modification_date;
    int reg_file;
    struct File* next;
};

void push(struct File** head_ref, char* name, char* date, int reg_file) {
    struct File* new_file = (struct File*) malloc(sizeof(struct File));
    new_file->name = name;
    new_file->modification_date = date;
    new_file->reg_file = reg_file;
    new_file->next = (*head_ref);

    (*head_ref) = new_file;
}

// Creates a path to specific file by name
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

// Lists all the files and directories in a specific directory
// . and .. not included
void list_all(char *dir_name, struct File** head_ref, int R_FLAG) {

    DIR *d;
    struct dirent *dir;
    struct stat attr;
    d = opendir(dir_name);

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(".", dir->d_name) == 0) { continue; }
            if(strcmp("..", dir->d_name) == 0) { continue; }

            stat(file_path(dir_name, dir->d_name), &attr);
            
            if(R_FLAG == 0 && !S_ISREG(attr.st_mode)) {
                // if directory (not a regular file) and R_FLAG == 0 (is not active) 
                // exclude (skip) all the directoires
                continue;
            }

            char *date = NULL, *file_name = NULL;
            int reg_file;
            date = strdup(ctime(&attr.st_mtime));
            file_name = strdup(dir->d_name);
            reg_file = S_ISREG(attr.st_mode);
            push(head_ref, file_name, date, reg_file);
        }

    closedir(d);
  }
}

bool find(struct File* file, char *name, char *date) {
    // true (1) if found
    // false (0) if not
    while(file != NULL) {
        if(strcmp(file->name, name) == 0) {
            if(strcmp(file->modification_date, date) == 0) {
                return true;
            } else {
                return false;
            }
        }
        file = file->next;
    }
    return false;
}

void copy(struct File* source, struct File* destination, char *source_path, char *destination_path) {
    // Find files that only exist in source directory
    while(source != NULL) {
        if(!find(destination, source->name, source->modification_date)) {

            // printf("Copy \"%s\" from source to destination.\n", source->name);
            char *path_to_file, *destination_path_to_file;
            path_to_file = file_path(source_path, source->name);
            destination_path_to_file = file_path(destination_path, source->name);

            printf("Copy \"%s\" to destination: \"%s\". \n", path_to_file, destination_path_to_file);
            
            // Copying part of the program
            // $ cp -p katalog/hello.py katalog-sync <-- linux command to copy preserving the timestamp of the original file
            // ------- source/file ---- destination

        }
        source = source->next;
    }
}

// Function removes files or directories (recursively)
void remove_file(char* name, int indent) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name))) { return; }

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) { continue; }

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            remove_file(path, indent + 2);
            unlink(path);
            rmdir(path);
        } else {
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            remove(path);
        }
    }
    closedir(dir);
}

void delete(struct File* source, struct File* destination, char *destination_path) {
    while(destination != NULL) {
        if(!find(source, destination->name, destination->modification_date)) {
            // Removing part of the program
            char *path_to_file;
            path_to_file = file_path(destination_path, destination->name);
            printf("Delete \"%s\" from destination. ", path_to_file);
            if(destination->reg_file == 1) {
                remove_file(path_to_file, 0);
            } else {
                remove_file(path_to_file, 0);
                unlink(path_to_file);
                printf("%d\n", remove(path_to_file));
            }
        }
        destination = destination->next;
    }
}

void print(struct File *file) {
    while(file != NULL) {
        if(file->reg_file) {
            printf("F  %15s --- %13s", file->name, file->modification_date);
        } else {
            printf("D  %15s --- %13s", file->name, file->modification_date);
        }
        file = file->next;
    }

    return;
}

int main(void)
{
    struct File* source_files = NULL;
    struct File* destination_files = NULL;

    char* source_path = "katalog";
    char* destination_path = "katalog-sync";
    list_all(source_path, &source_files, 1);
    list_all(destination_path, &destination_files, 1);

    printf("Katalog:\n");
    print(source_files);
    printf("\nKatalog-sync:\n");
    print(destination_files);

    printf("\n\nWhat needs to be done:\n");

    delete(source_files, destination_files, destination_path);
    printf("\n");
    copy(source_files, destination_files, source_path, destination_path);

    return 0;
}