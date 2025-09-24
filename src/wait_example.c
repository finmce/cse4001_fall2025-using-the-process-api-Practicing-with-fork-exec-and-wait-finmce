#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child running (PID %d)\n", getpid());
        sleep(2);
        printf("Child exiting with status 42\n");
        exit(42);
    } else {
        int status;
        waitpid(pid, &status, 0);
        printf("Parent: child exited with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}
