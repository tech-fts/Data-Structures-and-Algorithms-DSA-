#include <stdio.h>
#include "motorcontrol/motor.h"

void init_motor(StapperMotor *motor, int motor_id) {
    motor->motor_id = motor_id;
    motor->current_position = 0;
    motor->target_position = 0;
    motor->speed = 0;
    motor->state = MOTOR_IDLE;

    init_motor_queue(&(motor->command_queue));
}