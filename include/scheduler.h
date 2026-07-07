#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

extern TCB *currentTask;

TCB *scheduler_get_next_task(void);

void scheduler_schedule(void);

void scheduler_start(void);

#endif