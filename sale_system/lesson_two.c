#include <stdio.h>

void check_type(const char *format, void *address, const char *err_msg){
    while(scanf(format, address) != 1){ //need to check 
        printf("%s",err_msg);

        while(getchar() != '\n');
        printf("Try again... \n");
    }

    while(getchar() != '\n');
}

void get_customerinfo(char *name, int *phone_number, char *shopname, char *address){
    printf("Enter your name: ");
    check_type("%s", name, "Invalid Input. Enter correct name only. \n");
    // while(getchar() != '\n');
    
    printf("Enter your phone number: ");
    check_type("%d", phone_number, "Invalid Input. Enter correct phone number only. \n");

    printf("Enter your shop name: ");
    check_type("%s", shopname, "Invaild Input. Enter correct shop name only. \n");
    // while(getchar() != '\n');

    printf("Enter your address: ");
    check_type("%s", address, "Invalid Input. Enter correct address only. \n");
    // while(getchar() != '\n');

}

void get_saleitems(char *item_name, int *item_quantity, float *item_price){
    printf("Enter item name: ");
    check_type("%s", item_name, "Invalid Input. Enter correct item name only. \n");
    // while(getchar() != '\n');

    printf("Enter item quantity: ");
    check_type("%d", item_quantity, "Invalid Input Enter correct item quantity only. \n");

    printf("Enter item price: \n");
    check_type("%f", item_price, "Invalid Input. Enter correct item price only \n");

}

int mainaction(){
    int action;

    printf("Welcome to Our Sale System\n");
    printf("add customerinfo\n");
    check_type("%d", &action, "Invalid Input. Enter correct option. \n");

    while (action != 1){
        return 0;
    }

    printf("continue to customer name data... \n");
    return 1;
}

int saleaction(){
    int sal_action = 0;
    printf("1. Add Sale Items\n");
    check_type("%d", &sal_action, "Invalid Input. Enter correct option. \n");
    if (sal_action != 1){
        return 0;
    }
    return 1;
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
            return 0;
        }

        // with customerinfo
        get_customerinfo(name, &phone_number, shopname, address);

        int check_sale = saleaction();
        if (check_sale != 1){
            return 0;
        }

        //get saleitems() and sales()
        get_saleitems(item_name, &item_quantity, &item_price);

        printf("\nSale Items:\n");
        printf("Item Name: %s\n", item_name);
        printf("Item Quantity: %d\n", item_quantity);
        printf("Item Price: %.2f\n", item_price);
        printf("Name: %s\n", name);
        printf("\n");
    }

    return 0;
}