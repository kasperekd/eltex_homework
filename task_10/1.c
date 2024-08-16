#include <stdio.h>
#include <stdlib.h>
// #include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    __pid_t pid;

    switch (pid = fork()) {
        case -1:  // Err
            perror("fork fail");
            exit(EXIT_FAILURE);
            break;
        case 0:  // child
            printf("Child - pid: %d\tppid: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
            break;
        default:  // parent
            printf("Parent - pid: %d\tppid: %d\n", getpid(), getppid());

            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                printf("Child exit code: %d\n", WIFEXITED(status));
            } else {
                printf("Child exit failed\n");
            }
            break;
    }

    return EXIT_SUCCESS;
}