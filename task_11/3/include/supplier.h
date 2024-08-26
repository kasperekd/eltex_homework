#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "customer.h"
#include "store.h"

/**
 * @brief Функция потока поставщика.
 *
 * Эта функция выполняется в контексте потока поставщика. Она
 * проверяет, удовлетворены ли потребности всех покупателей. Если
 * нет, поставщик пополняет запасы в магазинах, если они ниже
 * определенного уровня.
 *
 * @param arg Указатель на идентификатор поставщика.
 * @return NULL
 */
void* supplier_thread(void* arg);

#endif  // SUPPLIER_H
