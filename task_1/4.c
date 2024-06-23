#include <stdio.h>
#include <stdlib.h>

int getInteger(int *num) {
    int try_count = 0;
    int c = 0;

    while (1) {
        if ((scanf("%d", num) == 1) && (*num > 0)) {
            break;
        }

        try_count++;

        if (try_count < 3) {
            printf("\nInvalid number entered, try again\n> ");
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            printf("\nToo many failed input attempts\n");
            exit(1);
        }
    }

    return 0;
}

void getBinRep(int num, char *buf, int buf_size) {
    int int_size = sizeof(int) * 8;

    if (buf_size < int_size + 1) {
        printf("Buffer size is too small for binary representation\n");
        return;
    }

    buf[int_size] = '\0';

    for (int i = 0; i < int_size; i++) {
        buf[int_size - 1 - i] = ((num >> i) & 1) + '0';
    }
}

int main() {
    int mask = 0xFF00FFFF;
    
    int num = 0;
    int to_change = 0;
    printf("\nEnter a positive integer\n> ");
    getInteger(&num);

    printf("Enter a number to replace the third byte with\n> ");
    getInteger(&to_change);

    if (to_change < 0 || to_change > 255) {
        printf("Please enter a number between 0 and 255.\n");
        return 1;
    }

    num = (num & mask) | (to_change << 16);

    printf("Modified number: %d\n", num);

    char buf[sizeof(int) * 8 + 1];
    getBinRep(num, buf, sizeof(buf));
    printf("Binary representation of the modified number: %s\n", buf);

    return 0;
}
