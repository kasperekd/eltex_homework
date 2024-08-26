#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "store.h"

#if !defined(MAX_CUSTOMERS)
#define MAX_CUSTOMERS 10
#endif  // MAX_CUSTOMERS

/**
 * @brief Структура, представляющая покупателя.
 */
typedef struct {
    int need; /**< Потребность покупателя в товарах. */
    pthread_mutex_t
        mutex; /**< Мьютекс для синхронизации доступа к потребности. */
} Customer;

extern Store stores[MAX_STORES];
extern Customer customers[MAX_CUSTOMERS];
extern int num_stores;

/**
 * @brief Инициализирует покупателей с случайной потребностью.
 *
 * @param customers Указатель на массив покупателей.
 * @param num_customers Количество покупателей для инициализации.
 */
void initialize_customers(Customer* customers, int num_customers);

/**
 * @brief Функция потока покупателя.
 *
 * Эта функция выполняется в контексте потока покупателя. Она
 * пытается купить товары из магазинов, пока потребность покупателя
 * не будет удовлетворена.
 *
 * @param arg Указатель на структуру Customer.
 * @return NULL
 */
void* customer_thread(void* arg);

#endif  // CUSTOMER_H
