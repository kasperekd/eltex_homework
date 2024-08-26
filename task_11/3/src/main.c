#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STORES 10
#define MAX_CUSTOMERS 10
#define MAX_SUPPLIERS 10

#include "customer.h"
#include "store.h"
#include "supplier.h"
#include "utils.h"

Store stores[MAX_STORES];          /**< Массив магазинов. */
Customer customers[MAX_CUSTOMERS]; /**< Массив покупателей. */
int supplier_ids[MAX_SUPPLIERS]; /**< Массив идентификаторов поставщиков. */
int num_stores, num_customers,
    num_suppliers; /**< Количество магазинов, покупателей и поставщиков. */

/**
 * @brief Освобождает ресурсы, включая мьютексы для магазинов и покупателей.
 */
void clean() {
    clean_stores(stores, num_stores);
    for (int i = 0; i < num_customers; i++) {
        pthread_mutex_destroy(&customers[i].mutex);
    }
    printf("Cleaned up resources.\n");
}

/**
 * @brief Создает потоки для клиентов и поставщиков.
 *
 * Эта функция создает потоки для обработки клиентов и поставщиков.
 * Для каждого клиента и поставщика создается отдельный поток, который выполняет
 * соответствующую функцию обработки.
 *
 * @param customer_threads Указатель на массив потоков клиентов.
 * @param supplier_threads Указатель на массив потоков поставщиков.
 *
 * @note В случае неудачи при создании потока, функция выводит сообщение об
 * ошибке и завершает выполнение программы с кодом ошибки EXIT_FAILURE.
 *
 * @warning Убедитесь, что массивы customer_threads и supplier_threads имеют
 *          достаточный размер для хранения всех потоков.
 */
void create_threads(pthread_t* customer_threads, pthread_t* supplier_threads) {
    for (int i = 0; i < num_customers; i++) {
        if (pthread_create(&customer_threads[i], NULL, customer_thread,
                           (void*)&customers[i]) != 0) {
            perror("Failed to create customer thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_suppliers; i++) {
        supplier_ids[i] = i;  // уникальный id
        if (pthread_create(&supplier_threads[i], NULL, supplier_thread,
                           (void*)(&supplier_ids[i])) != 0) {
            perror("Failed to create supplier thread");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * @brief Главная функция программы.
 *
 * Эта функция обрабатывает аргументы командной строки, инициализирует
 * магазины и покупателей, создает потоки и ожидает их завершения.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return 0 при успешном завершении, иначе код ошибки.
 */
int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr,
                "Usage: %s <num_stores> <num_customers> <num_suppliers>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!is_positive_integer(argv[1]) || !is_positive_integer(argv[2]) ||
        !is_positive_integer(argv[3])) {
        fprintf(stderr, "Error: All arguments must be positive integers.\n");
        exit(EXIT_FAILURE);
    }

    num_stores = atoi(argv[1]);
    num_customers = atoi(argv[2]);
    num_suppliers = atoi(argv[3]);

    if (num_stores > MAX_STORES || num_customers > MAX_CUSTOMERS ||
        num_suppliers > MAX_SUPPLIERS) {
        fprintf(stderr,
                "Error: Number of stores, customers, or suppliers exceeds "
                "maximum limit.\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));  // Инициализируем генератор случайных чисел

    atexit(clean);  // Регистрируем функцию очистки ресурсов

    initialize_stores(stores, num_stores);  // Инициализируем магазины
    initialize_customers(customers,
                         num_customers);  // Инициализируем покупателей

    pthread_t customer_threads[MAX_CUSTOMERS];  // Массив потоков покупателей
    pthread_t supplier_threads[MAX_SUPPLIERS];  // Массив потоков поставщиков

    create_threads(customer_threads, supplier_threads);  // Создаем потоки

    // Ожидаем завершения потоков покупателей
    for (int i = 0; i < num_customers; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    // Ожидаем завершения потоков поставщиков
    for (int i = 0; i < num_suppliers; i++) {
        pthread_join(supplier_threads[i], NULL);
    }

    printf("All customers satisfied.\n");
    exit(EXIT_SUCCESS);
}
