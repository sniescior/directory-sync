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

int main(int argc, char const *argv[])
{
    // Compare two directories side by side
    char* source = "katalog";
    char* destination = "katalog-sync";
    compare(source, destination, "", "");

    return 0;
}
