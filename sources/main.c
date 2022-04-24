#include "../headers/file_handler.h"
#include "../headers/compare.h"
#include "../headers/directory_handler.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

void print_danger(char* message) {
    printf("\033[0;31m");   // red
    printf("%s\n", message);
    printf("\033[0;30m");   // black
}

void print_warning(char* message) {
    printf("\033[0;33m");   // yellow
    printf("%s\n", message);
    printf("\033[0;30m");
}

void print_success(char* message, char* additional) {
    printf("\033[0;32m");   // green

    if(strcmp(additional, "")) {
        printf("%s \"%s\"\n", message, additional);
    } else {
        printf("%s\n", message);
    }
    printf("\033[0;30m");
}

int main(int argc, char * const argv[])
{
    char* source;
    char* destination;

    bool recursive = false;

    int opt;
    while((opt = getopt(argc, argv, ":s:d:R")) != -1) {
        switch (opt) {
            case 's':
                source = strdup(optarg);
                printf("Source directory: \"%s\"\n", source);
                break;
            case 'd':
                destination = strdup(optarg);
                printf("Destination directory: \"%s\"\n", destination);
                break;
            case 'R':
                printf("Recursion active\n");
                recursive = true;
                break;
        }
    }

    if(argc < 3) {
        printf("Not enough arguments. Note that the program should receive at least path to source and destination directory.\n");
        printf("Read the documentation.\n");

        print_danger("Exit error");
        exit(1);
    }

    struct stat source_stat;
    struct stat destination_stat;

    stat(source, &source_stat);
    if(!S_ISDIR(source_stat.st_mode)) {
        printf("Source path \"\" doesn't exist or is not a directory.\n");

        print_danger("Exit error");
        exit(1);
    }

    stat(destination, &destination_stat);
    if(!S_ISDIR(destination_stat.st_mode)) {
        printf("Destination path \"%s\" is not a directory.\n", destination);

        printf("Create one at: \"%s\"? [Y/N] ", destination);
        char choice;
        scanf("%c", &choice);
        
        switch (choice) {
        case 'y':
            create_dir(destination);
            print_success("Directory created at:", destination);
            break;
        case 'Y':
            create_dir(destination);
            print_success("Directory created at:", destination);
            break;
        case 'n':
            print_warning("Abort");
            exit(1);
            break;
        case 'N':
            print_warning("Abort");
            exit(1);
            break;
        
        default:
            print_warning("Abort");
            exit(1);
            break;
        }
    }

    printf("\nAll good. ");
    print_success("Starting daemon.", "");

    stat(destination, &destination_stat);

    compare(source, destination, "", "", false, recursive);
    compare(destination, source, "", "", true, recursive);

    return 0;
}
