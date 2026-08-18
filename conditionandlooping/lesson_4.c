#include <stdio.h>
#include <stdbool.h>

bool check_userage(int userAge){
    printf("Enter your age to check permit age: ");
    scanf("%d", &userAge);

    while (userAge < 18){
        printf("You are too young. Enter again: \n");
        scanf("%d", &userAge);
    }

    return userAge >= 18;
}

int main(){
    int userAge;

    printf("Welcome to out lottery system!");

    if(check_userage(userAge)){
        printf("You are auth person to play the game");
    }

    return 0;
}