#include "scheduler.h"

TCB* scheduler_get_next_task(void)
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