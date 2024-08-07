#include "myFileUtils.h"

void shorten_number(long long number, char *shortened, int max_length) {
    if (max_length <= 0) {
        shortened[0] = '\0';
        return;
    }

    const char *suffixes[] = {"", "k", "M", "G", "T"};
    size_t suffix_index = 0;

    char temp[32];
    snprintf(temp, sizeof(temp), "%lld", number);

    if (strlen(temp) <= (size_t)max_length) {
        snprintf(shortened, max_length + 1, "%s", temp);
        return;
    }

    while (number >= 1000 &&
           suffix_index < sizeof(suffixes) / sizeof(suffixes[0]) - 1) {
        number /= 1000;
        suffix_index++;
    }

    snprintf(temp, sizeof(temp), "%lld%s", number, suffixes[suffix_index]);

    if (strlen(temp) > (size_t)max_length) {
        snprintf(shortened, max_length + 1, "%.*s...", max_length - 3, temp);
    } else {
        snprintf(shortened, max_length + 1, "%s", temp);
    }
}