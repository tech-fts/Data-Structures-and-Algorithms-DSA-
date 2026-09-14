#include <stdio.h>
#include <string.h>
#include "atm.h"

int check_card(void) {
    int card;
    printf("1. Enter your card: \n");
    while (scanf("%d", &card) != 1) {
        printf("Invalid Input. Please enter again: ");
        while (getchar() != '\n');
    }
    return 1;
}

int check_pin(void) {
    char pin[] = "123456";
    char input[32];

    printf("Enter your card pin: ");
    scanf("%s", input);

    if (strcmp(input, pin) == 0) {
        return 1;
    }

    return Invalid_pin;
}

int main_atm_menu(void) {
    int main_option;
    printf("\n--- Main Menu ---\n");
    printf("1. Check account balance\n");
    printf("2. Withdraw balance\n");
    printf("3. Exit\n");
    printf("Select option: ");

    while (scanf("%d", &main_option) != 1 || (main_option < 1 || main_option > 3)) {
        printf("Invalid Input. Please enter 1, 2, or 3: ");
        while (getchar() != '\n');
    }

    return main_option;
}

int withdraw(float *main_account) {
    float amount;
    printf("Enter amount to withdraw: ");

    if (scanf("%f", &amount) != 1 || amount < 0) {
        printf("Invalid amount.\n");
        while (getchar() != '\n');
        return Invalid_withdraw;
    }

    if (amount > *main_account) {
        printf("Insufficient balance.\n");
        return Insufficient_amout;
    }

    *main_account -= amount;
    printf("Successfully withdrew: $%.2f\n", amount);
    printf("Remaining balance: $%.2f\n", *main_account);
    return 1;
}

void balance_function(int opt, float *main_account) {
    if (opt == 1) {
        printf("Your balance is: $%.2f\n", *main_account);
    } else if (opt == 2) {
        withdraw(main_account);
    }
}

int deposite(void) {
    return 0;
}