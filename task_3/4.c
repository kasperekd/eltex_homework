#include <stdio.h>

#define MAX_STRING_SIZE 256

void remNewline(char* str) {
    while (*str) {
        if (*str == '\n') {
            *str = '\0';
            return;
        }
        str++;
    }
}

char* findSub(char* str, char* substr) {
    if (*substr == '\0') return str;

    char *p1 = str, *p2;
    
    while (*p1) {
        p2 = substr;
        char *p1_begin = p1;
        while (*p1 && *p2 && *p1 == *p2) {
            p1++;
            p2++;
        }
        if (*p2 == '\0') {
            return p1_begin;
        }
        p1 = p1_begin + 1;
    }
    return NULL;
}

int isEmpty(char* str) {
    return str[0] == '\0';
}

int stringLen(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main() {
    char str[MAX_STRING_SIZE];
    char substr[MAX_STRING_SIZE];

    printf("Enter the main string: ");
    fgets(str, MAX_STRING_SIZE, stdin);
    remNewline(str);

    if (isEmpty(str)) {
        printf("Error: Main string is empty.\n");
        return 1;
    }
    
    printf("Enter the substring: ");
    fgets(substr, MAX_STRING_SIZE, stdin);
    remNewline(substr);

    if (isEmpty(substr)) {
        printf("Error: Substring is empty.\n");
        return 1;
    }

    if (stringLen(substr) > stringLen(str)) {
        printf("Error: Substring is longer than the main string.\n");
        return 1;
    }
    
    char* result = findSub(str, substr);
    
    if (result != NULL) {
        printf("Substring found at address: %p\n", (void*)result);
        printf("Substring starts with: \"%s\"\n", result);
    } else {
        printf("Substring not found.\n");
    }
    
    return 0;
}
