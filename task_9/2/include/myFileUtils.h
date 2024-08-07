#ifndef MY_FILE_UTILS_H
#define MY_FILE_UTILS_H

#include <stdio.h>
#include <string.h>

void shorten_name(const char *original, char *shortened, int max_length);
void shorten_number(long long number, char *shortened, int max_length);

#endif  // MY_FILE_UTILS_H