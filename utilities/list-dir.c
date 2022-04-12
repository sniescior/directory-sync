#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_dir(char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {

        char path[1024];
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            listdir(path, indent + 2);
            printf("%s/%s  --  %s -- \n", name, entry->d_name, path);
            unlink(path);
            rmdir(path);
        } else {
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%s/%s -- %s -- \n", name, entry->d_name, path);
            remove(path);
        }
    }
    closedir(dir);
}

int main(void) {
    remove_dir("katalog", 0);
    return 0;
}