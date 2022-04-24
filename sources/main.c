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

int main(int argc, char const *argv[])
{
    char* source;
    char* destination;

    if(argc < 3) {
        printf("Not enough arguments. Note that the program should receive at least path to source and destination directory.\n");
        printf("Read the documentation.\n");

        printf("\033[1;31m");
        printf("Exit error\n");

        exit(1);
    }

    source = strdup(argv[1]);
    destination = strdup(argv[2]);

    struct stat source_stat;
    struct stat destination_stat;

    stat(source, &source_stat);
    if(!S_ISDIR(source_stat.st_mode)) {
        printf("Source path \"\" doesn't exist or is not a directory.\n");

        printf("\033[1;31m");
        printf("Exit error\n");
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
            printf("\033[0;32m");
            create_dir(destination);
            printf("Directory created at: \"%s\".\n", destination);
            printf("\033[0;30m");
            break;
        case 'Y':
            printf("\033[0;32m");
            create_dir(destination);
            printf("Directory created at: \"%s\".\n", destination);
            printf("\033[0;30m");
            break;
        case 'n':
            printf("\033[0;33m");
            printf("Abort\n");
            printf("\033[0;30m");
            exit(1);
            break;
        case 'N':
            printf("\033[0;33m");
            printf("Abort\n");
            printf("\033[0;30m");
            exit(1);
            break;
        
        default:
            printf("\033[0;33m");
            printf("Abort\n");
            printf("\033[0;30m");
            exit(1);
            break;
        }
    }

    printf("\nStarting daemon\n");

    stat(destination, &destination_stat);

    compare(source, destination, "", "", false);
    compare(destination, source, "", "", true);

    // printf("\n\nSecond loop:\n\n");
    // Reverse loop to delete all files and directories that are only in (b) directory
    // compare(destination, source, "", "", true);

    return 0;
}
