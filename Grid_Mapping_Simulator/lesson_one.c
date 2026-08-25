#include <stdio.h>

#define GRID_SIZE           15
#define NUM_SENSORS         8
#define MAX_SORNER_RANGE    10.0f
#define CONE_HALF_ANGLE     0.26f
#define PI                  3.14159265f

#define CELL_UNKNOWN        0
#define CELL_FREE           1
#define CELL_WALL           2

int robot_x = 7;
int robot_y = 7;

//sensor heading degree
float sensor_headings[NUM_SENSORS] = {
    0.00f, 0.78f, 1.57f, 2.35f, 3.14f, 3.92f, 4.71f, 5.49f
};

float sonar_reading[NUM_SENSORS];

int real_world_room[GRID_SIZE][GRID_SIZE];
int robot_internal_map[GRID_SIZE][GRID_SIZE];

void setup_environment(void){
    for(int y =0; y< GRID_SIZE; y++){
        printf("%d\n", y);
        for(int x=0; x< GRID_SIZE; x++){
            printf("%d\n", x);

            if(x == 0 || x == GRID_SIZE -1 || y == 0 || y == GRID_SIZE - 1){
                real_world_room[y][x] = CELL_WALL;
                printf("wall creation %d", CELL_WALL);
            }
        }
    }
}


int main(){
    printf("This is start of the project...\n");
    setup_environment();
    return 0;
}