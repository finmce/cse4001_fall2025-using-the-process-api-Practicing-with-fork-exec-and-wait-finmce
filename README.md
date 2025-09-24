# Assignment: Practicing the Process API
Practicing with fork, exec, wait. 

### Overview

In this assignment, you will practice using the Process API to create processes and run programs under Linux. The goal is to gain hands-on experience with system calls related to process management. Specifically, you will practice using the unix process API functions 'fork()', 'exec()', 'wait()', and 'exit()'. 

⚠️ Note: This is not an OS/161 assignment. You will complete it directly on Linux. 

Use the Linux in your CSE4001 container. If you are using macOS, you may use the Terminal (you may need to install development tools with C/C++ compilers). 

**Reference Reading**: Arpaci-Dusseau, *Operating Systems: Three Easy Pieces*, Chapter 5 (Process API Basics)
 👉 [Chapter 5 PDF](http://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf)

---

### **Steps to Complete the Assignment**

1. **Accept the GitHub Classroom Invitation**
    [GitHub Link](https://classroom.github.com/a/FZh4BrQG)
2. **Set up your Repository**
   - Clone the assignment repository.
3. **Study the Reference Materials**
   - Read **Chapter 5**.
   - Download and explore the sample programs from the textbook repository:
      [OSTEP CPU API Code](https://github.com/remzi-arpacidusseau/ostep-code/tree/master/cpu-api).
4. **Write Your Programs**
   - Adapt the provided example code to answer the assignment questions.
   - Each program should be clear, well-commented, and compile/run correctly.
   - Add your solution source code to the repository.

5. **Prepare Your Report**
   - Answer the questions in the README.md file. You must edit the README.md file and not create another file with the answers. 
   - For each question:
     - Include your **code**.
     - Provide your **answer/explanation**.
6. **Submit Your Work via GitHub**
   - Push both your **program code** to your assignment repository.
   - This push will serve as your submission.
   - Make sure all files, answers, and screenshots are uploaded and rendered properly.








---
### Questions
1. Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?


```cpp
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int x = 100;
    printf("Before fork: PID %d, x=%d\n", getpid(), x);

    pid_t pid = fork();

    if (pid == 0) {
        // Child
        printf("Child: initial x=%d\n", x);
        x = 200;
        printf("Child: changed x=%d\n", x);
    } else {
        // Parent
        printf("Parent: initial x=%d\n", x);
        x = 300;
        printf("Parent: changed x=%d\n", x);
    }

    return 0;
}
//Each process has its own copy of memory after fork(). Changing x in the child doesnt effect the parent, and vice versa.
// Add your code or answer here. You can also add screenshots showing your program's execution.  
```


2. Write a program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently, i.e., at the same time?

```cpp
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
//File descriptors are shared after fork(). Both processes can write to the same file, but writes may interleave if not synchronized.
// Add your code or answer here. You can also add screenshots showing your program's execution.  
```

3. Write another program using `fork()`.The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling `wait()` in the parent?

```cpp
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
//Without wait(), we can still influence order by delaying the parent (sleep), though it isnt as reliable as wait()
// Add your code or answer here. You can also add screenshots showing your program's execution.  
```


4. Write a program that calls `fork()` and then calls some form of `exec()` to run the program `/bin/ls`. See if you can try all of the variants of `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, and `execvpe()`. Why do you think there are so many variants of the same basic call?

```cpp
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
//Different exec*() functions vary in how you pass the program name, args, and environment.
// Add your code or answer here. You can also add screenshots showing your program's execution.  
```

5. Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

```cpp
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
//wait() returns the PID of the finished child and stores its exit code in status. If called in the child, it fails
// Add your code or answer here. You can also add screenshots showing your program's execution.  
```

6. Write a slight modification of the previous program, this time using `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

```cpp
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
//waitpid() is useful when you want to wait for a specific child
// Add your code or answer here. You can also add screenshots showing your program's execution.  
```

7. Write a program that creates a child process, and then in the child closes standard output (`STDOUT FILENO`). What happens if the child calls `printf()` to print some output after closing the descriptor?

```cpp
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
//Closing STDOUT_FILENO in the child means calls to printf() silently fail Add your code or answer here. You can also add screenshots showing your program's execution.  
```

