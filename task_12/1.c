#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Основная функция программы.
 *
 * Эта программа создает неименованный канал, порождает дочерний процесс,
 * записывает строку "Hi!" в канал и затем дочерний процесс читает
 * эту строку и выводит ее на экран.
 *
 * @return Возвращает 0 при успешном завершении, иначе 1.
 */
int main() {
    int pipefd[2]; /**< Массив для дескрипторов канала */
    pid_t cpid; /**< Переменная для идентификатора дочернего процесса */
    char buf[20]; /**< Буфер для чтения данных из канала */

    // Создание канала
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Создаем дочерний процесс
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {  // Дочерний процесс
        close(pipefd[1]);  // Закрываем дескриптор для записи

        // Читаем из канала
        ssize_t bytesRead = read(pipefd[0], buf, sizeof(buf));
        if (bytesRead == -1) {
            perror("read");
            close(pipefd[0]);  // Закрываем дескриптор для чтения
            exit(EXIT_FAILURE);
        }
        printf("Дочерний процесс прочитал: %s\n", buf);

        close(pipefd[0]);  // Закрываем дескриптор для чтения
        exit(EXIT_SUCCESS);
    } else {               // Родительский процесс
        close(pipefd[0]);  // Закрываем дескриптор для чтения

        // Записываем строку в канал
        const char *message = "Hi!";
        ssize_t bytesWritten = write(pipefd[1], message, strlen(message) + 1);
        if (bytesWritten == -1) {
            perror("write");
            close(pipefd[1]);  // Закрываем дескриптор для записи
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);  // Закрываем дескриптор для записи

        // Ожидание завершения дочернего процесса
        if (wait(NULL) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        printf("Родительский процесс завершен.\n");
    }

    exit(EXIT_SUCCESS);
}
