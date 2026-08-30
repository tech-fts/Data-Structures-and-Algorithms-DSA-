#include <stdio.h>
#include <stdlib.h>
#define mock_size 10

typedef struct
{
    int id;
    char name[64];
    double price;
    double discount_rate;
    int quantity;
}Item;

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

    if(checkout_array == NULL){
        return 0;
    }
    return 1;
}

char add_item_checkout(Item mock_items[], const int item_num, Item checkout_array[]){
    int check_index = 0;

    printf("item name is: %s\n", mock_items[item_num].name);
    printf("item quantity is: %d\n", mock_items[item_num].quantity);
    printf("item price is: %d\n", mock_items[item_num].price);

}

int main(){
    int item_num;
    Item *checkout_array = NULL;
    printf("continue to do checkout");
    for(int i = 0; i < mock_size; i++){
        printf("%d. items name is: %s \n", i, mock_items[i].name);
    }

    while(1){
        printf("Enter item number to buy: ");

        while (scanf("%d", &item_num) != 1 || item_num < 0)
        {
            printf("Invalid Input. Please enter again...");
            while(getchar() != '\n');
        }

        printf("itemnumbers:%d \n", item_num);

        if(!init_memory(&checkout_array, item_num)){
            printf("Failed to allocate cart memory.\n");
            return 1;
        };

        add_item_checkout(mock_items,item_num, checkout_array);
    }
    return 0;
}