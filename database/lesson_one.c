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
    for(int i=0; i< size; i++){
        printf("Enter details for person %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &database[i].id);
        printf("Name: ");
        scanf("%s", database[i].name);
        printf("Email: ");
        scanf("%s", database[i].email);
        printf("Address: ");
        scanf("%s", database[i].address);
        printf("Phone Number: ");
        scanf("%s", database[i].phoneNumber);

        pe.name[i] = database[i].name;
        pe.email[i] = database[i].email;
        pe.address[i] = database[i].address;
        pe.phoneNumber[i] = database[i].phoneNumber;
    }

    for(int i=0; i < size; i++){
        printf("\nDetails of person %d:\n", i + 1);
        printf("ID: %d\n", database[i].id);
        printf("Name: %s\n", database[i].name);
        printf("Email: %s\n", database[i].email);
        printf("Address: %s\n", database[i].address);
        printf("Phone Number: %s\n", database[i].phoneNumber);
    }
}

int main(){
    printf("Welcome to our database system");
    Person pe;
    Person *database = (Person *)malloc(sizeof(Person) * person_size); // Allocate memory for 100 Person records
    if(database == NULL) { //check null for memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    get_userdata(database, person_size, pe);//declare function
    free(database); // Don't forget to free the allocated memory
    return 0;
}