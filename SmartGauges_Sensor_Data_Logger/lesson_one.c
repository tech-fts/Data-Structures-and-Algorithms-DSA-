#include <stdio.h>
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
    s1.temp = 25.4f;
    s1.pressure = 1013.25f;
    s1.status_code = 0;

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