#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child exiting with status 42\n");
        exit(42);
    } else {
        int status;
        pid_t w = wait(&status);
        printf("Parent: wait() returned PID=%d, status=%d\n", w, WEXITSTATUS(status));
    }

    return 0;
}
