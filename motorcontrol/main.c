#include <stdio.h>
#include "motor.h"

int main(){

    StapperMotor motor;
    init_motor(&motor, 1);

    if(is_motor_queue_empty(&(motor.command_queue)) && motor.state == MOTOR_IDLE){
        printf("Motor is idle and command queue is empty.\n");
        set_command(&motor, "M", 100);
    }
    return 0;
}