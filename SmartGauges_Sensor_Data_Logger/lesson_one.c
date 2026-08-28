#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

struct Sensor {
    char timestamp[25];  // Increased slightly for safety  
    float temp;           
    float pressure;       
    uint8_t status_code;
};

void getCustomTimestamp(char *buffer, size_t max_size) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, max_size, "%Y-%m-%d %H:%M:%S", timeinfo);
}

float get_temp(){
    return 20.0f + ((float)rand() /(float)RAND_MAX) * 15.0f;
}

float get_pressure(){
    return 98.0f + ((float)rand()/(float)RAND_MAX) * 7.0f;
}

uint8_t get_status(float temp, float pressure) {
    if (temp > 32.0f) return 1;       // High Temp Warning
    if (pressure > 103.5f) return 2;   // High Pressure Warning
    return 0;                          // System OK
}

int main() {
    FILE *fptr;
    printf("Start of the project.\n");

    fptr = fopen("log.csv", "a+");
    if (fptr == NULL) {
        printf("There is no file in this project...\n");
        return 1; // Stop execution if file failed to open
    }

    struct Sensor s1;

    // 1. Fill timestamp directly into s1.timestamp
    getCustomTimestamp(s1.timestamp, sizeof(s1.timestamp));

    // 2. Assign remaining struct values
    s1.temp = get_temp();
    s1.pressure = get_pressure();
    s1.status_code = get_status(s1.temp);

    // 3. Write formatted string (%s for timestamp)
    fprintf(fptr, "%s,%.2f,%.2f,%u\n", 
            s1.timestamp, 
            s1.temp, 
            s1.pressure, 
            s1.status_code);

    fclose(fptr);
    printf("Data successfully logged!\n");
    return 0;
}