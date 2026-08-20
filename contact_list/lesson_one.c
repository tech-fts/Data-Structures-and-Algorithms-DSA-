#include <stdio.h>
#define MaxSize 1000

struct personInfo
{
    char name[50];
    char phone_number[50];
    char email[50];
    char address[100];
    int contactId;
};

int choose_option() {
    int useroption;
    printf("\n--- Contact List Menu ---\n");
    printf("1. Create contact\n");
    printf("2. Update contact\n");
    printf("3. Delete contact\n");
    printf("4. View contact list\n");
    printf("5. Exit\n");                  // Added Exit option
    printf("Enter choice (1-5): ");        // Updated range text

    // Changed condition to allow choice 5
    while (scanf("%d", &useroption) != 1 || useroption < 1) {
        printf("Invalid Input. Try Again (1-5): ");
        while (getchar() != '\n'); // Clear input buffer
    }
    
    return useroption;
}

int create_contact(struct personInfo personlist[], int arrsize){
    int keepAdding = 1;

    while (keepAdding == 1) {
        // Check if the array has reached maximum capacity
        if (arrsize >= MaxSize) {
            printf("\nContact list is full!\n");
            break;
        }

        struct personInfo p1;

        printf("\n--- Enter Contact #%d Details ---\n", arrsize + 1);

        printf("Enter user name: \n");
        scanf("%s", p1.name);

        printf("Enter user phone_number: \n");
        scanf("%s", p1.phone_number);

        printf("Enter user email: \n");
        scanf("%s", p1.email);

        printf("Enter user address: \n");
        scanf("%s", p1.address);

        p1.contactId = arrsize + 1;

        // Store contact into array and increment count
        personlist[arrsize] = p1; 
        arrsize++;                 

        // Display updated array elements
        printf("\nUpdated Contact List (%d total):\n", arrsize);
        for (int i = 0; i < arrsize; i++) {
            printf("ID: %d | Name: %s | Phone: %s | Email: %s | Address: %s\n", 
                   personlist[i].contactId, 
                   personlist[i].name, 
                   personlist[i].phone_number,
                   personlist[i].email,
                   personlist[i].address);
        }

        // Ask user if they want to enter another contact
        printf("\nDo you want to add another contact? (1 = Yes, 0 = No): ");
        scanf("%d", &keepAdding);
    }

    return arrsize; // Return updated total count back to main
}

void view_contact(struct personInfo personList[], int length){
    
    for (int i = 0; i < length; i++) {
        printf("ID: %d | Name: %s | Phone: %s | Email: %s | Address: %s\n", 
            personList[i].contactId, 
            personList[i].name, 
            personList[i].phone_number,
            personList[i].email,
            personList[i].address);
    }
}

int main(){
    struct personInfo p1;
    struct personInfo personlist[MaxSize]; // Array initialized with size MaxSize
    int arrsize = 0;                       // Start count at 0

    while (1)
    {
        printf("Contact List\n", choose_option);
        int option = choose_option();
        if( option == 1){
            arrsize = create_contact(personlist, arrsize);
        }else if(option == 4){
            view_contact(personlist, arrsize);
        }else if(option == 5){
            printf("\nExiting program... Goodbye!\n");
            break; // Breaks out of the while loop to terminate main()
        }
    }
    
    
    return 0;
}