#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_TASK 10

typedef void (*Taskfunction)(void);

typedef struct{
    Taskfunction execute;
    uint32_t interval_ms;
    uint32_t next_run_time; //change name
    int priority;
} Task_t;

typedef struct{
    Task_t array[MAX_TASK];
    int size;
} MinHeap_t;

void scheduler_init(void);
bool scheduler_add_task(Taskfunction taskfunc, uint32_t interval, int priority);
void scheduler_run(uint32_t current_time_ms); //fixed wrong parameter

#endif