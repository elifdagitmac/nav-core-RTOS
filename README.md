# NAV-CORE RTOS

A lightweight Real-Time Operating System (RTOS) kernel implemented on Arduino UNO,
featuring priority-based preemptive scheduling and interrupt-driven sensor management.

## Overview
NAV-CORE demonstrates core RTOS concepts in a real embedded environment:
a custom kernel manages three concurrent tasks with different priorities,
coordinated via timer interrupts and a linked-list task queue.

## Architecture
NAV-CORE/

├── kernel.cpp / kernel.h     # RTOS kernel: scheduler, task queue (linked list)

├── tasks.cpp / tasks.h       # Task definitions: Radar, Motor, SystemMonitor

├── NAV-CORE.ino              # Entry point: task registration, ISR, pin config

└── devre_semasi.png          # Circuit diagram

## Tasks
| Task | Priority | Function |
|---|---|---|
| Radar | 1 (highest) | Reads ultrasonic distance, triggers obstacle flag |
| Motor Control | 2 | Drives servo motors based on radar input |
| System Monitor | 3 | Logs system state via Serial |

## Key Concepts Implemented
- Priority-based preemptive scheduler
- Linked-list task queue
- Timer interrupt (ISR) for context switching
- Volatile shared variables for inter-task communication
- Sensor-driven task activation (active/passive state)

## Hardware
| Component | Pin |
|---|---|
| HC-SR04 Trig | 11 |
| HC-SR04 Echo | 2 (interrupt-capable) |
| Servo 1 (Tilt) | 9 |
| Servo 2 (Rotation) | 6 |

## Getting Started
1. Open `NAV-CORE.ino` in Arduino IDE
2. Connect components per circuit diagram (`devre_semasi.png`)
3. Select **Arduino UNO** and upload
4. Open Serial Monitor at **9600 baud** to observe task execution

## Simulation
> Coming soon — software simulation module for running without hardware.
