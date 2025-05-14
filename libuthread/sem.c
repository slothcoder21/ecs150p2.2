#include <stddef.h>
#include <stdlib.h>

#include "sem.h"
#include "queue.h"
#include "private.h"    // for preempt_disable/enable, uthread_block, uthread_unblock, uthread_self()

struct semaphore {
    int        count;    /* semaphore count, can go negative when threads wait */
    queue_t    waiting;  /* queue of blocked threads */
};

sem_t sem_create(size_t count)
{
    struct semaphore *sem = malloc(sizeof(*sem));
    if (!sem) return NULL;

    sem->count   = (int)count;
    sem->waiting = queue_create();
    if (!sem->waiting) {
        free(sem);
        return NULL;
    }

    return sem;
}

int sem_destroy(sem_t sem)
{
    if (!sem) return -1;
    /* cannot destroy if threads are still waiting */
    if (queue_length(sem->waiting) != 0)
        return -1;

    queue_destroy(sem->waiting);
    free(sem);
    return 0;
}

int sem_down(sem_t sem)
{
    if (!sem) return -1;

    preempt_disable();
    sem->count--;
    if (sem->count < 0) {
        /* queue this thread, then re-enable and block */
        queue_enqueue(sem->waiting, uthread_self());
        preempt_enable();
        uthread_block();
    } else {
        preempt_enable();
    }

    return 0;
}

int sem_up(sem_t sem)
{
    if (!sem) return -1;

    preempt_disable();
    sem->count++;
    if (sem->count <= 0) {
        /* wake exactly one waiter */
        struct uthread_tcb *next;
        queue_dequeue(sem->waiting, (void**)&next);
        uthread_unblock(next);
    }
    preempt_enable();

    return 0;
}
