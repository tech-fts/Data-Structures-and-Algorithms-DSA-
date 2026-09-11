#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*Taskfunction)(void);

typedef struct{
    Taskfunction execute;
    uint32_t interval_ms;
    uint32_t last_run_ms;
    bool is_active;
} Task_t;

void scheduler_init(void);
bool scheduler_add_task(Taskfunction taskfunc, uint32_t interval);
void scheduler_run(void);

#endif