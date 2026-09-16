#include <stdio.h>
#include "billing.h"
#include "billing.c"

//Admin side
int admin_dashboard(struct Person users[], const int userIndex){
    printf("\n--- USER DASHBOARD ---\n");
    printf("Account Type: %s | Location: %s\n", users[userIndex].userRole, users[userIndex].Location);

    int adopt = 0;
    printf("1. users lists\n");
    printf("2. payment List from all users\n");
    printf("0. Exit program\n");
    scanf("%d", &adopt);

    return adopt;
}

void payment_list(struct Person users[]){
    printf("**********Payment List**********",users[1].accountId);
    for (int i =0; i < 2; i++){
        if (strcmp(users[i].userRole, "admin") != 0) {
            printf("\nAccount ID: %d | User: %s | Total Paid: $%.2f | Status: %s\n", 
                    users[i].accountId, 
                    users[i].userName, 
                    users[i].amount, 
                    users[i].payment ? "Paid" : "Unpaid");
        }
    }
}

void users_list(struct Person users[]){

    printf("**********Users List**********\n");
    for(int i; i<2; i++){
        if(strcmp(users[i].userRole,"admin") != 0){
            printf("Users name: %s | MeterType: %s | Location: %s\n | paid: $%.2f\n", users[i].userName, users[i].useType, users[i].Location, users[i].amount);
        }
    }
}

// User side
int user_dashboard(struct Person users[], const int userIndex) {
    printf("\n--- USER DASHBOARD ---\n");
    printf("Account Type: %s | Location: %s\n", users[userIndex].useType, users[userIndex].Location);
    int useropt = 0;
    printf("0. Exit program\n");
    printf("1. Meter usage\n");
    printf("2. Meter usage calculation\n");
    printf("3. Meter payment\n");
    printf("Enter option: ");
    scanf("%d", &useropt);

    return useropt;
}

int main() {
    struct Person p1;
    // Initialize struct Meter so it doesn't hold random memory garbage
    struct Meter m = {0.0f, 0.0f, 0.0f};

    struct Person users[2] = {
        {101, "admin", "admin123", "admin", "Work", "Urban"},
        {102, "john_doe", "pass456", "user", "House", "Rural", 0, 00001},
    };

    struct Meter meters[2] = {
        {00001,0.0f, 0.0f, 0.0f},
        {00002,0.0f, 0.0f, 0.0f}
    };
    

    printf("**********Electricity Bill Calculator**********\n");
    printf("*****Login*****\n");
    printf("Enter user name: ");
    scanf("%s", p1.userName);
    printf("Enter password: ");
    scanf("%s", p1.password);

    int userIndex = login(users, p1.userName, p1.password);

    if (userIndex != -1) {
        if (strcmp(users[userIndex].userRole, "admin") == 0) {
            printf("\n--- ADMIN DASHBOARD ---\n");

            int admintime = 1;

            while (admintime) {
                int adoption = admin_dashboard(users, userIndex);

                if (adoption == 1) {
                    printf("\nAdmin Action Executed Successfully!\n");
                    users_list(users);
                } else if (adoption == 2){
                    payment_list(users);
                }else if (adoption == 0) {
                    printf("Exiting admin dashboard...\n");
                    admintime = 0;
                } else {
                    printf("Invalid Option. Try again.\n");
                }
            }
            
        } else {
            int running = 1;

            // This loop keeps showing the dashboard after every task completes
            while (running) {
                int option = user_dashboard(users, userIndex);

                if (option == 1) {
                    // Save updated readings to 'm' declared in main
                    m = user_meter(users, userIndex, meters); 
                } else if (option == 2) {
                    // Pass saved values from 'm' to calculation
                    p1 = meter_usageCalculation(m, users, userIndex); 
                }else if(option == 3){
                    p1 = make_payment(p1, users, userIndex);
                    users[userIndex].amount = p1.amount; // Save to the global array
                }
                else if (option == 0) {
                    printf("Exiting application...\n");
                    running = 0; // Exit dashboard loop
                } else {
                    printf("Invalid option! Try again.\n");
                }
            }
        }
    } else {
        printf("\nAccess Denied. Exiting program...\n");
    }

    return 0;
}