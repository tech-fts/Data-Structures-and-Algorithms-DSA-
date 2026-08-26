#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
  #include <windows.h>
  #define sleep_ms(ms) Sleep(ms)
#else
  #include <unistd.h>
  #define sleep_ms(ms) usleep((ms) * 1000)
#endif

#define MAX_SONAR_RANGE     10.0f
#define PI                  3.14159265f

#define CELL_UNKNOWN        0
#define CELL_FREE           1
#define CELL_WALL           2

int grid_size = 15;
int num_sensors = 8;
int delay_ms = 300;

int room_shape_choice = 1;
int movement_mode_choice = 1;

int robot_x = 1;
int robot_y = 1;

// Movement & Bypass State
int dir_x = 1;           // 1 = Right, -1 = Left
int dir_y = 1;           // 1 = Up, -1 = Down
int bypass_state = 0;    // 0: Normal sweep, 1: Detouring
int original_pos = 1;    // Holds row/col before detour

float *sensor_headings = NULL;
float *sonar_reading = NULL;

int **real_world_room;
int **robot_internal_map;

int** allocate_grid(int size) {
    int **grid = (int**)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) {
        grid[i] = (int*)malloc(size * sizeof(int));
    }
    return grid;
}

void free_grid(int **grid, int size) {
    for(int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}

void setup_sensors(int count) {
    sensor_headings = (float*)malloc(count * sizeof(float));
    sonar_reading = (float*)malloc(count * sizeof(float));

    float step = (2.0f * PI) / count;
    for(int i = 0; i < count; i++) {
        sensor_headings[i] = i * step;
    }
}

// Generates the real-world environment layout based on user selection
void setup_environment(int shape) {
    for(int y = 0; y < grid_size; y++) {
        for(int x = 0; x < grid_size; x++) {
            // Default outer boundary walls
            if(x == 0 || x == grid_size - 1 || y == 0 || y == grid_size - 1) {
                real_world_room[y][x] = CELL_WALL;
            } else {
                real_world_room[y][x] = CELL_FREE;
            }
            robot_internal_map[y][x] = CELL_UNKNOWN;
        }
    }

    switch(shape) {
        case 1: // Standard with 3 Pillars
            real_world_room[grid_size/3][grid_size/3] = CELL_WALL;
            real_world_room[2*grid_size/3][2*grid_size/3] = CELL_WALL;
            real_world_room[2*grid_size/3][grid_size/3] = CELL_WALL;
            break;

        case 2: // Empty Box Room
            // Outer walls only (already set above)
            break;

        case 3: // Donut / Central Structure Room
            for(int y = grid_size/3; y <= 2*grid_size/3; y++) {
                for(int x = grid_size/3; x <= 2*grid_size/3; x++) {
                    real_world_room[y][x] = CELL_WALL;
                }
            }
            break;

        case 4: // L-Shaped Room (Blocks top-right quadrant)
            for(int y = grid_size/2; y < grid_size - 1; y++) {
                for(int x = grid_size/2; x < grid_size - 1; x++) {
                    real_world_room[y][x] = CELL_WALL;
                }
            }
            break;

        default:
            break;
    }
}

float simulate_sonar_range(float angle) {
    for(float dist = 0.1f; dist < MAX_SONAR_RANGE; dist += 0.1f) {
        int check_x = (int)roundf(robot_x + dist * cosf(angle));
        int check_y = (int)roundf(robot_y + dist * sinf(angle));

        if(check_x >= 0 && check_x < grid_size && check_y >= 0 && check_y < grid_size) {
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
    for(int i = 0; i < num_sensors; i++) {
        sonar_reading[i] = simulate_sonar_range(sensor_headings[i]);
    }

    for(int i = 0; i < num_sensors; i++) {
        float angle = sensor_headings[i];
        float hit_dist = sonar_reading[i];

        for(float d = 0.2f; d < hit_dist - 0.3f; d += 0.2f) {
            int cx = (int)roundf(robot_x + d * cosf(angle));
            int cy = (int)roundf(robot_y + d * sinf(angle));

            if(cx >= 0 && cx < grid_size && cy >= 0 && cy < grid_size) {
                if(robot_internal_map[cy][cx] != CELL_WALL) {
                    robot_internal_map[cy][cx] = CELL_FREE;
                }
            }
        }

        if(hit_dist < MAX_SONAR_RANGE) {
            int wx = (int)roundf(robot_x + hit_dist * cosf(angle));
            int wy = (int)roundf(robot_y + hit_dist * sinf(angle));

            if(wx >= 0 && wx < grid_size && wy >= 0 && wy < grid_size) {
                robot_internal_map[wy][wx] = CELL_WALL;
            }
        }
    }
}

int is_walkable(int x, int y) {
    if(x <= 0 || x >= grid_size - 1 || y <= 0 || y >= grid_size - 1) return 0;
    return real_world_room[y][x] != CELL_WALL;
}

// 1. Horizontal Lawnmower Pattern
void move_horizontal_sweep(void) {
    if(bypass_state == 1) {
        int next_x = robot_x + dir_x;
        if(is_walkable(next_x, robot_y)) {
            robot_x = next_x;
            if(is_walkable(robot_x, original_pos)) {
                robot_y = original_pos;
                bypass_state = 0;
            }
            return;
        }
    }

    int next_x = robot_x + dir_x;
    if(is_walkable(next_x, robot_y)) {
        robot_x = next_x;
        return;
    }

    if(next_x <= 0 || next_x >= grid_size - 1) {
        int next_y = robot_y + dir_y;
        if(!is_walkable(robot_x, next_y)) {
            dir_y = -dir_y;
            next_y = robot_y + dir_y;
        }
        if(is_walkable(robot_x, next_y)) {
            robot_y = next_y;
        }
        dir_x = -dir_x;
        bypass_state = 0;
        return;
    }

    original_pos = robot_y;
    int detour_y = robot_y + dir_y;
    if(!is_walkable(robot_x, detour_y)) detour_y = robot_y - dir_y;

    if(is_walkable(robot_x, detour_y)) {
        robot_y = detour_y;
        bypass_state = 1;
    } else {
        dir_x = -dir_x;
    }
}

// 2. Vertical Lawnmower Pattern
void move_vertical_sweep(void) {
    if(bypass_state == 1) {
        int next_y = robot_y + dir_y;
        if(is_walkable(robot_x, next_y)) {
            robot_y = next_y;
            if(is_walkable(original_pos, robot_y)) {
                robot_x = original_pos;
                bypass_state = 0;
            }
            return;
        }
    }

    int next_y = robot_y + dir_y;
    if(is_walkable(robot_x, next_y)) {
        robot_y = next_y;
        return;
    }

    if(next_y <= 0 || next_y >= grid_size - 1) {
        int next_x = robot_x + dir_x;
        if(!is_walkable(next_x, robot_y)) {
            dir_x = -dir_x;
            next_x = robot_x + dir_x;
        }
        if(is_walkable(next_x, robot_y)) {
            robot_x = next_x;
        }
        dir_y = -dir_y;
        bypass_state = 0;
        return;
    }

    original_pos = robot_x;
    int detour_x = robot_x + dir_x;
    if(!is_walkable(detour_x, robot_y)) detour_x = robot_x - dir_x;

    if(is_walkable(detour_x, robot_y)) {
        robot_x = detour_x;
        bypass_state = 1;
    } else {
        dir_y = -dir_y;
    }
}

// 3. Perimeter (Wall Following) Movement
void move_wall_follower(void) {
    int right_x = robot_x + dir_y;
    int right_y = robot_y - dir_x;

    int forward_x = robot_x + dir_x;
    int forward_y = robot_y + dir_y;

    if(is_walkable(right_x, right_y)) {
        int temp = dir_x;
        dir_x = dir_y;
        dir_y = -temp;
        robot_x = right_x;
        robot_y = right_y;
    } else if(is_walkable(forward_x, forward_y)) {
        robot_x = forward_x;
        robot_y = forward_y;
    } else {
        int temp = dir_x;
        dir_x = -dir_y;
        dir_y = temp;
    }
}

// 4. Random Bounce Movement
void move_random_bounce(void) {
    int next_x = robot_x + dir_x;
    int next_y = robot_y + dir_y;

    if(is_walkable(next_x, next_y)) {
        robot_x = next_x;
        robot_y = next_y;
    } else {
        dir_x = (rand() % 3) - 1; 
        dir_y = (rand() % 3) - 1;
        if(dir_x == 0 && dir_y == 0) dir_x = 1;
    }
}

void auto_move_robot(int mode) {
    switch(mode) {
        case 1: move_horizontal_sweep(); break;
        case 2: move_vertical_sweep(); break;
        case 3: move_wall_follower(); break;
        case 4: move_random_bounce(); break;
        default: move_horizontal_sweep(); break;
    }
}

float calculate_coverage(void) {
    int total_cells = grid_size * grid_size;
    int explored_cells = 0;

    for(int y = 0; y < grid_size; y++) {
        for(int x = 0; x < grid_size; x++) {
            if(robot_internal_map[y][x] != CELL_UNKNOWN) {
                explored_cells++;
            }
        }
    }

    return ((float)explored_cells / total_cells) * 100.0f;
}

void print_robot_map(int step) {
    printf("\033[H\033[J");
    
    printf("=== OBSTACLE-AVOIDANCE SLAM SIMULATOR (%dx%d) ===\n", grid_size, grid_size);
    printf("Step: %d | Position: (%d, %d) | Coverage: %.1f%%\n\n", 
           step, robot_x, robot_y, calculate_coverage());
    
    for(int y = grid_size - 1; y >= 0; y--) {
        for(int x = 0; x < grid_size; x++) {
            if(x == robot_x && y == robot_y) printf("R ");
            else if(robot_internal_map[y][x] == CELL_WALL) printf("█ ");
            else if(robot_internal_map[y][x] == CELL_FREE) printf(". ");
            else printf("? ");
        }
        printf("\n");
    }
    printf("\nLegend: R=Robot, █=Wall, .=Free Space, ?=Unexplored\n");
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("Enter grid size (min 8, max 50): ");
    if(scanf("%d", &grid_size) != 1 || grid_size < 8) grid_size = 15;

    printf("Enter number of sonar sensors (min 4, max 36): ");
    if(scanf("%d", &num_sensors) != 1 || num_sensors < 4) num_sensors = 8;

    printf("\nSelect Room Shape:\n 1) Pillars (Standard)\n 2) Empty Room\n 3) Donut / Central Wall\n 4) L-Shaped Room\nEnter choice (1-4): ");
    if(scanf("%d", &room_shape_choice) != 1) room_shape_choice = 1;

    printf("\nSelect Movement Pattern:\n 1) Horizontal Lawnmower (Zig-Zag)\n 2) Vertical Lawnmower\n 3) Wall Follower (Perimeter)\n 4) Random Bounce\nEnter choice (1-4): ");
    if(scanf("%d", &movement_mode_choice) != 1) movement_mode_choice = 1;

    printf("\nSelect Speed:\n 1) Fast (150ms)\n 2) Medium (300ms)\n 3) Slow (500ms)\nEnter choice (1-3): ");
    int speed_choice = 2;
    if(scanf("%d", &speed_choice) == 1) {
        switch(speed_choice) {
            case 1: delay_ms = 150; break;
            case 2: delay_ms = 300; break;
            case 3: delay_ms = 500; break;
            default: delay_ms = 300; break;
        }
    }
    
    robot_x = 1;
    robot_y = 1;

    setup_sensors(num_sensors);
    real_world_room = allocate_grid(grid_size);
    robot_internal_map = allocate_grid(grid_size);

    setup_environment(room_shape_choice);

    int max_steps = grid_size * grid_size * 2;
    int step = 1;

    while(step <= max_steps) {
        mapping_algorithms();
        print_robot_map(step);

        auto_move_robot(movement_mode_choice);
        sleep_ms(delay_ms);
        step++;
    }

    free(sensor_headings);
    free(sonar_reading);
    free_grid(real_world_room, grid_size);
    free_grid(robot_internal_map, grid_size);

    printf("Exploration complete after %d steps.\n", step - 1);
    return 0;
}