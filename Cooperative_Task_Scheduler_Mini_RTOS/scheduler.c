#include <stdio.h>
#include "scheduler.h"

static MinHeap_t task_heap;

static void min_heap_insert(Task_t task){
    if(task_heap.size >= MAX_TASK) return;

    int x = task_heap.size;
    task_heap.array[x] = task;
    task_heap.size++;

    while( x != 0 && is_eariler(task_heap.array[x], task_heap.array[(x-1)/2])){
        swap(&task_heap.array[x], &task_heap.array[(x-1)/2]);
        x = (x -1)/2;
    }
}

void scheduler_init(void){
    task_heap.size = 0;
}

bool scheduler_add_task(Taskfunction taskfunc, uint32_t interval, int priority){ // need to declare usage inside function
    if(task_heap.size >= MAX_TASK || taskfunc == NULL) return false;

    Task_t new_task = {
        .execute = taskfunc,
        .interval_ms = interval,
        .next_run_time = 0,
        .priority = priority
    };

    min_heap_insert(new_task);
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