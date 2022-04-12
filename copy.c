#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

// https://stackoverflow.com/questions/59602852/permission-denied-in-open-function-in-c

void read_file() {
    int fd, sz; 
    char *c = (char *) calloc(1, sizeof(char)); 
  
    fd = open("foo.txt", O_RDONLY);
    if (fd < 0) { perror("r1"); exit(1); }
    
    while(sz = read(fd, c, 1) > 0) { 
        printf("%s", c);
    }

    printf("\n");
}

int main(int argc, char const *argv[])
{
    int fd, fd_copy, sz, sz_copy;
    char *c = (char *) calloc(1, sizeof(char)); 
  
    fd = open("foo.txt", O_RDONLY);
    if (fd < 0) { perror("r1"); exit(1); }

    fd_copy = open(
        "foo-kopia.txt", 
        O_WRONLY | O_CREAT | O_TRUNC, 
        0644
    );
    if (fd_copy < 0) { perror("r2"); exit(1); }

    while(sz = read(fd, c, 1) > 0) { 
        // printf("%s", c);
        write(fd_copy, c, strlen(c));
    }

    printf("\n");

    return 0;
}
