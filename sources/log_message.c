#include "../headers/log_message.h"
#include <syslog.h>
#include <stdlib.h>

void log_remove_directory(char* path, int error_code) {
    if(error_code != 0) {
        syslog(LOG_NOTICE, "Directory removing from: \"%s\" FAILED with error code: %d.", path, error_code);
    } else {
        syslog(LOG_NOTICE, "Directory removed from: \"%s\".", path);
    }
}

void log_create_directory(char* path, int error_code) {
    if(error_code != 0) {
        syslog(LOG_NOTICE, "Created directory at: \"%s\" FAILED with error code: %d.", path, error_code);
    } else {
        syslog(LOG_NOTICE, "Created directory at: \"%s\".", path);
    }
}

void log_remove_file(char* path, int error_code) {
    if (error_code != 0) {
        syslog(LOG_NOTICE, "File removing from: \"%s\" FAILED with error code: %d", path, error_code);
    } else {
        syslog(LOG_NOTICE, "File removed from: \"%s\".", path);
    }
    
}

void log_copy_file(char* source, char* destination, int error_code) {
    if(error_code != 0) {
        syslog(LOG_NOTICE, "Copying file from \"%s\" to \"%s\" FAILED with error code: %d.", source, destination, error_code);
    } else {
        syslog(LOG_NOTICE, "Copied file from \"%s\" to \"%s\".", source, destination);
    }
}