#include "task.h"

TCB taskList[MAX_TASKS];

uint32_t taskCount = 0;

void task_create(void (*task)(void), uint8_t priority)
{
    if(taskCount >= MAX_TASKS)
        return;

    TCB *tcb = &taskList[taskCount];

    uint32_t *sp = &tcb->stack[STACK_SIZE];

    /* Hardware stack frame */

    *(--sp) = 0x01000000;      // xPSR
    *(--sp) = (uint32_t)task;  // PC
    *(--sp) = 0xFFFFFFFD;      // LR (Return to Thread mode using PSP)

    *(--sp) = 0;   // R12
    *(--sp) = 0;   // R3
    *(--sp) = 0;   // R2
    *(--sp) = 0;   // R1
    *(--sp) = 0;   // R0

    /* Software stack frame */

    *(--sp) = 0;   // R11
    *(--sp) = 0;   // R10
    *(--sp) = 0;   // R9
    *(--sp) = 0;   // R8
    *(--sp) = 0;   // R7
    *(--sp) = 0;   // R6
    *(--sp) = 0;   // R5
    *(--sp) = 0;   // R4

    tcb->sp = sp;

    tcb->entry = task;
    tcb->priority = priority;
    tcb->state = TASK_READY;

    taskCount++;
}