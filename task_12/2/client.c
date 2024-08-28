#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO_NAME "my_channel" /**< Имя именованного канала */

/**
 * @brief Основная функция клиента.
 *
 * Эта функция открывает именованный канал на чтение,
 * считывает строку из канала и выводит ее на экран, и удаляет канал перед
 * завершением.
 *
 * @return Возвращает 0 при успешном завершении, иначе 1.
 */
int main() {
    // Открытие канала на чтение
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Чтение строки из канала
    char buf[20];
    if (read(fd, buf, sizeof(buf)) == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Вывод прочитанной строки
    printf("Клиент прочитал: %s\n", buf);

    // Закрытие канала
    close(fd);

    // Удаление именованного канала
    if (unlink(FIFO_NAME) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
