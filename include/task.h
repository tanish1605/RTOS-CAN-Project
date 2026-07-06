#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 8
#define STACK_SIZE 256

typedef enum
{
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED
} TaskState;

typedef struct
{
    uint32_t *sp;
    uint32_t stack[STACK_SIZE];

    void (*entry)(void);

    uint8_t priority;

    TaskState state;

} TCB;

extern TCB taskList[MAX_TASKS];
extern uint32_t taskCount;

void task_create(void (*task)(void), uint8_t priority);

#endif