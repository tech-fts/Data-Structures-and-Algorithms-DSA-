#include <stdio.h>
#include <stdlib.h>

int user_input(){
    int numbers;
    printf("Please enter number that you want to add: ");
    
    while (scanf("%d", &numbers) != 1)
    {
        printf("Invalid Input: Please try again: ");
        while (getchar() != '\n');
    }
   return numbers; 
}

void array_adding(int numbers[], const int x){
    int user_numbers;
    printf("Enter numbers for array: ");
    while( scanf("%d", &user_numbers) != 1){
        printf("Invalid Input: Please try again: ");
        while (getchar() != '\n');
    }

    numbers[x] = user_numbers;
}

int main(){
    int count;
    int x = 0; //assigned value first

    count = user_input();

    int *numbers = (int *)malloc(count * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("numbers of user wanted: %d\n ", count);

    while(x < count){ 
        printf("numbers:%d\n", x);

        array_adding(numbers, x);

        printf("successful\n");
        x++;
    }

    for(int i =0; i < count; i++){
        printf("array %d\n",numbers[i]);
    }

    return 0;
}