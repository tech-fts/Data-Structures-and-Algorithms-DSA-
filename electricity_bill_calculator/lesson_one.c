#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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
    float amount;
    bool payment;
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