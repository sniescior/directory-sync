#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

void daemon_skeleton() {
    pid_t pid;
    pid = fork();
    if(pid < 0) {
        exit(1);
    }

    if(pid > 0) {
        // Exit parent process
        exit(0);
    }

    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close(x);
    }

    openlog ("dir-sync", LOG_PID, LOG_DAEMON);
}