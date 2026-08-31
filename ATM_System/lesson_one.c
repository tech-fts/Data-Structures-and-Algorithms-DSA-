#include <stdio.h>
#include <string.h>

void project_display(){
    printf("**********ATM**********\n");
    printf("Welcom to our bank atm system\n");
}

int check_card(int card){
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
    printf("1. Check account balance: \n");
    printf("2. Withdraw balance: \n");

    while (scanf("%d", &main_option) != 1 && main_option < 0)
    {
        printf("Invalid Input. Please enter again: ");
        while(getchar() != '\n');
    }

    return main_option;
}

float withdraw_balance(float main_account){
    return 0;
}

float balance_function(int opt, float main_account){
    if(opt == 1){
        printf("Your balance is : %.f", main_account);
    }else if(opt == 2){
        withdraw_balance(main_account);
        printf("successfully withdraw!");
    }
}

int main(){
    int card;
    float main_account = 1200000;
    project_display();

    //check card
    int check = check_card(card);
    if(check != 1){
        printf("your card not inserted");
    }
    
    //check pin
    int check_pin = get_password();
    if(check_pin == 0){
        printf("Your card pin are wrong");
    }

    //main function for atm
    int opt = main_atm_menu();
    balance_function(opt, main_account);
    return 0;
}