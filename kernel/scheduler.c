#include "scheduler.h"
#include <stddef.h>

TCB *currentTask = 0;

TCB *scheduler_get_next_task(void)
{
    TCB *best = 0;

    for(uint32_t i = 0; i < taskCount; i++)
    {
        if(taskList[i].state != TASK_READY)
            continue;

        if(best == 0 || taskList[i].priority > best->priority)
            best = &taskList[i];
    }

    return best;
}

void scheduler_schedule(void)
{
    TCB *next = scheduler_get_next_task();

    if(next == NULL)
        return;

    if(currentTask &&
       currentTask->state == TASK_RUNNING)
        currentTask->state = TASK_READY;

    currentTask = next;

    currentTask->state = TASK_RUNNING;
}

void scheduler_start(void)
{
    scheduler_schedule();
}