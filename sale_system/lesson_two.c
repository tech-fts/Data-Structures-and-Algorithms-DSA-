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

char get_saleitems(char *item_name, int *item_quantity, float *item_price){
    printf("Enter item name: ");
    scanf("%s", item_name);
    printf("Enter item quantity: ");
    scanf("%d", &item_quantity);
    printf("Enter item price: ");
    scanf("%f", &item_price);
    return 0;
}

int mainaction(){
    int action;

    printf("Welcome to Our Sale System\n");
    printf("add customerinfo\n");
    scanf("%d", &action);

    while (action != 1){
        printf("add customerinfo\n");
        scanf("%d", &action);
    }

    printf("continue to customer name data... \n");
    return 1;
}

int saleaction(){
    printf("1. Add Sale Items\n");
    return 0;
}

int main(){

    while(1){
        //customerinfo();
        char name[20];
        int phone_number;
        char shopname[20];
        char address[20];

        //sale items() and sales()
        char item_name[20];
        int item_quantity;
        float item_price;

        if (mainaction() != 1){
            get_saleitems(item_name, &item_quantity, &item_price);

            //data for getsaleitems
            printf("\nSale Items:\n");
            printf("Item Name: %s\n", item_name);
            printf("Item Quantity: %d\n", item_quantity);
            printf("Item Price: %.2f\n", item_price);
        }

        // with customerinfo
        get_customerinfo(name, &phone_number, shopname, address);

        //get saleitems() and sales()
        get_saleitems(item_name, &item_quantity, &item_price);

        printf("\nSale Items:\n");
        printf("Item Name: %s\n", item_name);
        printf("Item Quantity: %d\n", item_quantity);
        printf("Item Price: %.2f\n", item_price);
        printf("Name: %s\n", name);
    }

    return 0;
}