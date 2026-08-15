#include <stdio.h>

int main(){
    int numberone = 0; //need to be assign zero because other value assign to varibale 
    int numbertwo = 0;
    int total= 0;

    printf("Please enter numberone: \n");
    scanf("%d", &numberone);

    printf("Please enter numbertwo: \n");
    scanf("%d", &numbertwo);

    total  = numberone + numbertwo;

    printf("total of the two number is: %d", total);
    return 0;
}