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
    if (length == 0)
    {
        printf("\nNo contacts available to view.\n");
        return;
    }
    
    for (int i = 0; i < length; i++) {
        printf("ID: %d | Name: %s | Phone: %s | Email: %s | Address: %s\n", 
            personList[i].contactId, 
            personList[i].name, 
            personList[i].phone_number,
            personList[i].email,
            personList[i].address);
    }
}

void update_contact(struct personInfo personList[], int length) {
    if (length == 0) {
        printf("\nNo contacts available to update.\n");
        return;
    }

    int updateId;
    printf("\nEnter ID that you want to update: ");
    if (scanf("%d", &updateId) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n'); // Clear buffer
        return;
    }

    int found = 0;
    for (int i = 0; i < length; i++) {
        if (personList[i].contactId == updateId) {
            found = 1;
            int choice;

            printf("\nUpdating Contact ID #%d (%s)\n", updateId, personList[i].name);
            printf("1. Update Name\n");
            printf("2. Update Phone Number\n");
            printf("3. Update Email\n");
            printf("4. Update Address\n");
            printf("Enter field to edit (1-4): ");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Enter new name: ");
                scanf("%s", personList[i].name);
            } else if (choice == 2) {
                printf("Enter new phone number: ");
                scanf("%s", personList[i].phone_number);
            } else if (choice == 3) {
                printf("Enter new email: ");
                scanf("%s", personList[i].email);
            } else if (choice == 4) {
                printf("Enter new address: ");
                scanf("%s", personList[i].address);
            } else {
                printf("Invalid field option.\n");
                return;
            }

            printf("--> Contact updated successfully!\n");
            break; // Stop loop once match is found
        }
    }

    if (!found) {
        printf("\nContact with ID %d not found.\n", updateId);
    }
}

int delete_contact(struct personInfo personList[], int length){
    if (length == 0) {
        printf("\nNo contacts available to delete.\n");
        return length;
    }

    view_contact(personList, length);

    int deleteId;
    printf("\nEnter ID that you want to delete: ");
    if (scanf("%d", &deleteId) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n'); 
        return length; // FIX: Return current array size on error
    }

    int found = 0;
    for (int i = 0; i < length; i++) {
        if (personList[i].contactId == deleteId) {
            found = 1;

            for (int j = i; j < length - 1; j++) {
                personList[j] = personList[j + 1];
            }

            length--; 
            printf("\n--> Contact ID %d deleted successfully!\n", deleteId);
            break; 
        }
    }

    if (!found) {
        printf("\nContact with ID %d not found.\n", deleteId);
    }

    return length; // Returns updated array size back to main
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
        }else if(option == 2){
            update_contact(personlist, arrsize);
        }else if(option == 3){
            arrsize = delete_contact(personlist, arrsize);
        }else if(option == 4){
            view_contact(personlist, arrsize);
        }else if(option == 5){
            printf("\nExiting program... Goodbye!\n");
            break; // Breaks out of the while loop to terminate main()
        }
    }
    
    return 0;
}