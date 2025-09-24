#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child first
        printf("hello\n");
    } else {
        // Give child a head start
        sleep(1);
        printf("goodbye\n");
    }

    return 0;
}
