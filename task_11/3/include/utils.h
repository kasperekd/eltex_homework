#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>

/**
 * @brief Проверяет, является ли строка положительным целым числом.
 *
 * Эта функция проверяет, состоит ли строка только из цифр.
 *
 * @param str Указатель на строку.
 * @return 1, если строка является положительным целым числом, иначе 0.
 */
int is_positive_integer(const char* str);

#endif  // UTILS_H
