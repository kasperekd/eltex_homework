#include "myFileUtils.h"

void shorten_name(const char *original, char *shortened, int max_length) {
    int len = strlen(original);
    if (len <= max_length) {
        snprintf(shortened, max_length + 1, "%s", original);
    } else {
        int part_len = (max_length - 2) / 2;
        snprintf(shortened, max_length + 1, "%.*s~%s", part_len, original,
                 original + len - part_len);
    }
}