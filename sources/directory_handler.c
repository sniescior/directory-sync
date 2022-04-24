#include "../headers/directory_handler.h"
#include "../headers/log_message.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fts.h>
#include <errno.h>
#include <syslog.h>

void create_dir(char *path) {
    // printf("Create directory at: \"%s\"", path);
    log_create_directory(path);
    mkdir(path, 0700);
}

void delete_dir(char* dir) {

    log_remove_directory(dir);
    // printf("Delete directory from: \"%s\"", dir);

    int ret = 0;
    FTS *ftsp = NULL;
    FTSENT *curr;

    char *files[] = { (char *) dir, NULL };

    ftsp = fts_open(files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
    if (!ftsp) {
        ret = -1;
        goto finish;
    }

    while ((curr = fts_read(ftsp))) {
        switch (curr->fts_info) {
        case FTS_NS:
        case FTS_DNR:
        case FTS_ERR:
            break;

        case FTS_DC:
        case FTS_DOT:
        case FTS_NSOK:
            break;

        case FTS_D:
            break;

        case FTS_DP:
        case FTS_F:
        case FTS_SL:
        case FTS_SLNONE:
        case FTS_DEFAULT:
            if (remove(curr->fts_accpath) < 0) {
                ret = -1;
            }
            break;
        }
    }

finish:
    if (ftsp) {
        fts_close(ftsp);
    }
}

void dir_handle(char* source, char* destination, bool reverse) {
    // Creates a directory at given path

    DIR *t_directory;

    t_directory = opendir(destination);
    if(t_directory == NULL) {
        // Directory only exists in source path

        if(!reverse) {
            create_dir(destination);
        } else {
            delete_dir(source);
        }
        return;
    }
}