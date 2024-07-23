#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include "calc.h"

#define TRUE 1
#define FALSE 0

void clearIBuf() {
    while (getchar() != '\n');
}

void printMenu() {
    printf("---------------------\n"
            "Select an operation:\n"
            "1) Addition\n"
            "2) Subtraction\n"
            "3) Multiplication\n"
            "4) Division\n"
            "5) Exit\n");
}

int getIntInput(const char *prompt) {
    int num;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &num) != 1) {
            printf("Input error. Please try again.\n");
            clearIBuf();
        } else {
            clearIBuf();
            return num;
        }
    }
}

int main() {
    int choice, a, b, result;

    while (1) {
        printMenu();
        choice = getIntInput("Your choice: ");

        if (choice > 5 || choice < 1){
            printf("Invalid choice. Please try again.\n");
            continue;
        }
        
        if (choice == 5) {
            break;
        }

        a = getIntInput("Enter the first number: ");
        b = getIntInput("Enter the second number: ");

        errno = 0;
        int success = FALSE;

        switch (choice) {
            case 1:
                result = add(a, b);
                success = TRUE;
                break;
            case 2:
                result = sub(a, b);
                success = TRUE;
                break;
            case 3:
                result = mul(a, b);
                success = TRUE;
                break;
            case 4:
                result = div(a, b);
                if (errno == EDOM) {
                    printf("Error: division by zero!\n");
                } else {
                    success = TRUE;
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        if (success){
            printf("Result: %d\n", result);
        }
    }

    return 0;
}