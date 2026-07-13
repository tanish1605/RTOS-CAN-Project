# RTOS-CAN: Embedded RTOS Kernel with SocketCAN Integration

> A modular Real-Time Operating System (RTOS) kernel developed in C for ARM Cortex-M3, featuring priority-based task scheduling, task management, counting semaphores, and a SocketCAN (vCAN)-based event-driven demonstration framework.

---

## Overview

RTOS-CAN is an educational embedded systems project aimed at understanding the core building blocks of a Real-Time Operating System (RTOS). The project implements a modular kernel capable of task management, priority-based scheduling, synchronization using counting semaphores, and event-driven task dispatch through Linux SocketCAN (vCAN).

The firmware is cross-compiled for **ARM Cortex-M3** and executed using **QEMU**, while a Linux-based host demonstration simulates CAN communication and validates kernel behavior without requiring physical hardware.

---

## Features

- Task Control Blocks (TCBs)
- Priority-based Scheduler
- Task State Management
    - READY
    - RUNNING
    - BLOCKED
- Counting Semaphores
- Modular Kernel Architecture
- SocketCAN (vCAN) Integration
- ARM Cortex-M3 Cross Compilation
- QEMU Emulation
- GNU Make Build System

---

## Project Structure

```
RTOS-CAN
│
├── arch/          # Startup code and architecture-specific files
├── drivers/       # UART and SocketCAN drivers
├── host/          # Linux host demonstration
├── include/       # Header files
├── kernel/        # Scheduler, task management, semaphores
├── src/           # Firmware entry point
├── build/
├── Makefile
└── linker.ld
```

---

## RTOS Architecture

```
                +----------------------+
                |      Application     |
                +----------+-----------+
                           |
                           |
                    Task Creation API
                           |
                           ▼
                +----------------------+
                |   Task Control Block |
                +----------+-----------+
                           |
                           ▼
                +----------------------+
                | Priority Scheduler   |
                +----------+-----------+
                           |
                           ▼
                +----------------------+
                |   Selected Task      |
                +----------------------+
```

---

## Scheduler

The scheduler implements **priority-based task selection**.

Each task is represented using a **Task Control Block (TCB)** containing:

- Task Entry Function
- Stack Pointer
- Task Stack
- Priority
- Task State

Supported task states:

- READY
- RUNNING
- BLOCKED

The scheduler always selects the **highest-priority READY task**.

---

## Semaphore

The kernel provides a simple counting semaphore implementation for synchronization.

Supported operations:

```c
semaphore_init()

semaphore_take()

semaphore_give()
```

The host demonstration uses semaphores to emulate synchronization between incoming CAN events and task scheduling.

---

## SocketCAN Integration

The host demonstration integrates Linux **SocketCAN (vCAN)** to simulate event-driven RTOS behavior.

Incoming CAN messages activate specific RTOS tasks based on the received CAN ID.

Example mapping:

| CAN ID | Activated Task |
|---------|----------------|
| 0x100 | Telemetry Task |
| 0x200 | Logger Task |
| 0x300 | Diagnostics Task |

This demonstrates how external communication events can interact with an RTOS scheduler.

---

## Build

### ARM Firmware

Requirements

- arm-none-eabi-gcc
- QEMU
- GNU Make

Build

```bash
make
```

Run

```bash
qemu-system-arm \
-M mps2-an385 \
-cpu cortex-m3 \
-kernel build/firmware.elf \
-nographic
```

---

### Host Demonstration

Compile

```bash
gcc \
-Iinclude \
host/demo.c \
kernel/task.c \
kernel/scheduler.c \
kernel/semaphore.c \
drivers/uart.c \
drivers/can.c \
-o demo
```

Run

```bash
./demo
```

---

## Virtual CAN Setup

Load the virtual CAN driver

```bash
sudo modprobe vcan
```

Create the interface

```bash
sudo ip link add dev vcan0 type vcan
```

Bring it up

```bash
sudo ip link set up vcan0
```

Send a CAN frame

```bash
cansend vcan0 100#11223344
```

Example output

```
CAN Frame Received

ID : 0x100

Telemetry Task Activated

Scheduler Selected : Telemetry
```

---

## Technologies Used

- C
- ARM Cortex-M3
- Embedded Systems
- RTOS
- SocketCAN
- Linux
- QEMU
- GNU Make
- GDB

---

## Learning Outcomes

This project was developed to gain practical understanding of:

- RTOS kernel architecture
- Task scheduling algorithms
- Embedded firmware development
- Synchronization primitives
- ARM Cortex-M software development
- SocketCAN-based embedded communication
- Cross-compilation and QEMU emulation

---

## Author

**Tanish Niraj Palsapure**

24b3946

Department of Electrical Engineering

Indian Institute of Technology Bombay