#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#if !defined(PATH_MAX)
#define PATH_MAX 1024
#endif  // PATH_MAX

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

int main(int argc, char *argv[]) {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    int debug_mode = 0;

    // Отладка
    if (argc > 1 && strcmp(argv[1], "--debug") == 0) {
        debug_mode = 1;
    }

    while (1) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("shell: %s > ", cwd);
        } else {
            perror("getcwd() error");
            continue;
        }

        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets failed");
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Токенизация
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL && arg_count < MAX_ARG_SIZE - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        // Новый процесс
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            continue;
        } else if (pid == 0) {
            // Дочерний процесс
            if (debug_mode) {
                printf("Debug: Child PID: %d, Parent PID: %d\n", getpid(),
                       getppid());
            }
            execvp(args[0], args);
            perror("exec failed");
            exit(EXIT_FAILURE);
        } else {
            // Родительский процесс
            if (debug_mode) {
                printf("Debug: Parent PID: %d\n", getpid());
            }
            int status;
            waitpid(pid, &status, 0);  // Ожидание завершения
        }
    }

    return EXIT_SUCCESS;
}
