#include <stdio.h>

int main(){
    int number;

    printf("Enter numberone: \n");
    scanf("%d", &number);

    while (number < 10) //condition check
    {
        number++;
        printf("pre %d\n", number);
        if (number % 2 != 0 && number == 3){ //check condition and logical operator
            printf("after %d\n", number);
        }

        if (number % 2 == 0){
            printf("This is prime number.%d\n", number);
        }
    }
    printf("\n");
    return 0; //exit the program
}
