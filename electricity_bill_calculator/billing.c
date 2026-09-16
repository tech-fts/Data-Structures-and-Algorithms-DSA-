#include <stdio.h>
#include "billing.h"

//user login
int login(struct Person users[], const char userName[], const char password[]) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(users[i].userName, userName) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Authenticated as: %s (%s)\n", users[i].userName, users[i].userRole);
            return i;
        }
    }
    printf("Invalid username or password!\n");
    return -1;
}

struct Person meter_usageCalculation(struct Meter m, struct Person users[], const int index) {
    printf("\n--- METER USAGE CALCULATION ---\n");
    float ratePerUnit = 5.50f;
    users[index].total_usage = m.units_consumed * ratePerUnit;

    printf("Previous Reading : %.2f\n", m.preReading);
    printf("Current Reading  : %.2f\n", m.currentReading);
    printf("Units Consumed   : %.2f kW\n", m.units_consumed);
    printf("Total Cost       : $%.2f\n", users[index].total_usage);

    return users[index];
}

// Return float instead of int. payment
float cash_payment() {
    int status = 0;
    float amount = 0.0f;

    while (1) {
        printf("Enter amount to pay: ");
        status = scanf("%f", &amount);

        if (status == EOF) {
            printf("Error: no input detected.\n");
            return -1.0f;
        }

        if (status == 0) {
            printf("Invalid input! Please enter numbers only.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        if (amount <= 0.0f) {
            printf("Payment amount must be greater than 0.\n");
            continue;
        }

        break;
    }

    return amount; // Return the entered amount
}

// Return float instead of int
float mobile_payment() {
    int status = 0;
    float amount = 0.0f;

    while (1) {
        printf("Enter amount to pay: ");
        status = scanf("%f", &amount);

        if (status == EOF) {
            printf("Error: no input detected.\n");
            return -1.0f;
        }

        if (status == 0) {
            printf("Invalid input! Please enter numbers only.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        if (amount <= 0.0f) {
            printf("Payment amount must be greater than 0.\n");
            continue;
        }

        break;
    }

    return amount; // Return the entered amount
}

struct Person make_payment(struct Person p, struct Person users[], const int index) {
    // Sync local struct p with array state
    p.total_usage = users[index].total_usage;
    printf("Your meter usage cost is: $%.2f\n", p.total_usage);

    int method = 0; 

    printf("Enter payment methods: \n");
    printf("1. Cash\n");
    printf("2. Mobile Pay\n");
    printf("3. Own Payment List\n");
    printf("Choice: ");
    scanf("%d", &method);

    if (method == 1) {
        float paid = cash_payment();
        if (paid > 0.0f) {
            users[index].amount += paid; // Accumulate payment
            if (users[index].amount >= users[index].total_usage && users[index].total_usage > 0.0f) {
                users[index].payment = true;
            }
            printf("Payment of $%.2f accepted!\n", paid);
        }
        printf("Your Cash Payment status is: %s\n", users[index].payment ? "Paid" : "Unpaid");

    } else if (method == 2) {
        float paid = mobile_payment();
        if (paid > 0.0f) {
            users[index].amount += paid; // Accumulate payment
            if (users[index].amount >= users[index].total_usage && users[index].total_usage > 0.0f) {
                users[index].payment = true;
            }
            printf("Your Mobile Payment of $%.2f accepted!\n", paid);
        }
        printf("Your Mobile Payment status is: %s\n", users[index].payment ? "Paid" : "Unpaid");

    } else if (method == 3) {
        // FIXED: Changed %d to $%.2f so float values format properly
        printf("User amount: $%.2f | User Payment status: %s\n", 
               users[index].amount, 
               users[index].payment ? "Paid" : "Unpaid");
    }

    return users[index]; // Return updated array element back to main
}

struct Meter user_meter(struct Person users[], const int userIndex, struct Meter meters[]) {

    int userMeter, meterid = 0;
    for(int i = 0; i < 2; i++){
        if (meters->meterId == users[userIndex].meterId){
            userMeter = 1;
            printf("%d", i);
            meterid = i;
        }
    }

    meters[meterid].preReading = 120.3f;
    meters[meterid].currentReading = meters[meterid].preReading;
    meters[meterid].units_consumed = 0.0f;
    
    int choice = 0;
    printf("\nMeter started!\n");

    while (1) {
        meters[meterid].currentReading += 1.0f;
        meters[meterid].units_consumed = meters[meterid].currentReading - meters[meterid].preReading;

        printf("\rCurrent Reading: %.2f | Consumed: %.2f kW  ", meters[meterid].currentReading, meters[meterid].units_consumed);
        fflush(stdout);

        sleep(1);

        printf("\nPress 1 to Exit (or 0 to keep running): ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Exiting meter...\n");
            // Break loop cleanly to return m1 back to main
            break; 
        }
    }

    return meters[meterid]; 
}