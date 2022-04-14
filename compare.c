#include "compare.h"
#include "destination_path.h"
#include "directory_handler.h"
#include "file_handler.h"
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

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