# Stepper Motor State Machine & Command Parser

A lightweight, bare-metal C simulation of an industrial stepper motor controller. This project models a real-world mechatronic firmware design by using a finite state machine (FSM), command parsing, and pointer-based state updates without relying on external libraries or dynamic memory.

---

## Key Features

- Finite State Machine (FSM): tracks discrete states such as IDLE, RUNNING, and ESTOP.
- Command parser: recognizes movement, stop, and reset commands safely.
- Safety lockout: ignores movement commands while in emergency stop until reset.
- Non-blocking pulse simulation: models stepping logic in a modular loop.
- Clean architecture: separates configuration, controller logic, and main execution flow.

---

## Project Structure

```text
motor_controller/
├── motor.h       # Configuration, state definitions, and function signatures
├── controller.c  # Core state machine logic and command parsing
├── main.c        # Firmware execution loop simulation
└── README.md     # Project overview and usage notes
```

---

## State Flow

```text
      [ IDLE ] <---- (Command 'R' / target reached) ----+
         ^                                                  |
         |                                                  |
 (Command 'M')                                           (Command 'S')
         |                                                  |
         v                                                  v
     [ RUNNING ] --------- (Command 'S') --------> [ EMERGENCY STOP ]
```

### Motor states

- `MOTOR_IDLE (0)`: system initialized and ready for movement commands.
- `MOTOR_RUNNING (1)`: motor is actively stepping toward a target position.
- `MOTOR_ESTOP (2)`: critical state; movement commands are ignored until reset.

---

## Supported Commands

| Code | Command | Description | Payload |
|------|---------|-------------|---------|
| `M` | Move | Sets target step position and transitions to RUNNING | target position (integer steps) |
| `S` | Stop | Immediately triggers an emergency stop | ignored |
| `R` | Reset | Clears ESTOP fault and restores the system to IDLE | ignored |

---

## Notes

This project is intended as a learning-oriented simulation of how embedded controllers use state transitions and command validation to safely manage hardware movement.