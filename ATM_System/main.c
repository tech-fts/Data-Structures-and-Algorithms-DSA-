#include <stdio.h>
#include "atm.h"

int main(void) {
    float balance = Fixed_Deposite;

    if (check_card() != 1) {
        printf("Your card was not inserted.\n");
        return 0;
    }

    if (check_pin() != 1) {
        printf("Your card PIN is wrong.\n");
        return 0;
    }

    while (1) {
        int opt = main_atm_menu();

        if (opt == 3) {
            printf("Thank you for using our bank ATM. Goodbye!\n");
            break;
        }

        balance_function(opt, &balance);
    }

    return 0;
}