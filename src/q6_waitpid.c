#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child running...\n");
        sleep(2);
        exit(7);
    } else {
        int status;
        pid_t w = waitpid(pid, &status, 0);
        printf("Parent: waitpid() returned PID=%d, status=%d\n", w, WEXITSTATUS(status));
    }

    return 0;
}
