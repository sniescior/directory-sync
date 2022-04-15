#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <stdbool.h>

// Regular file handler - duplicate / remove (if needed)

void duplicate_file(char *source, char* destination);
void delete_file(char* path);
void file_handle(char* source, char* destination, bool reverse);

#endif