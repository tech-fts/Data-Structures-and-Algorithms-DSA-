#include <stdio.h>
#include "scheduler.h"

static Task_t task_list[MAX_TASK];
static uint8_t task_count;

void scheduler_init(void){
    task_count = 0;
    for(int i=0; i < MAX_TASK; i++){
        task_list[i].is_active = false;
    }
}

bool scheduler_add_task(Taskfunction taskfunc, uint32_t interval){
    if(task_count >= MAX_TASK){
        return false;
    }

    task_list[task_count].execute = taskfunc;
    task_list[task_count].interval_ms = interval;
    task_list[task_count].last_run_ms = 0;
    task_list[task_count].is_active = false;

    task_count++;
    return true;
}

void scheduler_run(uint32_t current_time_ms){
    for(int x=0; x<task_count; x++){
        if(!task_list[x].is_active)continue;

        if(current_time_ms - task_list[x].last_run_ms  >= task_list[x].interval_ms){
            task_list[x].last_run_ms = current_time_ms;
            task_list[x].execute();
        }
    }
}