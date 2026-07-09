#include "semaphore.h"
#include <stddef.h>

void semaphore_init(Semaphore *sem, int32_t initial_count)
{
    sem->count = initial_count;
}

void semaphore_take(Semaphore *sem)
{
    if (sem->count > 0)
    {
        sem->count--;
    }
}

void semaphore_give(Semaphore *sem)
{
    sem->count++;
}