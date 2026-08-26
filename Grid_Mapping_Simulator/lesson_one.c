#include <stdio.h>      // standard input output
#include <stdlib.h>     //
#include <math.h>       // math eq like sqrt

#define GRID_SIZE           15
#define NUM_SENSORS         8
#define MAX_SONAR_RANGE     10.0f
#define PI                  3.14159265f

#define CELL_UNKNOWN        0
#define CELL_FREE           1
#define CELL_WALL           2

int robot_x = 7;
int robot_y = 7;

float sensor_headings[NUM_SENSORS] = {
    0.00f, 0.785f, 1.57f, 2.356f, 3.1415f, 3.927f, 4.712f, 5.497f
};

float sonar_reading[NUM_SENSORS];
int real_world_room[GRID_SIZE][GRID_SIZE];
int robot_internal_map[GRID_SIZE][GRID_SIZE];

void setup_environment(void) {
    for(int y = 0; y < GRID_SIZE; y++) {
        for(int x = 0; x < GRID_SIZE; x++) {
            if(x == 0 || x == GRID_SIZE - 1 || y == 0 || y == GRID_SIZE - 1) {
                real_world_room[y][x] = CELL_WALL;
            } else if((x == 4 && y == 4) || (x == 10 && y == 10) || (x == 4 && y == 10)) {
                real_world_room[y][x] = CELL_WALL; // Multiple internal obstacles
            } else {
                real_world_room[y][x] = CELL_FREE;
            }
            robot_internal_map[y][x] = CELL_UNKNOWN;
        }
    }
}

float simulate_sonar_range(float angle) {
    for(float dist = 0.1f; dist < MAX_SONAR_RANGE; dist += 0.1f) {
        int check_x = (int)roundf(robot_x + dist * cosf(angle));
        int check_y = (int)roundf(robot_y + dist * sinf(angle));

        if(check_x >= 0 && check_x < GRID_SIZE && check_y >= 0 && check_y < GRID_SIZE) {
            if(real_world_room[check_y][check_x] == CELL_WALL) {
                return dist;
            }
        } else {
            return dist;
        }
    }
    return MAX_SONAR_RANGE;
}

void mapping_algorithms(void) {
    for(int i = 0; i < NUM_SENSORS; i++) {
        sonar_reading[i] = simulate_sonar_range(sensor_headings[i]);
    }

    for(int i = 0; i < NUM_SENSORS; i++) {
        float angle = sensor_headings[i];
        float hit_dist = sonar_reading[i];

        // Mark free path along ray
        for(float d = 0.2f; d < hit_dist - 0.3f; d += 0.2f) {
            int cx = (int)roundf(robot_x + d * cosf(angle));
            int cy = (int)roundf(robot_y + d * sinf(angle));

            if(cx >= 0 && cx < GRID_SIZE && cy >= 0 && cy < GRID_SIZE) {
                if(robot_internal_map[cy][cx] != CELL_WALL) {
                    robot_internal_map[cy][cx] = CELL_FREE;
                }
            }
        }

        // Mark wall collision point
        if(hit_dist < MAX_SONAR_RANGE) {
            int wx = (int)roundf(robot_x + hit_dist * cosf(angle));
            int wy = (int)roundf(robot_y + hit_dist * sinf(angle));

            if(wx >= 0 && wx < GRID_SIZE && wy >= 0 && wy < GRID_SIZE) {
                robot_internal_map[wy][wx] = CELL_WALL;
            }
        }
    }
}

void print_robot_map(void) {
    // Clear screen (Linux/macOS ANSI clear sequence)
    printf("\033[H\033[J");
    
    printf("=== 2D ROBOT SLAM SIMULATOR ===\n\n");
    for(int y = GRID_SIZE - 1; y >= 0; y--) {
        for(int x = 0; x < GRID_SIZE; x++) {
            if(x == robot_x && y == robot_y) printf("R ");
            else if(robot_internal_map[y][x] == CELL_WALL) printf("█ ");
            else if(robot_internal_map[y][x] == CELL_FREE) printf(". ");
            else printf("? ");
        }
        printf("\n");
    }
    printf("\nControls: [W] Up | [A] Left | [S] Down | [D] Right | [Q] Quit\n");
}

void move_robot(char dir) {
    int new_x = robot_x;
    int new_y = robot_y;

    if(dir == 'w' || dir == 'W') new_y++;
    if(dir == 's' || dir == 'S') new_y--;
    if(dir == 'a' || dir == 'A') new_x--;
    if(dir == 'd' || dir == 'D') new_x++;

    // Collision check against real world environment
    if(new_x >= 0 && new_x < GRID_SIZE && new_y >= 0 && new_y < GRID_SIZE) {
        if(real_world_room[new_y][new_x] != CELL_WALL) {
            robot_x = new_x;
            robot_y = new_y;
        }
    }
}

int main(void) {
    setup_environment();
    char command = ' ';

    while(command != 'q' && command != 'Q') {
        mapping_algorithms();
        print_robot_map();

        printf("Enter move command: ");
        if(scanf(" %c", &command) != 1) break;

        if(command != 'q' && command != 'Q') {
            move_robot(command);
        }
    }

    printf("\nSimulation ended.\n");
    return 0;
}