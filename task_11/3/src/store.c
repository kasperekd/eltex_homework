#include "store.h"

/**
 * @brief Инициализирует магазины с случайным запасом.
 *
 * Эта функция инициализирует каждый магазин с случайным количеством
 * товаров и создает мьютексы для синхронизации доступа к запасам.
 *
 * @param stores Указатель на массив магазинов.
 * @param num_stores Количество магазинов для инициализации.
 */
void initialize_stores(Store* stores, int num_stores) {
    for (int i = 0; i < num_stores; i++) {
        stores[i].stock =
            rand() % 1001 + 9500;  // Случайный запас от 9500 до 10500
        if (pthread_mutex_init(&stores[i].mutex, NULL) != 0) {
            perror("Failed to initialize store mutex");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * @brief Освобождает ресурсы, связанные с магазинами.
 *
 * Эта функция освобождает мьютексы, используемые магазинами.
 *
 * @param stores Указатель на массив магазинов.
 * @param num_stores Количество магазинов для очистки.
 */
void clean_stores(Store* stores, int num_stores) {
    for (int i = 0; i < num_stores; i++) {
        pthread_mutex_destroy(&stores[i].mutex);
    }
}
