#include <stddef.h>
#include <stdlib.h>

#include "sem.h"
#include "queue.h"
#include "private.h"

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
    /* decrement count; if negative, block current thread */
    if (--sem->count < 0) {
        /* enqueue the current thread's TCB and block */
        queue_enqueue(sem->waiting, uthread_current());
        uthread_block();
    }
    return 0;
}

int sem_up(sem_t sem)
{
    if (!sem) return -1;
    /* increment count; if there are waiters, wake one */
    if (++sem->count <= 0) {
        struct uthread_tcb *next;
        /* dequeue a waiting thread's TCB */
        queue_dequeue(sem->waiting, (void**)&next);
        uthread_unblock(next);
    }
    return 0;
}
