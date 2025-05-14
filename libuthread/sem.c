#include <stddef.h>
#include <stdlib.h>

#include "sem.h"
#include "queue.h"
#include "private.h"    // for preempt_disable/enable, uthread_current, uthread_block, uthread_unblock

/* Semaphore structure for thread synchronization */
struct semaphore {
    int     count;    /* semaphore count, can go negative when threads wait */
    queue_t waiting;  /* queue of blocked threads */
};

/* Create a new semaphore with initial count */
sem_t sem_create(size_t count)
{
    struct semaphore *sem = malloc(sizeof *sem);
    if (!sem) return NULL;

    sem->count   = (int)count;
    sem->waiting = queue_create();
    if (!sem->waiting) {
        free(sem);
        return NULL;
    }

    return sem;
}

/* Destroy a semaphore - fails if threads are still waiting */
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

/* Decrement semaphore - block if count becomes negative */
int sem_down(sem_t sem)
{
    if (!sem) return -1;

    preempt_disable();
    sem->count--;
    if (sem->count < 0) {
        /* enqueue current thread, re-enable preemption, then block */
        queue_enqueue(sem->waiting, uthread_current());
        preempt_enable();
        uthread_block();
    } else {
        preempt_enable();
    }
    return 0;
}

/* Increment semaphore - wake one waiting thread if any */
int sem_up(sem_t sem)
{
    if (!sem) return -1;

    preempt_disable();
    sem->count++;
    if (sem->count <= 0) {
        /* wake exactly one waiter */
        void *tcb;
        queue_dequeue(sem->waiting, &tcb);
        uthread_unblock((struct uthread_tcb*)tcb);
    }
    preempt_enable();

    return 0;
}
