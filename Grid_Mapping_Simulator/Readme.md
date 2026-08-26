# 2D Robot SLAM & Grid Mapping Simulator

A lightweight 2D Simultaneous Localization and Mapping (SLAM) and autonomous coverage simulator written in pure C. This project demonstrates raycasting-based range sensors (sonar/LiDAR), grid mapping techniques, and various autonomous navigation algorithms in terminal-rendered environments.

---

## Features

- **Raycasting Sonar Simulation**: Simulates omnidirectional distance sensors using trigonometric raycasting (`cosf`/`sinf`) to detect obstacles.
- **Occupancy Grid Mapping**: Build real-time internal maps categorized into **Unknown (`?`)**, **Free Space (`.`)**, and **Walls (`█`)**.
- **Interactive & Autonomous Navigation**:
  - **Lesson 1**: Direct manual control via WASD keys.
  - **Lesson 2**: Full autonomous exploration featuring lawnmower sweeps, perimeter/wall following, and random bounce modes.
- **Dynamic Configuration**: Adjustable grid sizes, sensor counts, simulation speed, and room layouts.
- **Cross-Platform Output**: Uses ANSI control sequences for smooth terminal rendering on Linux, macOS, and Windows.

---

## Program Versions

### `lesson_one.c` — Manual Grid Mapper
An interactive 15x15 terminal application where you manually pilot the robot. As you move, the robot fires 8 simulated sonar sensors to dynamically discover obstacles and chart its internal map.

### `lesson_two.c` — Autonomous Exploration & Obstacle Avoidance
An enhanced, fully automated simulation that dynamically allocates memory for user-configured environments. Features obstacle-bypassing state machines and live coverage percentage metrics.

---

## Algorithms Included

| Algorithm Mode | Description | Key Mechanism |
| :--- | :--- | :--- |
| **Horizontal Sweep** | Zig-zag lawnmower pattern across rows. | Bypasses obstacles via dynamic vertical detours. |
| **Vertical Sweep** | Column-by-column lawnmower coverage. | Bypasses obstacles via horizontal detours. |
| **Wall Follower** | Perimeter-crawling algorithm. | Right-hand rule maintaining contact with walls. |
| **Random Bounce** | Stochastic area coverage model. | Bounces off obstacles in random trajectories. |

---

## Build & Run Instructions

### Prerequisites
- C Compiler (`gcc`, `clang`, or MSVC)
- C Standard Library (`math` library support)

### Compiling

Using `gcc`:

```bash
# Compile Lesson 1 (Manual Control)
gcc -O2 lesson_one.c -o lesson_one -lm

# Compile Lesson 2 (Autonomous Navigation)
gcc -O2 lesson_two.c -o lesson_two -lm