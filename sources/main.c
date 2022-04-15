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
    // Compare two directories side by side
    char* source = "katalog";
    char* destination = "katalog-sync";
    compare(source, destination, "", "", false);
    compare(destination, source, "", "", true);

    // printf("\n\nSecond loop:\n\n");
    // Reverse loop to delete all files and directories that are only in (b) directory
    // compare(destination, source, "", "", true);

    return 0;
}
