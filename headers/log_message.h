#ifndef LOG_MESSAGE_H_
#define LOG_MESSAGE_H_

void log_remove_directory(char* path);
void log_create_directory(char* path);
void log_remove_file(char* path);
void log_copy_file(char* source, char* destination);

#endif