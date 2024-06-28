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

int main() {   
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

    char* ptr = (char*) &num;
    ptr +=2; // {0000 0000}(3) {0000 0000}(2) {0000 0000}(1) {0000 0000}(0)
    *ptr = to_change;

    printf("Modified number: %d\n", num);
    return 0;
}