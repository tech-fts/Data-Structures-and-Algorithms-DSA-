#include <stdio.h>
#include <string.h>

void project_display(){
    printf("**********ATM**********\n");
    printf("Welcome to our bank atm system\n");
}

int check_card(){
    int card;
    printf("1. Enter your card: \n");
    while (scanf("%d", &card) != 1)
    {
        printf("Invalid Input. Please enter again: ");
        while(getchar() != '\n');
    }
    return 1;
}

int get_password() {
    char pin[] = "123456";
    char input[32];

    printf("Enter your card pin: ");
    scanf("%s", input);

    if (strcmp(input, pin) == 0) {
        return 1; // Correct PIN
    }
    
    return 0; // Wrong PIN
}

int main_atm_menu(){
    int main_option;
    printf("\n--- Main Menu ---\n");
    printf("1. Check account balance\n");
    printf("2. Withdraw balance\n");
    printf("3. Exit\n"); // Added Exit option
    printf("Select option: ");

    // Loop until user enters integer 1, 2, or 3
    while (scanf("%d", &main_option) != 1 || (main_option < 1 || main_option > 3))
    {
        printf("Invalid Input. Please enter 1, 2, or 3: ");
        while(getchar() != '\n');
    }

    return main_option;
}

// Pass main_account as a pointer so changes update the balance in main()
void enter_manually(float *main_account){
    float manual_amount;
    printf("Enter amount that you want to withdraw: ");
    
    while (scanf("%f", &manual_amount) != 1 || manual_amount > *main_account || manual_amount < 5000) {
        printf("Invalid or insufficient balance. Try again: ");
        while(getchar() != '\n');
    }

    *main_account -= manual_amount;
    printf("Successfully withdrew: $%.2f\n", manual_amount);
    printf("Remaining balance: $%.2f\n", *main_account);
}

void withdraw_balance(float *main_account){
    int withdraw;
    float amount_to_withdraw = 0;
    
    printf("\nSelect withdraw amount:\n");
    printf("1. 50000\n");
    printf("2. 100000\n");
    printf("3. 150000\n");
    printf("4. 200000\n");
    printf("5. 300000\n");
    printf("6. Enter manually\n");
    printf("Option: ");
    
    while(scanf("%d", &withdraw) != 1 || withdraw < 1 || withdraw > 6){
        printf("Invalid Input. Please enter (1-6): ");
        while(getchar() != '\n');
    }

    switch (withdraw)
    {
    case 1: amount_to_withdraw = 50000; break;
    case 2: amount_to_withdraw = 100000; break;
    case 3: amount_to_withdraw = 150000; break;
    case 4: amount_to_withdraw = 200000; break;
    case 5: amount_to_withdraw = 300000; break;
    case 6:
        enter_manually(main_account);
        return;
    }

    if (amount_to_withdraw > *main_account) {
        printf("Transaction failed! Insufficient balance.\n");
    } else {
        *main_account -= amount_to_withdraw;
        printf("Successfully withdrew: $%.2f\n", amount_to_withdraw);
        printf("Remaining balance: $%.2f\n", *main_account);
    }
}

void balance_function(int opt, float *main_account){
    if(opt == 1){
        printf("Your balance is: $%.2f\n", *main_account);
    } else if(opt == 2){
        withdraw_balance(main_account);
    }
}

int main(){
    float main_account = 1200000;
    project_display();

    // Check card
    if(check_card() != 1){
        printf("Your card was not inserted.\n");
        return 0;
    }
    
    // Check pin
    if(get_password() == 0){
        printf("Your card PIN is wrong.\n");
        return 0;
    }

    while (1)
    {
        // Main ATM operations
        int opt = main_atm_menu();

        if (opt == 3) {
            printf("Thank you for using our bank ATM. Goodbye!\n");
            break; // Exit the loop cleanly
        }

        balance_function(opt, &main_account);
    }

    return 0;
}