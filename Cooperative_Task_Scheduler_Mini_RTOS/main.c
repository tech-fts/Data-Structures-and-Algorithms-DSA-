#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "scheduler.h"

//need to declare simulated_time
uint32_t simulated_time= 0;

//hardware function
void task_blink_led(void){
    printf("[TIME: %d ms] LED toggled!\n", simulated_time);
}

void task_read_sensor(void){
    printf("[TIME: %d ms] Reading temperature... 24.5 C\n", simulated_time);
}

void task_update_screen(void){
    printf("[TIME: %d ms] --- Screen Refreshed ---\n", simulated_time);
}

int main(){
    printf("Booting Cooperative OS...\n");

    scheduler_add_task(task_blink_led, 500);
    scheduler_add_task(task_read_sensor, 200);
    scheduler_add_task(task_update_screen, 1000);

    printf("Scheduler running. Press Ctrl+C to stop.\n\n");

    while (1)
    {
        scheduler_run(simulated_time);

        #ifdef _WIN32
        Sleep(1)
        #else
        usleep(1000);
        #endif

        simulated_time++;
    }
    
    return 0;
}