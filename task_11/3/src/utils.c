#include "utils.h"

/**
 * @brief Проверяет, является ли строка положительным целым числом.
 *
 * Эта функция проверяет, состоит ли строка только из цифр.
 *
 * @param str Указатель на строку.
 * @return 1, если строка является положительным целым числом, иначе 0.
 */
int is_positive_integer(const char* str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;  // Если встречается нецифровой символ, возвращаем 0
        }
        str++;
    }
    return 1;  // Все символы - цифры
}