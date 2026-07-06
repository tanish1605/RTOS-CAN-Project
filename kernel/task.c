#include "task.h"

TCB taskList[MAX_TASKS];

uint32_t taskCount = 0;

void task_create(void (*task)(void), uint8_t priority)
{
    if(taskCount >= MAX_TASKS)
        return;

    TCB *tcb = &taskList[taskCount];

    tcb->entry = task;

    tcb->priority = priority;

    tcb->state = TASK_READY;

    tcb->sp = &tcb->stack[STACK_SIZE-1];

    taskCount++;
}