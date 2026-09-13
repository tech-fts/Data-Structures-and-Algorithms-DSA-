#include <stdio.h>
#include "scheduler.h"

static MinHeap_t task_heap;

static void swap(Task_t *a, Task_t *b){
    Task_t temp = *a;
    *a = *b;
    *b = temp;
}

static bool is_eariler(Task_t a, Task_t b){
    if(a.next_run_time != b.next_run_time){
        return a.next_run_time < b.next_run_time;
    }
    return a.priority < b.priority;
}

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

static Task_t min_heap_extract_min(void){
    if(task_heap.size <= 0){
        Task_t empty = {NULL , 0, 0, 0};
        return empty;
    }

    Task_t root = task_heap.array[0];
    task_heap.array[0] = task_heap.array[task_heap.size -1];
    task_heap.size--;

    int x = 0;
    while(true){
        int left = 2*x+1;
        int right = 2*x +2;
        int smallest = x;

        if(left < task_heap.size && is_eariler(task_heap.array[left], task_heap.array[smallest])){
            smallest = left;
        }
        if(right < task_heap.size && is_eariler(task_heap.array[right], task_heap.array[smallest])){
            smallest = right;
        }

        if(smallest != x){
            swap(&task_heap.array[x], &task_heap.array[smallest]);
            x = smallest;
        }else{
            break;
        }
    }
    return root;
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
    while(task_heap.size > 0 && current_time_ms >= task_heap.array[0].next_run_time){
        Task_t current_task = min_heap_extract_min();

        if(current_task.execute != NULL){
            current_task.execute();
        }

        current_task.next_run_time += current_task.interval_ms;
        min_heap_insert(current_task);
    }
}