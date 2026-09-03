#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PERSONS 100

typedef struct {
    int id;
    char name[50];
    char email[50];
    char address[200];
    char phoneNumber[100];
} Person;

int input_check(const char *type, int user_input) {
    while (scanf(type, &user_input) != 1) {
        printf("Invalid input. Please enter a valid integer: ");
        while (getchar() != '\n'); // Clear the input buffer
    }
    while (getchar() != '\n'); // Clear trailing newline
    return user_input;
}

void get_userdata(Person database[], int count) {
    for (int i = 0; i < count; i++) {
        printf("\n--- Enter details for person %d ---\n", i + 1);
        database[i].id = i + 1;

        printf("Name: ");
        fgets(database[i].name, sizeof(database[i].name), stdin);
        database[i].name[strcspn(database[i].name, "\n")] = 0; // Remove newline

        printf("Email: ");
        fgets(database[i].email, sizeof(database[i].email), stdin);
        database[i].email[strcspn(database[i].email, "\n")] = 0;

        printf("Address: ");
        fgets(database[i].address, sizeof(database[i].address), stdin);
        database[i].address[strcspn(database[i].address, "\n")] = 0;

        printf("Phone Number: ");
        fgets(database[i].phoneNumber, sizeof(database[i].phoneNumber), stdin);
        database[i].phoneNumber[strcspn(database[i].phoneNumber, "\n")] = 0;
    }
}

void show_database(Person database[], int size) {
    if (database == NULL || size == 0) {
        printf("\nNo data to show. Please add people to the database first.\n");
        return;
    }

    printf("\n================ DATABASE CONTENTS ================\n");
    for (int i = 0; i < size; i++) {
        printf("Person %d (ID: %d):\n", i + 1, database[i].id);
        printf("  Name:  %s\n", database[i].name);
        printf("  Email: %s\n", database[i].email);
        printf("  Addr:  %s\n", database[i].address);
        printf("  Phone: %s\n", database[i].phoneNumber);
        printf("--------------------------------------------------\n");
    }
}

void name_search(Person database[], int size){
    char search_name[50];
    printf("Enter name to search: ");
    scanf("%s", search_name);
    for (int i = 0; i < size; i++) {
        if (strcmp(database[i].name, search_name) == 0) {
            printf("Person found:\n");
            printf("  Name:  %s\n", database[i].name);
            printf("  Email: %s\n", database[i].email);
            printf("  Addr:  %s\n", database[i].address);
            printf("  Phone: %s\n", database[i].phoneNumber);
            return;
        }
    }
    printf("Person not found.\n");
}

void email_search(Person database[], int size){
    char search_email[50];
    printf("Enter email to search: ");
    scanf("%s", search_email);
    for (int i = 0; i < size; i++) {
        if (strcmp(database[i].email, search_email) == 0) {
            printf("Person found:\n");
            printf("  Name:  %s\n", database[i].name);
            printf("  Email: %s\n", database[i].email);
            printf("  Addr:  %s\n", database[i].address);
            printf("  Phone: %s\n", database[i].phoneNumber);
            return;
        }
    }
    printf("Person not found.\n");
}

void address_search(Person database[], int size){
    char search_address[200];
    printf("Enter address to search: ");
    scanf("%s", search_address);
    for (int i = 0; i < size; i++) {
        if (strcmp(database[i].address, search_address) == 0) {
            printf("Person found:\n");
            printf("  Name:  %s\n", database[i].name);
            printf("  Email: %s\n", database[i].email);
            printf("  Addr:  %s\n", database[i].address);
            printf("  Phone: %s\n", database[i].phoneNumber);
            return;
        }
    }
    printf("Person not found.\n");
}

void phone_search(Person database[], int size){
    char search_phone[20];
    printf("Enter phone number to search: ");
    scanf("%s", search_phone);
    for (int i = 0; i < size; i++) {
        if (strcmp(database[i].phoneNumber, search_phone) == 0) {
            printf("Person found:\n");
            printf("  Name:  %s\n", database[i].name);
            printf("  Email: %s\n", database[i].email);
            printf("  Addr:  %s\n", database[i].address);
            printf("  Phone: %s\n", database[i].phoneNumber);
            return;
        }
    }
    printf("Person not found.\n");
}

void search_person(Person database[], int size, const char *option){
    if(option == NULL || database == NULL || size <= 0) {
        printf("Invalid search parameters.\n");
        return;
    }

    if (strcmp(option, "name") == 0) {
        name_search(database, size);
    } else if (strcmp(option, "email") == 0) {
        email_search(database, size);
    } else if (strcmp(option, "address") == 0) {
        address_search(database, size);
    } else if (strcmp(option, "phone") == 0) {
        phone_search(database, size);
    } else {
        printf("Invalid search option. Please choose from name/email/address/phone.\n");
    }
}

int get_userOption() {
    int user_input = 0;
    printf("\nPlease choose an option:\n");
    printf("1. Add new persons to database\n");
    printf("2. View database contents\n");
    printf("3. Search for a person\n");
    printf("4. Exit\n");
    printf("Selection: ");
    return input_check("%d", user_input);
}

int main() {
    Person *database = NULL;
    int current_count = 0;
    bool running = true;

    printf("Welcome to our database system\n");

    while (running) {
        int option = get_userOption();

        if (option == 1) {
            printf("How many people do you want to add? ");
            int new_people = 0;
            new_people = input_check("%d", new_people);

            if (new_people <= 0) {
                printf("Invalid number of records.\n");
                continue;
            }

            // Fix scope bug: allocate into outer 'database' pointer using realloc
            Person *temp = realloc(database, sizeof(Person) * (current_count + new_people));
            if (temp == NULL) {
                fprintf(stderr, "Memory allocation failed!\n");
                free(database);
                return 1;
            }
            database = temp;

            // Populate data starting at current end index
            get_userdata(&database[current_count], new_people);
            current_count += new_people;

        } else if (option == 2) {
            show_database(database, current_count);

        } else if(option == 3){
            char search_option[50];
            printf("Enter search option (name/email/address/phone): ");
            scanf("%s", search_option);
            search_person(database, current_count, search_option); // Example search by name
        }else if (option == 4) {
            printf("Exiting database system...\n");
            running = false;

        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    if (database != NULL) {
        free(database);
    }

    return 0;
}