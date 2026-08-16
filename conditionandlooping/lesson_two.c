#include <stdio.h>
#include <math.h>

void check_type(const char *format, void *address){
    while(scanf(format, address) != 1){
        printf("Invalid Input. Enter correct number for: ");

        while(getchar() != '\n');
    }
}

int main(){
    int a,b,c;

    int D1, x;

    printf("Enter a number for a: \n");
    check_type("%d", &a);

    printf("Enter a number for b: \n");
    check_type("%d", &b);

    printf("Enter a number for c: \n");
    check_type("%d", &c);

    D1 = (b*b) - (4*a*c);
    printf("%d", D1);

    if(D1 >= 0){
        double root = sqrt(D1);
        printf("Square root of discriminant: %lf\n", root);
    }else{
        printf("Discriminant is negative (complex roots).\n");
    }

    int ans1 = -b - sqrt(D1);
    int ans2 = -b + sqrt(D1);

    printf("%d", ans1, ans2);

    return 0;
}