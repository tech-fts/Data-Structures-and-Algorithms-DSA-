#include <stdio.h>
#include "motorcontrol/motor.h"
#include "motorcontrol/controller.c"

int main(){

    StapperMotor motor;
    init_motor(&motor, 1);

    if(is_motor_queue_empty(&(motor.command_queue)) && motor.state == MOTOR_IDLE){
        printf("Motor is idle and command queue is empty.\n");
        set_command(&motor, "MOVE", 100);
    }
    return 0;
}