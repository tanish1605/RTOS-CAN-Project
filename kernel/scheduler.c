#include "scheduler.h"

TCB *currentTask = 0;

TCB *scheduler_get_next_task(void)
{
    TCB *best = 0;

    for(uint32_t i=0;i<taskCount;i++)
    {
        if(taskList[i].state != TASK_READY)
            continue;

        if(best == 0 || taskList[i].priority > best->priority)
            best = &taskList[i];
    }

    return best;
}

void scheduler_start(void)
{
    TCB *next = scheduler_get_next_task();

    if(next == 0)
        return;

    next->state = TASK_RUNNING;

    next->entry();
}