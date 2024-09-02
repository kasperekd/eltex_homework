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

#define MAX_INPUT_SIZE 1024  ///< Максимальный размер ввода
#define MAX_ARG_SIZE 100  ///< Максимальное количество аргументов

/**
 * @brief Основная функция командного интерпретатора.
 *
 * Эта функция реализует простой командный интерпретатор, который поддерживает
 * выполнение команд с пайпами. Пользователь может вводить команды, которые
 * будут выполняться в дочерних процессах. Поддерживается отладочный режим.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Возвращает EXIT_SUCCESS при нормальном завершении.
 */
int main(int argc, char *argv[]) {
    char input[MAX_INPUT_SIZE];  ///< Буфер для ввода команды
    char *args[MAX_ARG_SIZE];  ///< Массив для аргументов команды
    int debug_mode = 0;  ///< Флаг для отладочного режима

    // Проверка на наличие отладочного режима
    if (argc > 1 && strcmp(argv[1], "--debug") == 0) {
        debug_mode = 1;
    }

    while (1) {
        char cwd[PATH_MAX];  ///< Буфер для текущего рабочего каталога
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("shell: %s > ", cwd);  ///< Вывод текущего каталога
        } else {
            perror("getcwd() error");
            continue;
        }

        // Чтение ввода пользователя
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets failed");
            continue;
        }

        input[strcspn(input, "\n")] = 0;  ///< Удаление символа новой строки

        // Проверка на команду выхода
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Обработка пайпов
        char *pipe_pos = strchr(input, '|');
        if (pipe_pos != NULL) {
            *pipe_pos = '\0';           // Разделяем команды
            char *cmd1 = input;         ///< Первая команда
            char *cmd2 = pipe_pos + 1;  ///< Вторая команда

            // Токенизация первой команды
            int arg_count1 = 0;
            char *token = strtok(cmd1, " ");
            while (token != NULL && arg_count1 < MAX_ARG_SIZE - 1) {
                args[arg_count1++] = token;
                token = strtok(NULL, " ");
            }
            args[arg_count1] = NULL;

            // Создание пайпа
            int pipefd[2];
            if (pipe(pipefd) == -1) {
                perror("pipe failed");
                continue;
            }

            // Первый процесс
            pid_t pid1 = fork();
            if (pid1 < 0) {
                perror("fork failed");
                continue;
            } else if (pid1 == 0) {
                // Дочерний процесс 1
                dup2(pipefd[1], STDOUT_FILENO);  // Перенаправляем stdout в пайп
                close(pipefd[0]);  // Закрываем неиспользуемый
                close(pipefd[1]);
                execvp(args[0], args);
                perror("exec failed");
                exit(EXIT_FAILURE);
            }

            // Второй процесс
            pid_t pid2 = fork();
            if (pid2 < 0) {
                perror("fork failed");
                continue;
            } else if (pid2 == 0) {
                // Дочерний процесс 2
                dup2(pipefd[0], STDIN_FILENO);  // Перенаправляем stdin из пайпа
                close(pipefd[1]);  // Закрываем неиспользуемый
                close(pipefd[0]);

                // Токенизация второй команды
                int arg_count2 = 0;
                token = strtok(cmd2, " ");
                while (token != NULL && arg_count2 < MAX_ARG_SIZE - 1) {
                    args[arg_count2++] = token;
                    token = strtok(NULL, " ");
                }
                args[arg_count2] = NULL;

                execvp(args[0], args);
                perror("exec failed");
                exit(EXIT_FAILURE);
            }

            // Закрываем оба конца пайпа в родительском процессе
            close(pipefd[0]);
            close(pipefd[1]);

            // Ожидание завершения обоих процессов
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        } else {
            // Токенизация без пайпа
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
    }

    exit(EXIT_SUCCESS);  ///< Успешное завершение программы
}
