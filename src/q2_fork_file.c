#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child writes
        const char *msg = "Child writing\n";
        write(fd, msg, strlen(msg));
    } else {
        // Parent writes
        const char *msg = "Parent writing\n";
        write(fd, msg, strlen(msg));
    }

    close(fd);
    return 0;
}

