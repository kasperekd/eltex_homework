// #include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
};

struct abonent* phonebook = NULL;
int phonebook_size = 0;

void clearIBuf() {
    while (getchar() != '\n');
}

void handleMemERR() {
    if (errno == ENOMEM) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
}

void addAbonent() {
    phonebook_size++;
    phonebook = realloc(phonebook, phonebook_size * sizeof(struct abonent));
    if (phonebook == NULL) {
        handleMemERR();
    }

    struct abonent* new_abonent = &phonebook[phonebook_size - 1];
    
    printf("Enter name (max 9 characters): ");
    if (scanf("%9s", new_abonent->name) != 1) {
        clearIBuf();
        printf("Invalid input. Abonent not added.\n");
        phonebook_size--;
        phonebook = realloc(phonebook, phonebook_size * sizeof(struct abonent));
        if (phonebook_size > 0 && phonebook == NULL) {
            handleMemERR();
        }
        return;
    }
    clearIBuf();

    printf("Enter second name (max 9 characters): ");
    if (scanf("%9s", new_abonent->second_name) != 1) {
        clearIBuf();
        printf("Invalid input. Abonent not added.\n");
        phonebook_size--;
        phonebook = realloc(phonebook, phonebook_size * sizeof(struct abonent));
        if (phonebook_size > 0 && phonebook == NULL) {
            handleMemERR();
        }
        return;
    }
    clearIBuf();

    printf("Enter telephone (max 9 characters): ");
    if (scanf("%9s", new_abonent->tel) != 1) {
        clearIBuf();
        printf("Invalid input. Abonent not added.\n");
        phonebook_size--;
        phonebook = realloc(phonebook, phonebook_size * sizeof(struct abonent));
        if (phonebook_size > 0 && phonebook == NULL) {
            handleMemERR();
        }
        return;
    }
    clearIBuf();

    printf("Abonent added successfully.\n");
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

    for (int i = 0; i < phonebook_size; i++) {
        if (strcmp(phonebook[i].name, name) == 0 && strcmp(phonebook[i].second_name, second_name) == 0) {
            // Перемещение последнего элемента на место удаляемого
            phonebook[i] = phonebook[phonebook_size - 1];
            phonebook_size--;

            // Изменение размера массива
            phonebook = realloc(phonebook, phonebook_size * sizeof(struct abonent));
            if (phonebook_size > 0 && phonebook == NULL) {
                handleMemERR();
            }

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
    for (int i = 0; i < phonebook_size; i++) {
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
    if (phonebook_size == 0) {
        printf("Phonebook is empty.\n");
        return;
    }

    for (int i = 0; i < phonebook_size; i++) {
        printf("Name: %s, Second Name: %s, Tel: %s\n", phonebook[i].name, phonebook[i].second_name, phonebook[i].tel);
    }
}

int main() {
    int choice;

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

    free(phonebook);
    return 0;
}
