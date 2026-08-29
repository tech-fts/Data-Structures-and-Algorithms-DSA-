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
    while( scanf("%d", &user_numbers) != 1 && user_numbers > 1){
        printf("Invalid Input: Please try again: ");
        while (getchar() != '\n');
    }

    numbers[x] = user_numbers;
}

int main(){
    int count;
    int x = 0; //assigned value first
    int *numbers = NULL;

    while(1){
        int user_opt;
        
    
        printf("Please enter option: \n");
        printf("1. array added: \n");
        printf("2. array element delete: \n");
        printf("3. exit\n");

        while (scanf("%d", &user_opt) != 1)
        {
            printf("Invalid value.Please enter again: ");
            while(getchar() != '\n');
        }

        if (user_opt == 1){
            count = user_input();

            numbers = (int *)malloc(count * sizeof(int));
            if (numbers == NULL) {
                printf("Memory allocation failed!\n");
                return 1;
            }

            printf("numbers of user wanted: %d\n ", count);
            int x = 0;
            while(x < count){ // this condition check user want to add element to array
                printf("numbers:%d\n", x);

                array_adding(numbers, x);

                printf("successful\n");
                x++;
            }

            for(int i =0; i < count; i++){
                printf("array %d\n",numbers[i]);
            }
        }else if(user_opt == 2){
            if (count == 0 || numbers == NULL){
                printf("There is no data to delete inside this array!\n");
                continue; // Return to main menu instead of exiting program with return 0
            }

            int delete_element;
            printf("Enter number that you want to delete: ");
            while (scanf("%d", &delete_element) != 1) {
                printf("Invalid Input. Try again: ");
                while (getchar() != '\n');
            }

            int found_index = -1;
            for(int i = 0; i < count; i++){
                if(numbers[i] == delete_element){
                    found_index = i;
                    break;
                }
            }

            if (found_index != -1) {
                // Shift elements left to overwrite the target index
                for (int i = found_index; i < count - 1; i++) {
                    numbers[i] = numbers[i + 1];
                }
                count--; // Reduce count by 1 ONLY ONCE
                printf("Successfully deleted %d\n", delete_element);
            } else {
                printf("Number %d not found in array.\n", delete_element);
            }

            printf("\nUpdated array:\n");
            for(int i = 0; i < count; i++){
                printf("numbers[%d] = %d\n", i, numbers[i]);
            }

        } else if (user_opt == 3) {
            free(numbers);
            printf("Exiting program.\n");
            break;
        }
    }

    return 0;
}