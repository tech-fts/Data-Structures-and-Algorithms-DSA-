#include <stdio.h>
#include <stdint.h>

struct Sensor {
    char timestamp[20];   // Formatted time string: "YYYY-MM-DD HH:MM:SS" + null terminator
    float temp;           // Temperature reading (e.g., 23.45)
    float pressure;       // Pressure reading (e.g., 101.32)
    uint8_t status_code;
};

int main(){
    return 0;
}