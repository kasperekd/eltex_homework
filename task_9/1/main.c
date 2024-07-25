#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    // Запись
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing: %s\n", strerror(errno));
        return 1;
    }

    const char *text = "String from file";
    if (fputs(text, file) == EOF) {
        fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
        fclose(file);
        return 1;
    }

    if (fclose(file) != 0) {
        fprintf(stderr, "Error closing the file: %s\n", strerror(errno));
        return 1;
    }

    // Чтение ...
    file = fopen("output.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading: %s\n", strerror(errno));
        return 1;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fprintf(stderr, "Error seeking in file: %s\n", strerror(errno));
        fclose(file);
        return 1;
    }
    long file_size = ftell(file);
    if (file_size == -1) {
        fprintf(stderr, "Error getting file size: %s\n", strerror(errno));
        fclose(file);
        return 1;
    }

    // ... с конца
    for (long i = file_size - 1; i >= 0; i--) {
        if (fseek(file, i, SEEK_SET) != 0) {
            fprintf(stderr, "Error seeking in file: %s\n", strerror(errno));
            fclose(file);
            return 1;
        }
        int c = fgetc(file);
        if (c == EOF) {
            if (ferror(file)) {
                fprintf(stderr, "Error reading from file: %s\n", strerror(errno));
            }
            break;
        }
        putchar(c);
    }

    putchar('\n');
    
    if (fclose(file) != 0) {
        fprintf(stderr, "Error closing the file: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
