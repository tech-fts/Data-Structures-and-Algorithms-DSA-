#include <stdio.h>
#include <stdbool.h>

int main(){
    int number = 0;
    int total = 0;

    printf("Enter numberone: \n");
    scanf("%d", &number);

    while (number < 10) // condition check
    {
        number++;
        printf("pre %d\n", number);

        if (number % 2 != 0 && number == 3){ // check condition and logical operator
            printf("after %d\n", number);
        }

        // Prime checking logic
        if (number > 1) {
            bool isPrime = true;

            // Start i at 2 to avoid division by zero and false positives on 1
            for (int i = 2; i * i <= number; i++) {
                if ((number % i) == 0) {
                    printf("This is not prime number: %d\n", number);
                    isPrime = false;
                    break; // Stop checking further divisors once one is found
                }
            }

            // Accumulate total only if the number was proven prime
            if (isPrime) {
                total += number;
            }
        }
    }
    printf("\n");

    printf("This is total of prime number: %d\n", total);
    return 0; // exit the program
}