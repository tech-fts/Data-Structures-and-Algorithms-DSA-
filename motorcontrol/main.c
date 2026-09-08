#include <stdio.h>
#include "motorcontrol/motor.h"
#include "motorcontrol/controller.c"

int main(){

    StapperMotor motor;
    init_motor(&motor, 1);
    return 0;
}