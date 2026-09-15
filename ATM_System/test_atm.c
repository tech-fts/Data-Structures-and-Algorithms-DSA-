#include <assert.h>
#include <stdio.h>
#include "atm.h"

int test_deposite(void) {
    float amount = 15000.0f;
    assert(deposite(amount) == 0);
    printf("test deposite function is succeed\n");
    return 0;
}

int test_withdraw(void) {
    float main_account = 120000.0f;

    printf("Enter amount to withdraw: 50000\n");
    assert(withdraw(&main_account) == 1);
    assert(main_account == 70000.0f);
    printf("withdraw amount is succeed\n");
    return 0;
}

int test_balance_function(void) {
    float balance = 120000.0f;

    balance_function(1, &balance);
    printf("test balance_function is succeed\n");
    return 0;
}