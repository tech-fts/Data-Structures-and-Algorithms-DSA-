#include <stdio.h>

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

struct Person users[3] = {
        {101, "admin", "admin123", "admin", "Work", "Urban"},
        {102, "john_doe", "pass456", "user", "House", "Rural"},
    };

void login(const char userName[], const char password[]){
    printf("\nAuthenticating user: %s...\n", users);

    // if (userName == user[])
}

int main(){
    struct Person p1;

    printf("**********Electricity Bill Calculator**********\n");
    printf("*****Login*****\n");
    printf("Enter user name: \n");
    scanf("%s", p1.userName);
    printf("Enter password: \n");
    scanf("%s", p1.password);

    login(p1.userName, p1.password);
    return 0;
}