#include "../headers/log_message.h"
#include <syslog.h>
#include <stdlib.h>

void log_remove_directory(char* path) {
    syslog(LOG_NOTICE, "Directory removed from: \"%s\".", path);
}

void log_create_directory(char* path) {
    syslog(LOG_NOTICE, "Created directory at: \"%s\".", path);
}

void log_remove_file(char* path) {
    syslog(LOG_NOTICE, "File removed from: \"%s\".", path);
}

void log_copy_file(char* source, char* destination) {
    syslog(LOG_NOTICE, "Copied file from \"%s\" to \"%s\".", source, destination);
}