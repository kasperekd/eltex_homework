#include <stdio.h>
#include <string.h>

#define MAX_ABONENTS 2

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
};

struct abonent phonebook[MAX_ABONENTS];

void initPB() {
    for (int i = 0; i < MAX_ABONENTS; i++) {
        strcpy(phonebook[i].name, "");
        strcpy(phonebook[i].second_name, "");
        strcpy(phonebook[i].tel, "");
    }
}

void clearIBuf() {
    while (getchar() != '\n');
}

void addAbonent() {
    for (int i = 0; i < MAX_ABONENTS; i++) {
        if (strcmp(phonebook[i].name, "") == 0) {
            printf("Enter name (max 9 characters): ");
            if (scanf("%9s", phonebook[i].name) != 1) {
                clearIBuf();
                printf("Invalid input. Abonent not added.\n");
                return;
            }
            clearIBuf();
            
            printf("Enter second name (max 9 characters): ");
            if (scanf("%9s", phonebook[i].second_name) != 1) {
                clearIBuf();
                printf("Invalid input. Abonent not added.\n");
                strcpy(phonebook[i].name, "");
                return;
            }
            clearIBuf();
            
            printf("Enter telephone (max 9 characters): ");
            if (scanf("%9s", phonebook[i].tel) != 1) {
                clearIBuf();
                printf("Invalid input. Abonent not added.\n");
                strcpy(phonebook[i].name, "");
                strcpy(phonebook[i].second_name, "");
                return;
            }
            clearIBuf();

            printf("Abonent added successfully.\n");
            return;
        }
    }
    printf("Phonebook is full. Cannot add more abonents.\n");
}

void deleteAbonent() {
    char name[10];
    char second_name[10];
    printf("Enter the name of the abonent to delete (max 9 characters): ");
    if (scanf("%9s", name) != 1) {
        clearIBuf();
        printf("Invalid input. Abonent not deleted.\n");
        return;
    }
    clearIBuf();

    printf("Enter the second name of the abonent to delete (max 9 characters): ");
    if (scanf("%9s", second_name) != 1) {
        clearIBuf();
        printf("Invalid input. Abonent not deleted.\n");
        return;
    }
    clearIBuf();

    for (int i = 0; i < MAX_ABONENTS; i++) {
        if (strcmp(phonebook[i].name, name) == 0 && strcmp(phonebook[i].second_name, second_name) == 0) {
            strcpy(phonebook[i].name, "");
            strcpy(phonebook[i].second_name, "");
            strcpy(phonebook[i].tel, "");
            printf("Abonent deleted successfully.\n");
            return;
        }
    }
    printf("Abonent not found.\n");
}

void searchAbonent() {
    char name[10];
    printf("Enter name to search (max 9 characters): ");
    if (scanf("%9s", name) != 1) {
        clearIBuf();
        printf("Invalid input.\n");
        return;
    }
    clearIBuf();

    int found = 0;
    for (int i = 0; i < MAX_ABONENTS; i++) {
        if (strcmp(phonebook[i].name, name) == 0) {
            printf("Name: %s, Second Name: %s, Tel: %s\n", phonebook[i].name, phonebook[i].second_name, phonebook[i].tel);
            found = 1;
        }
    }
    if (!found) {
        printf("No abonents found with name %s.\n", name);
    }
}

void displayAll() {
    int found = 0;
    for (int i = 0; i < MAX_ABONENTS; i++) {
        if (strcmp(phonebook[i].name, "") != 0) {
            printf("Name: %s, Second Name: %s, Tel: %s\n", phonebook[i].name, phonebook[i].second_name, phonebook[i].tel);
            found = 1;
        }
    }
    if (!found) {
        printf("Phonebook is empty.\n");
    }
}

int main() {
    int choice;
    initPB();

    do {
        printf("\nPhonebook Menu:\n");
        printf("1) Add abonent\n");
        printf("2) Delete abonent\n");
        printf("3) Search abonents by name\n");
        printf("4) Display all records\n");
        printf("5) Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clearIBuf();
            printf("Invalid input. Please enter a number between 1 and 5.\n");
            continue;
        }
        clearIBuf();

        switch (choice) {
            case 1:
                addAbonent();
                break;
            case 2:
                deleteAbonent();
                break;
            case 3:
                searchAbonent();
                break;
            case 4:
                displayAll();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
