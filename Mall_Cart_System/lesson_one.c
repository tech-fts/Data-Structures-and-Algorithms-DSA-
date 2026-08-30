#include <stdio.h>
#include <stdlib.h>
#define mock_size 10

int check_index = 0;

typedef struct
{
    int id;
    char name[64];
    double price;
    double discount_rate;
    int quantity;
} Item;

Item mock_items[mock_size] = {
    {101, "Wireless Noise-Canceling Headphones", 199.99, 0.15, 1},
    {102, "Ergonomic Mechanical Keyboard",       129.50, 0.10, 1},
    {103, "Ultra-Wide Gaming Monitor 27-inch",   349.00, 0.20, 2},
    {104, "USB-C Multi-Port Adapter Hub",         45.00, 0.00, 3},
    {105, "Anker Portable Power Bank 20000mAh",   59.99, 0.05, 1},
    {106, "HD Webcam 1080p with Microphone",      79.25, 0.00, 1},
    {107, "Adjustable Standing Desk Mat",         39.95, 0.25, 1},
    {108, "Bluetooth Vertical Mouse",             49.99, 0.00, 2},
    {109, "Smart Fitness Tracker Watch",          89.90, 0.30, 1},
    {110, "Braided Nylon Fast Charging Cable",    14.99, 0.00, 5}
};

int init_memory(Item **checkout_array, int initial_capacity){
    *checkout_array = (Item *)malloc(initial_capacity * sizeof(Item));

    // DEREFERENCE FIX: Check allocated heap pointer, not double pointer
    if(*checkout_array == NULL){
        return 0;
    }
    return 1;
}

// TYPE FIX: Return double so cents are preserved in calculations
double calculate_total_price(double price, double dis_rate, int qty){
    return (price * (1.0 - dis_rate)) * qty;
}

// POINTER FIX: Pass grand_total and total_qty as pointers to update by reference
void add_item_checkout(Item mock_items[], const int item_num, Item checkout_array[], double *grand_total, int *total_qty){

    // FORMAT FIX: Use %.2f for double unit price
    printf("item name is: %s\n", mock_items[item_num].name);
    printf("item quantity is: %d\n", mock_items[item_num].quantity);
    printf("item price is: $%.2f\n", mock_items[item_num].price);

    double unit_price = mock_items[item_num].price;
    double dis_rate = mock_items[item_num].discount_rate;
    int qty = mock_items[item_num].quantity;

    // RANGE FIX: Allow item_num 0 to be valid
    if(item_num >= 0 && item_num < mock_size){
        
        // Copy item to heap array
        checkout_array[check_index] = mock_items[item_num];
        check_index++;

        double total = 0.0;

        if(dis_rate > 0.0){
            printf("dis rate appear: %.2f%%\n", dis_rate * 100);
            total = calculate_total_price(unit_price, dis_rate, qty);
        } else {
            printf("dis rate appear: No Discount\n");
            total = unit_price * qty;
        }

        // ACCUMULATE FIX: Update values via pointers before printing
        *total_qty += qty;
        *grand_total += total;

        printf("total qty in cart: %d\n", *total_qty);
        printf("grand total price: $%.2f\n", *grand_total);
    }
}

int main(){
    int item_num;
    Item *checkout_array = NULL;
    double grand_total = 0.0; 
    int total_qty = 0;

    printf("continue to do checkout\n");
    for(int i = 0; i < mock_size; i++){
        printf("%d. items name is: %s \n", i, mock_items[i].name);
    }

    while(1){
        printf("\nEnter item number to buy (-1 to exit): ");

        while (scanf("%d", &item_num) != 1 || item_num < -1 || item_num >= mock_size)
        {
            printf("Invalid Input. Please enter again: ");
            while(getchar() != '\n');
        }

        if(item_num == -1) break;

        printf("itemnumbers: %d\n", item_num);

        if(!init_memory(&checkout_array, mock_size)){
            printf("Failed to allocate cart memory.\n");
            return 1;
        }

        // REFERENCE FIX: Pass memory addresses (&) of accumulators
        add_item_checkout(mock_items, item_num, checkout_array, &grand_total, &total_qty);
    }

    if(checkout_array != NULL){
        free(checkout_array);
        checkout_array = NULL;
    }

    return 0;
}