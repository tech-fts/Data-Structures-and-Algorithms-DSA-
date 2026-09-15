#ifndef ATM_H
#define ATM_H

#define Fixed_Deposite 10000
#define Insufficient_amout -1
#define Invalid_withdraw -2
#define Invalid_pin -3

int check_card(void);
int check_pin(void);
int deposite(amount);
int withdraw(float *main_account);
int main_atm_menu(void);
void balance_function(int opt, float *main_account);

#endif