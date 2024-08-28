#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_NAME "my_channel" /**< Имя именованного канала */

/**
 * @brief Основная функция сервера.
 *
 * Эта функция создает именованный канал, открывает его на запись,
 * записывает строку "Hi!".
 *
 * @return Возвращает 0 при успешном завершении, иначе 1.
 */
int main() {
    // Создание именованного канала
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Открытие канала на запись
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Запись строки в канал
    const char *message = "Hi!";
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Закрытие канала
    close(fd);

    // Завершение работы сервера
    exit(EXIT_SUCCESS);
}