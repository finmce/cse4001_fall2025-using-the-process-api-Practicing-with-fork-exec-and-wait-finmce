#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("About to exec 'ls -l'...\n");

    char *args[] = { "ls", "-l", NULL };

    if (execvp(args[0], args) == -1) {
        perror("execvp failed");
        exit(1);
    }

    printf("This should not print!\n");
    return 0;
}
