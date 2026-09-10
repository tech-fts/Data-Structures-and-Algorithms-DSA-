#include <stdio.h>
#include "motor.h"

void init_motor_queue(MotorQueue *q){
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}

void init_motor(StapperMotor *motor, int motor_id) {
    motor->motor_id = motor_id;
    motor->current_position = 0;
    motor->target_position = 0;
    motor->speed = 0;
    motor->state = MOTOR_IDLE;
    init_motor_queue(&(motor->command_queue));
}

bool push_command(MotorQueue *queue, MotorCommand *cmd){
    if(is_motor_queue_full(queue)){
        return false;
    }
    queue->command[queue->head] = *cmd;
    queue->head = (queue->head + 1) % max_motor_command;
    queue->size++;
    return true;
}

bool pop_command(MotorQueue *queue, MotorCommand *cmd){
    if(is_motor_queue_empty(queue)){
        return false;
    }
    *cmd = queue->command[queue->tail];
    queue->tail = (queue->tail + 1) % max_motor_command;
    queue->size--;
    return true;
}

void set_command(StapperMotor *motor, const char *command_type, int payload){
    if(motor == NULL || command_type == NULL){
        return;
    }

    if(motor->state == MOTOR_ESTOP && *command_type != 'R'){
        printf("[ERROR] Motor in ESTOP. Only 'R' (reset) allowed.\n");
        return;
    }

    switch (*command_type){
        case 'M': {
            MotorCommand cmd;
            cmd.command = *command_type;
            cmd.payload = payload;
            if (push_command(&(motor->command_queue), &cmd)) {
                printf("[COMMAND] Queued move: %d steps.\n", payload);
            } else {
                printf("[ERROR] Command queue is full!\n");
            }
            break;
        }
        case 'R':
            if(motor->state == MOTOR_ESTOP){
                motor->state = MOTOR_IDLE;
                printf("[RESET] Emergency stop cleared. Motor ready.\n");
            }
            break;
        case 'S':
            motor->state = MOTOR_ESTOP;
            printf("[ESTOP] Motor emergency stopped.\n");
            break;
        default:
            printf("[ERROR] Unknown command: %c\n", *command_type);
            break;
    }
}

void run_motor(StapperMotor *motor){
    if(motor->state == MOTOR_ESTOP){
        return;
    }

    if(motor->state == MOTOR_IDLE && !is_motor_queue_empty(&motor->command_queue)){
        MotorCommand cmd;
        if(pop_command(&motor->command_queue, &cmd)){
            if(cmd.command == 'M'){
                motor->target_position = motor->current_position + cmd.payload;
                motor->state = MOTOR_RUNNING;
                printf("[RUN] Motor starting. Target: %d\n", motor->target_position);
            }
        }
    }

    if(motor->state == MOTOR_RUNNING){
        if(motor->current_position < motor->target_position){
            motor->current_position++;
            printf("[STEPPING] Motor position: %d\n", motor->current_position);
        } else if(motor->current_position > motor->target_position){
            motor->current_position--;
            printf("[STEPPING] Motor position: %d\n", motor->current_position);
        }

        if(motor->current_position == motor->target_position){
            printf("[COMPLETE] Motor reached target position: %d\n", motor->target_position);
            motor->state = MOTOR_IDLE;
        }
    }
}

bool is_motor_queue_empty(MotorQueue *q){
    return (q->size == 0);
}

bool is_motor_queue_full(MotorQueue *q){
    return (q->size == max_motor_command);
}