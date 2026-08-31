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

int main(){
    int card;
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
    return 0;
}