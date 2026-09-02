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
        scanf("%d", &pe.id);
        printf("Name: ");
        scanf("%s", pe.name);
        printf("Email: ");
        scanf("%s", pe.email);
        printf("Address: ");
        scanf("%s", pe.address);
        printf("Phone Number: ");
        scanf("%s", pe.phoneNumber);

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