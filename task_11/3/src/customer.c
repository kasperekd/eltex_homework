#include "customer.h"

/**
 * @brief Функция потока покупателя.
 *
 * Эта функция выполняется в контексте потока покупателя. Она
 * пытается купить товары из магазинов, пока потребность покупателя
 * не будет удовлетворена. Покупатель проверяет каждый магазин и
 * покупает товары, если они доступны.
 *
 * @param arg Указатель на структуру Customer.
 * @return NULL
 */
void* customer_thread(void* arg) {
    Customer* customer = (Customer*)arg;
    int customer_id = customer - customers; /**< Получаем индекс покупателя. */
    while (customer->need > 0) {
        for (int i = 0; i < num_stores; i++) {
            pthread_mutex_lock(&stores[i].mutex);  // Блокируем мьютекс магазина
            if (stores[i].stock > 0 && customer->need > 0) {
                // Определяем количество товаров для покупки
                int purchase_amount = (stores[i].stock < customer->need)
                                          ? stores[i].stock
                                          : customer->need;

                // Обновляем запасы магазина и потребности покупателя
                stores[i].stock -= purchase_amount;
                customer->need -= purchase_amount;

                printf(
                    "Customer %d bought %d items from store %d. Remaining "
                    "need: %d\n",
                    customer_id, purchase_amount, i, customer->need);
            }
            pthread_mutex_unlock(
                &stores[i].mutex);  // Освобождаем мьютекс магазина
        }
        sleep(2);  // Ждем перед следующей попыткой
    }
    return NULL;
}

/**
 * @brief Инициализирует покупателей с случайной потребностью.
 *
 * Эта функция инициализирует каждого покупателя с случайной
 * потребностью в товарах и создает мьютексы для синхронизации
 * доступа к потребностям.
 *
 * @param customers Указатель на массив покупателей.
 * @param num_customers Количество покупателей для инициализации.
 */
void initialize_customers(Customer* customers, int num_customers) {
    for (int i = 0; i < num_customers; i++) {
        customers[i].need = rand() % 10001 + 95000;  // потребность
        if (pthread_mutex_init(&customers[i].mutex, NULL) != 0) {
            perror("Failed to initialize customer mutex");
            exit(EXIT_FAILURE);
        }
    }
}
