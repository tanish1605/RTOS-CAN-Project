#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdint.h>

typedef struct
{
    int32_t count;
} Semaphore;

void semaphore_init(Semaphore *sem, int32_t initial_count);
void semaphore_take(Semaphore *sem);
void semaphore_give(Semaphore *sem);

#endif