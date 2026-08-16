#include <stdio.h>

int main(){
    int number=0;
    int total=0;

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
            printf("This is prime number: %d\n", number);

            for (size_t i = 1; i < number; i++)
            {
                printf("These are numbers from prime: %d\n", i);
            }
            total += number;
        }

    }
    printf("\n");

    printf("This is total of prime number: %d",total);
    return 0; //exit the program
}
