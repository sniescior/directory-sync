#ifndef DIRECTORY_HANDLER_H_
#define DIRECTORY_HANDLER_H_

#include <stdbool.h>

// Directory handler - duplicate / remove (if needed)

void create_dir(char* path);
void delete_dir(char* destination);
void dir_handle(char* source, char* destination, bool reverse);

#endif