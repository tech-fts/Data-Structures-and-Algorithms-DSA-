#include <stdio.h>
#include <math.h>

void check_type(const char *format, void *address){
    while(scanf(format, address) != 1){
        printf("Invalid Input. Enter correct number for: ");

        while(getchar() != '\n');
    }
}

int main(){
    double a,b,c;

    printf("Enter a number for a: \n");
    check_type("%d", &a);

    printf("Enter a number for b: \n");
    check_type("%d", &b);

    printf("Enter a number for c: \n");
    check_type("%d", &c);

    double D1 = (b*b) - (4*a*c);
    printf("%d\n", D1);

    if (D1 > 0) {
        double ans1 = (-b + sqrt(D1)) / (2.0 * a);
        double ans2 = (-b - sqrt(D1)) / (2.0 * a);
        
        printf("Two real roots:\n");
        printf("x1 = %.2f\n", ans1);
        printf("x2 = %.2f\n", ans2);
    }
    else if (D1 == 0) {
        double ans = -b / (2.0 * a);
        printf("One real (repeated) root:\n");
        printf("x = %.2f\n", ans);
    }else{
        double realPart = -b / (2.0 * a);
        double imagPart = sqrt(-D1) / (2.0 * a);
        
        printf("Complex roots:\n");
        printf("x1 = %.2f + %.2fi\n", realPart, imagPart);
        printf("x2 = %.2f - %.2fi\n", realPart, imagPart);
    }

    return 0;
}