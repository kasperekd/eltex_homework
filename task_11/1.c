/**
 * @file 1.c
 * @brief Пример создания потоков с заданными индексами и их вывод на экран.
 *
 * Данная программа создает несколько потоков, каждый из которых выводит свой
 * индекс на экран. Используется библиотека pthread для работы с потоками.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5 /**< Количество потоков для создания */

/**
 * @brief Функция, выполняемая каждым потоком.
 *
 * Эта функция принимает указатель на индекс потока, выводит его значение на
 * экран.
 *
 * @param index Указатель на целочисленный индекс потока.
 * @return NULL Указывает на завершение выполнения функции.
 */
void *some_function(void *index) {
    int *num = (int *)index; /**< Приведение указателя к целочисленному типу */
    printf("%d\n", *num);    /**< Вывод индекса на экран */
    return NULL;             /**< Завершение функции */
}

/**
 * @brief Главная функция программы.
 *
 * В этой функции создаются потоки и ожидается их завершение.
 *
 * @return Возвращает 0 при успешном завершении программы.
 */
int main() {
    pthread_t thread[N]; /**< Массив потоков */
    int args[N]; /**< Массив аргументов для потоков */

    for (size_t i = 0; i < N; i++) {
        args[i] = i; /**< Инициализация аргументов */
        pthread_create(&thread[i], NULL, some_function,
                       (void *)&(args[i])); /**< Создание потока */
    }
    for (size_t i = 0; i < N; i++) {
        pthread_join(thread[i], NULL); /**< Ожидание завершения потоков */
    }

    exit(EXIT_SUCCESS); /**< Завершение программы */
}