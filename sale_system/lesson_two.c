#include <stdio.h>

char get_customerinfo(char *name, int *phone_number, char *shopname, char *address){
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your phone number: ");
    scanf("%d", &phone_number);
    printf("Enter your shop name: ");
    scanf("%s", shopname);
    printf("Enter your address: ");
    scanf("%s", address);
    return 0;
}



int main(){
    //customerinfo();  //tempory comment
    char name[20];
    int phone_number;
    char shopname[20];
    char address[20];

    get_customerinfo(name, &phone_number, shopname, address);

    printf("\nCustomer Information:\n");
    printf("Name: %s\n", name);

    //sale items() and sales()
    char item_name[20];
    int item_quantity;
    float item_price;




    return 0;
}