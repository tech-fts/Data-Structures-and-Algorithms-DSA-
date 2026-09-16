#ifndef BILLING_H
#define BILLING_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

//declare person and meter
struct Person {
    int accountId;
    char userName[50];
    char password[50];
    char userRole[50];
    char useType[50];
    char Location[100];
    float total_usage;
    int meterId;
    float amount;
    bool payment;
};

struct Meter {
    int meterId;
    float preReading;
    float currentReading;
    float units_consumed;
};

int login(struct Person users[], const char userName[], const char password[]);
struct Person meter_usageCalculation(struct Meter m, struct Person users[], const int index);
float cash_payment();
float mobile_payment();

#endif