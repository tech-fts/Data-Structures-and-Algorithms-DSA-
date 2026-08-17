#include <stdio.h>
#include <math.h>

int main(){
    double x1,x2,y1,y2;

    printf("Enter value of x1: ");
    scanf("%d", &x1);

    printf("Enter value of x2: ");
    scanf("%d", &x2);

    printf("Enter value of y1: ");
    scanf("%d", &y1);

    printf("Enter value of y2: ");
    scanf("%d", &y2);

    if(x2>x1 && y2>y1){
        double ans1 = pow((x2-x1),2);
        double ans2 = pow((y2-y1),2);

        double d1 = sqrt(ans1+ans2);

        printf("The value of the distance is: %d", d1);
    } else {
        printf("\nError: Condition not met!\n");
        printf("Reason: x2 (%.2f) must be > x1 (%.2f) AND y2 (%.2f) must be > y1 (%.2f).\n", 
               x2, x1, y2, y1);
    }

    return 0;
}