#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

        for(int x=0; x< GRID_SIZE; x++){

            //build outer boundary wall
            if(x == 0 || x == GRID_SIZE -1 || y == 0 || y == GRID_SIZE - 1){
                real_world_room[y][x] = CELL_WALL;
            }
            // created internal obstacle
            else if(x == 4 && y == 4){
                real_world_room[y][x] = CELL_WALL;
            }
            else{
                real_world_room[y][x] = CELL_FREE;
            }

            robot_internal_map[y][x] = CELL_UNKNOWN;
        }
    }
}

float simulate_sonar_range(float angle){
    for(float dist = 0.5f; dist < MAX_SORNER_RANGE; dist += 0.5f){
        int check_x = robot_x + (int)roundf(dist * cosf(angle));
        int check_y = robot_y + (int)roundf(dist * sinf(angle));

        if(check_x >= 0 && check_x < GRID_SIZE && check_y >= 0 && check_y < GRID_SIZE){
            if(real_world_room[check_y][check_x] == CELL_WALL){
                return dist;
            }
        }   
    }
    return MAX_SORNER_RANGE;
}

void  mapping_algorithms(void){
    for(int i = 0; i < NUM_SENSORS; i++){
        sonar_reading[i] = simulate_sonar_range(sensor_headings[i]);
        printf("%.2f\n",sonar_reading[i]);
    }

    for(int x = 0; x < GRID_SIZE; x++){
        for(int y=x; y < GRID_SIZE; y++){
            if(x == robot_x &&  y == robot_y) continue;

            float dx = (float)(x - robot_x);
            float dy = (float)(y - robot_y);

            float cell_dist = sqrtf(dx*dx + dy*dy);
            float cell_ang = atan2f(dy, dx);

            if(cell_ang < 0) cell_ang += 2.0f * PI;

            for(int i = 0; i < NUM_SENSORS; i++){
                float diff = fabs(cell_ang - sensor_headings[i]);
                if(diff > PI) diff= (2.0f * PI) - diff;

                if (diff <= CONE_HALF_ANGLE){

                    if(cell_dist < (sonar_reading[i] - 0.4f)){
                        robot_internal_map[y][x] = CELL_FREE;
                    }

                    else if(fabs(cell_dist - sonar_reading[i]) <= 0.5f){
                        robot_internal_map[y][x] = CELL_WALL;
                    }
                }
            }
        }
    }
}

void print_robot_map(void) {
    printf("\n=== ACOUSTOSIM 2D - ROBOT MEMORY MAP ===\n\n");
    for(int y = GRID_SIZE - 1; y >= 0; y--) {
        for(int x = 0; x < GRID_SIZE; x++) {
            if(x == robot_x && y == robot_y) printf("R ");
            else if(robot_internal_map[y][x] == CELL_WALL) printf("█ ");
            else if(robot_internal_map[y][x] == CELL_FREE) printf(". ");
            else printf("? ");
        }
        printf("\n");
    }
    printf("\nLegend: R=Robot, █=Wall, .=Free Space, ?=Unexplored\n");
}

int main(){
    printf("This is start of the project...\n");
    setup_environment();
    mapping_algorithms();
    print_robot_map();
    return 0;
}