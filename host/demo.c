#include <stdio.h>

#include "task.h"
#include "scheduler.h"
#include "semaphore.h"

#include "uart.h"
#include "can.h"

Semaphore sem;
struct can_frame frame;

#define TELEMETRY_TASK   0
#define LOGGER_TASK      1
#define DIAGNOSTICS_TASK 2

void telemetryTask(void)
{
}

void loggerTask(void)
{
}

void diagnosticsTask(void){
}

int main(void)
{
    uart_init();

    if (can_init("vcan0") != 0)
    {
        printf("Failed to initialize vCAN\n");
        return -1;
    }

    uart_write_string("SocketCAN Initialized (vcan0)\n");

    uart_write_string(" RTOS-CAN Kernel Demonstration\n");

    task_create(telemetryTask, 3);
    task_create(loggerTask, 2);
    task_create(diagnosticsTask, 1);

    taskList[TELEMETRY_TASK].state = TASK_READY;
    taskList[LOGGER_TASK].state = TASK_BLOCKED;
    taskList[DIAGNOSTICS_TASK].state = TASK_BLOCKED;

    printf("Tasks Created : %u\n", taskCount);

    scheduler_schedule();

    uart_write_string("\nScheduler Selected:\n");

    if(currentTask == &taskList[TELEMETRY_TASK])

        printf("Telemetry Task\n");

    else if(currentTask == &taskList[LOGGER_TASK])

        printf("Logger Task\n");

    else if(currentTask == &taskList[DIAGNOSTICS_TASK])

        printf("Diagnostics Task\n");

    printf("Priority : %d\n", currentTask->priority);

    currentTask->state = TASK_BLOCKED;

    uart_write_string("Task completed. Waiting for next CAN event...\n");   

    semaphore_init(&sem,1);

    printf("\nSemaphore Count = %d\n",sem.count);

    uart_write_string("Taking semaphore...\n");

    semaphore_take(&sem);

    printf("Semaphore Count = %d\n",sem.count);

    uart_write_string("\nWaiting for CAN frames...\n");

    while (1)
    {
        if (can_receive(&frame) > 0)
        {
            printf("\n==============================\n");
            printf("CAN Frame Received\n");

            printf("ID   : 0x%03X\n", frame.can_id);

            printf("Data : ");

            for (int i = 0; i < frame.can_dlc; i++)
                printf("%02X ", frame.data[i]);

            printf("\n");

        switch(frame.can_id)
        {
            case 0x100:

                uart_write_string("\nTelemetry Event\n");

                taskList[TELEMETRY_TASK].state = TASK_READY;

                break;

            case 0x200:

                uart_write_string("\nLogger Event\n");

                taskList[LOGGER_TASK].state = TASK_READY;

                break;

            case 0x300:

                uart_write_string("\nDiagnostics Event\n");

                taskList[DIAGNOSTICS_TASK].state = TASK_READY;

                break;

            default:

                printf("Unknown CAN ID\n");

                continue;
        }

            semaphore_give(&sem);

            printf("Semaphore Count = %d\n", sem.count);

            scheduler_schedule();

            printf("Scheduler Selected : ");

            if(currentTask == &taskList[TELEMETRY_TASK])

                printf("Telemetry Task\n");

            else if(currentTask == &taskList[LOGGER_TASK])

                printf("Logger Task\n");

            else if(currentTask == &taskList[DIAGNOSTICS_TASK])

                printf("Diagnostics Task\n");
        }
    }

    can_close();

    return 0;
}