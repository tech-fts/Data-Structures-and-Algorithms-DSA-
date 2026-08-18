#include <stdio.h>
#include <stdlib.h>
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

int start_game(){
    int game_input = 0;
    int x;

    printf("Please enter a number for lottery: \n");
    scanf("%d", &game_input);

    if ( game_input > 0 && game_input < 10){
        for(int i =0; i <5 ; i++)
        {
            int number = rand() % 10 - 1;
            printf("%d\n",number);
            if (number == game_input){
                printf("You win the game. ");
                return 0;  
            }else{
                printf("You loose the game. Enter again...\n");
                scanf("%d", &game_input);
            }

        }
        printf("Your time is expired. Try again.");
    }
    printf("Your game input is too large... Try again\n");
    scanf("%d", &game_input);
}

int main(){
    int userAge;

    printf("Welcome to out lottery system!");

    if(check_userage(userAge)){
        printf("You are auth person to play the game \n");
        start_game();
    }

    return 0;
}