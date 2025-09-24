#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Parent (PID %d) starting...\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());
    } else {
        printf("Parent process: created child with PID=%d\n", pid);
    }

    return 0;
}
