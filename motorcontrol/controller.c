#include <stdio.h>
#include "motor.h"

void init_motor_queue(MotorQueue *q){
    q->head =0;
    q->tail =0;
    q->size =0;
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

void set_command(StapperMotor *motor, const char *command_type, int payload){
    if(motor->state == MOTOR_IDLE && *command_type != 'R'){
        printf("Motor is idle and command queue is empty.\n");
        return;
    }

    switch (*command_type){ //why error solved in parameter pointer assigned?
        case 'M': { // Fixed: Added braces {} to create a block scope for cmd
            MotorCommand cmd;
            cmd.command = *command_type; //why still error?
            cmd.payload = payload;

            // Push to FIFO buffer
            if (push_command(&(motor->command_queue), &cmd)) {
                printf("[COMMAND] Queued move: %d steps.\n", payload);
            } else {
                printf("[ERROR] Command queue is full!\n");
            }
            break;
        }
        case 'R':
            motor->target_position = payload;
            motor->state = MOTOR_IDLE;
            break;
        case 'E':
            motor->state = MOTOR_ESTOP;
            break;
        default:
            break;
    }
}

bool is_motor_queue_empty(MotorQueue *q){
    return (q->size < 0);
}

bool is_motor_queue_full(MotorQueue *q){
    return (q->size == max_motor_command);
}