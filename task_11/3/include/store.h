#ifndef STORE_H
#define STORE_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if !defined(MAX_STORES)
#define MAX_STORES 10
#endif  // MAX_STORES 10

/**
 * @brief Структура, представляющая магазин.
 */
typedef struct {
    int stock; /**< Текущий запас товаров в магазине. */
    pthread_mutex_t mutex; /**< Мьютекс для синхронизации доступа к запасу. */
} Store;

/**
 * @brief Инициализирует магазины с случайным запасом.
 *
 * @param stores Указатель на массив магазинов.
 * @param num_stores Количество магазинов для инициализации.
 */
void initialize_stores(Store* stores, int num_stores);

/**
 * @brief Освобождает ресурсы, связанные с магазинами.
 *
 * @param stores Указатель на массив магазинов.
 * @param num_stores Количество магазинов для очистки.
 */
void clean_stores(Store* stores, int num_stores);

#endif  // STORE_H
