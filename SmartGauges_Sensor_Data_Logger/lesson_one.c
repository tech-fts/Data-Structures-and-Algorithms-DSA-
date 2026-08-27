#include <stdio.h>
#include <stdint.h>

struct Sensor {
    char timestamp[20];   
    float temp;           
    float pressure;       
    uint8_t status_code;
};

int main(){
    FILE *fptr;
    printf("Start of the project.");
    fptr = fopen("log.csv", "a+");
    if(fptr == NULL){
        printf("There is no file in this project...\n");
    };
    struct Sensor s1;
    
    fprintf(fptr, "timestamp temp pressure status_code");
    fclose(fptr);
    return 0;
}