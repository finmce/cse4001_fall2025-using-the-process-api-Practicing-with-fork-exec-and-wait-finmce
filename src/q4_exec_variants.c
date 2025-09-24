#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child replaces itself with /bin/ls
        char *args[] = { "ls", "-l", NULL };

        // Try one at a time by uncommenting:
        // execl("/bin/ls", "ls", "-l", NULL);
        // execle("/bin/ls", "ls", "-l", NULL, environ);
        // execlp("ls", "ls", "-l", NULL);
        // execv("/bin/ls", args);
        execvp("ls", args);
        // execvpe("ls", args, environ);

        perror("exec failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent: child finished exec()\n");
    }

    return 0;
}
