#include <stdio.h>
#include <string.h>

struct Person
{
    int accountId;
    char userName[50];
    char password[50];
    char userRole[50];
    char useType[50];
    char Location[100];
};

struct  Meter
{
    float preReading;
    float currentReading;
    float units_consumed;
};

// Returns user index (0 or 1) if successful, or -1 if failed
int login(struct Person users[], const char userName[], const char password[]) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(users[i].userName, userName) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Authenticated as: %s (%s)\n", users[i].userName, users[i].userRole);
            return i; // Return array index of authenticated user
        }
    }

    printf("Invalid username or password!\n");
    return -1; // Authentication failed
}

int main(){
    struct Person p1;

    struct Person users[2] = {
        {101, "admin", "admin123", "admin", "Work", "Urban"},
        {102, "john_doe", "pass456", "user", "House", "Rural"},
    };

    printf("**********Electricity Bill Calculator**********\n");
    printf("*****Login*****\n");
    printf("Enter user name: \n");
    scanf("%s", p1.userName);
    printf("Enter password: \n");
    scanf("%s", p1.password);

    int userIndex = login(users, p1.userName, p1.password);
    printf("%d",userIndex);

    // 1. First, check if the login was successful (userIndex is not -1)
    if (userIndex != -1) {

        // 2. Compare the userRole field using strcmp
        if (strcmp(users[userIndex].userRole, "admin") == 0) {
            printf("\n--- ADMIN DASHBOARD ---\n");
            // Perform admin tasks (e.g., view all user accounts)
        } else {
            printf("\n--- USER DASHBOARD ---\n");
            printf("Account Type: %s | Location: %s\n", users[userIndex].useType, users[userIndex].Location);
            // Prompt for meter readings and compute bill here
        }

    } else {
        printf("\nAccess Denied. Exiting program...\n");
    }
    return 0;
}