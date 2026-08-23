#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct Person {
    int accountId;
    char userName[50];
    char password[50];
    char userRole[50];
    char useType[50];
    char Location[100];
    float total_usage;
    int meterId;
};

struct Meter {
    int meterId;
    float preReading;
    float currentReading;
    float units_consumed;
};

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

struct Person meter_usageCalculation(struct Meter m, struct Person p) {
    printf("\n--- METER USAGE CALCULATION ---\n");
    float ratePerUnit = 5.50f;
    p.total_usage = m.units_consumed * ratePerUnit;

    printf("Previous Reading : %.2f\n", m.preReading);
    printf("Current Reading  : %.2f\n", m.currentReading);
    printf("Units Consumed   : %.2f kW\n", m.units_consumed);
    printf("Total Cost       : $%.2f\n", p.total_usage);

    return p;
}

// Return float instead of int
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

float make_payment(struct Person p) {
    printf("Your meter usage cost is: $%.2f\n", p.total_usage);

    int method = 0; 
    float amount = 0.0f;

    printf("Enter payment methods: \n");
    printf("1. cash\n");
    printf("2. Mobile Pay\n");

    scanf("%d", &method);

    if (method == 1) {
        // Capture the returned value
        amount = cash_payment();
        printf("Payment of $%.2f accepted!\n", amount);
        return amount;
    } else if (method == 2) {
        // Capture the returned value
        amount = mobile_payment();
        printf("Your Mobile Payment of $%.2f accepted!\n", amount);
        return amount;
    }

    return 0.0f;
}

struct Meter user_meter(struct Person users[], const int userIndex) {
    struct Meter m1;
    
    m1.preReading = 120.3f;
    m1.currentReading = m1.preReading;
    m1.units_consumed = 0.0f;
    
    int choice = 0;
    printf("\nMeter started!\n");

    while (1) {
        m1.currentReading += 1.0f;
        m1.units_consumed = m1.currentReading - m1.preReading;

        printf("\rCurrent Reading: %.2f | Consumed: %.2f kW  ", m1.currentReading, m1.units_consumed);
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

    return m1; 
}

int main() {
    struct Person p1;
    // Initialize struct Meter so it doesn't hold random memory garbage
    struct Meter m = {0.0f, 0.0f, 0.0f};

    struct Person users[2] = {
        {101, "admin", "admin123", "admin", "Work", "Urban"},
        {102, "john_doe", "pass456", "user", "House", "Rural"},
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
        } else {
            int running = 1;

            // This loop keeps showing the dashboard after every task completes
            while (running) {
                int option = user_dashboard(users, userIndex);

                if (option == 1) {
                    // Save updated readings to 'm' declared in main
                    m = user_meter(users, userIndex); 
                } else if (option == 2) {
                    // Pass saved values from 'm' to calculation
                    p1 = meter_usageCalculation(m, p1); 
                }else if(option == 3){
                    make_payment(p1);
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