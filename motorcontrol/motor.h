#ifndef MOTOR_H
#define MOTOR_H

#include <stdbool.h>
#define max_motor_command 10

typedef enum{ //this is state for motor run 
    MOTOR_IDLE,
    MOTOR_RUNNING,
    MOTOR_ESTOP,
} MotorState;

typedef struct{ //this is command for motor run
    char command;
    int payload;
} MotorCommand;

typedef struct{ //this is queue for motor command
    MotorCommand command[max_motor_command];
    int head;
    int tail;
    int size;
} MotorQueue;

typedef struct{ //this is motor data
    int motor_id;
    int current_position;
    int target_position;
    int speed;
    MotorState state; // this is declare for motor state
    MotorQueue command_queue; // this is declare for motor command queue
} StapperMotor;

//core motor function
void init_motor(StapperMotor *motor, int motor_id); //start motor with motor id
void set_command(StapperMotor *motor, const char *command, int payload); //set command for motor run
void run_motor(StapperMotor *motor);//run motor with command

//motor queue function
void init_motor_queue(MotorQueue *queue); //init motor queue
bool is_motor_queue_empty(MotorQueue *queue); //check motor queue is empty
bool is_motor_queue_full(MotorQueue *queue); //check motor queue is full
bool push_command(MotorQueue *queue, MotorCommand *cmd);
bool pop_command(MotorQueue *queue, MotorCommand *cmd);

#endif // MOTOR_H