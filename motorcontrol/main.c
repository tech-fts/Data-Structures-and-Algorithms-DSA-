#include <stdio.h>
#include "motor.h"

int main(){

    StapperMotor motor;
    init_motor(&motor, 1);

    if(is_motor_queue_empty(&(motor.command_queue)) && motor.state == MOTOR_IDLE){
        printf("Motor is idle and command queue is empty.\n");
    }

    printf("set command for motor control ");
    set_command(&motor, "M", 100);
    set_command(&motor, "M", 5);
    set_command(&motor, "M", 2);

    return 0;
}