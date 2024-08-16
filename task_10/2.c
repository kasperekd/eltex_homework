#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void create_process1() {
    __pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork fail");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {  // 1
        printf("Process1 - pid: %d\tppid: %d\n", getpid(), getppid());

        __pid_t pid3 = fork();
        if (pid3 == -1) {
            perror("fork fail");
            exit(EXIT_FAILURE);
        } else if (pid3 == 0) {  // 3
            printf("Process3 - pid: %d\tppid: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }

        __pid_t pid4 = fork();
        if (pid4 == -1) {
            perror("fork fail");
            exit(EXIT_FAILURE);
        } else if (pid4 == 0) {  // 4
            printf("Process4 - pid: %d\tppid: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }

        // wait 3, 4
        waitpid(pid3, NULL, 0);
        waitpid(pid4, NULL, 0);
        exit(EXIT_SUCCESS);
    }
}

void create_process2() {
    __pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork fail");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {  // 2
        printf("Process2 - pid: %d\tppid: %d\n", getpid(), getppid());

        __pid_t pid5 = fork();
        if (pid5 == -1) {
            perror("fork fail");
            exit(EXIT_FAILURE);
        } else if (pid5 == 0) {  // 5
            printf("Process5 - pid: %d\tppid: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }

        // wait 5
        waitpid(pid5, NULL, 0);
        exit(EXIT_SUCCESS);
    }
}

int main() {
    create_process1();
    create_process2();

    // wait 1, 2
    wait(NULL);
    wait(NULL);

    return EXIT_SUCCESS;
}