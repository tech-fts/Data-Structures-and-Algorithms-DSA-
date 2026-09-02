#include <stdio.h>
#include <stdlib.h>
#define person_size 100

typedef struct {
    int id;
    char name[50];
    char email[50];
    char address[200];
    char phoneNumber[100];
} Person;

void get_userdata(Person database[],int size, Person pe){
    if(size > person_size){
        printf("Error: Number of people exceeds the maximum limit.\n");
        return;
    }
    for(int i=0; i< size; i++){
        printf("Enter details for person %d:\n", i + 1);
        pe.id = i + 1; // Assign a unique ID to each person
        printf("Name: ");
        scanf("%s", pe.name);
        printf("Email: ");
        scanf("%s", pe.email);
        printf("Address: ");
        scanf("%s", pe.address);
        printf("Phone Number: ");
        scanf("%s", pe.phoneNumber);

        printf("user name is: %s\n", pe.name);

        database[i] = pe; // Store the person in the database array

    }
}

void show_database(Person database[], int size){
    printf("Database Contents:\n");
    for(int i = 0; i < size; i++){
        printf("Person %d:\n", i + 1);
        printf("ID: %d\n", database[i].id);
        printf("Name: %s\n", database[i].name);
        printf("Email: %s\n", database[i].email);
        printf("Address: %s\n", database[i].address);
        printf("Phone Number: %s\n", database[i].phoneNumber);
        printf("\n");
    }
}

int main(){
    printf("Welcome to our database system\n");
    Person pe;
    int people = 0;
    int user_input = 0;

    printf("please enter number that you want to add in database: ");
    scanf("%d", &user_input);
    Person *database = (Person *)malloc(sizeof(Person) * user_input); // Allocate memory for 100 Person records changed to user input
    if(database == NULL) { //check null for memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    get_userdata(database, user_input, pe);//declare function
    show_database(database, user_input);
    free(database); // Don't forget to free the allocated memory
    return 0;
}