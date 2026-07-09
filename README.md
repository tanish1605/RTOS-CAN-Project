# RTOS-CAN

## Overview
A lightweight educational RTOS kernel developed in C for ARM Cortex-M3.

## Features

- Task Control Blocks (TCB)
- Priority-based Scheduler
- Task State Management
- Counting Semaphores
- Modular Kernel Architecture
- Cross-compilation using arm-none-eabi-gcc
- QEMU compatible

## Project Structure

arch/
drivers/
include/
kernel/
src/

## Scheduler

Explain:
- READY
- RUNNING
- BLOCKED

Explain that the scheduler always selects the highest-priority READY task.

## Semaphore

Explain:
- semaphore_init()
- semaphore_take()
- semaphore_give()

## Build

make

## Run

qemu-system-arm ...

## Current Status

Implemented:
- Task management
- Scheduler
- Semaphores

Future Work:
- PendSV
- SysTick
- Context Switching
- Message Queues
- SocketCAN Integration