#include "supplier.h"

extern Store stores[MAX_STORES];
extern Customer customers[MAX_CUSTOMERS];
extern int num_customers, num_stores;

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
void* supplier_thread(void* arg) {
    int supplier_id = *(int*)arg;
    while (1) {
        int all_satisfied = 1;
        for (int i = 0; i < num_customers; i++) {
            if (customers[i].need > 0) {
                all_satisfied = 0;
                break;
            }
        }
        if (all_satisfied) break;  // Выходим, если все удовлетворены

        for (int i = 0; i < num_stores; i++) {
            pthread_mutex_lock(&stores[i].mutex);  // Блокируем мьютекс магазина
            if (stores[i].stock < 5) {  // Проверяем уровень запасов
                int restock_amount = 5000;  // Количество для пополнения
                stores[i].stock += restock_amount;  // Обновляем запасы
                printf(
                    "Supplier %d restocked store %d with %d items. New stock: "
                    "%d\n",
                    supplier_id, i, restock_amount, stores[i].stock);
            }
            pthread_mutex_unlock(
                &stores[i].mutex);  // Освобождаем мьютекс магазина
        }
        sleep(1);  // Ждем перед следующей проверкой
    }
    return NULL;
}
