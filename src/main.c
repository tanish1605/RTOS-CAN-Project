#include "task.h"
#include "scheduler.h"

volatile uint32_t telemetryCounter = 0;
volatile uint32_t loggerCounter = 0;

void telemetryTask(void)
{
    while(1)
    {
        telemetryCounter++;
    }
}

void loggerTask(void)
{
    while(1)
    {
        loggerCounter++;
    }
}

int main(void)
{
    task_create(telemetryTask,2);

    task_create(loggerTask,1);

    scheduler_start();

    while(1)
    {

    }
}