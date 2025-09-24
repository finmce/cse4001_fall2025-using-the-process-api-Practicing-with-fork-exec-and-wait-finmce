#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        close(STDOUT_FILENO);
        printf("This will not appear on screen!\n");
        exit(0);
    } else {
        wait(NULL);
        printf("Parent still has stdout open.\n");
    }

    return 0;
}
