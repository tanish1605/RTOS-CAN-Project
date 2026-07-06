#include "task.h"
#include "scheduler.h"

void telemetryTask(void)
{
    while(1)
    {

    }
}

void loggerTask(void)
{
    while(1)
    {

    }
}

int main(void)
{
    task_create(telemetryTask,2);

    task_create(loggerTask,1);

    TCB *next = scheduler_get_next_task();

    (void)next;

    while(1)
    {

    }
}