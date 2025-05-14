#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "private.h"
#include "sem.h"

struct semaphore {
	/* TODO Phase 3 */

	size_t count;
	queue_t waiting;
};

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
	sem_t sem = malloc(sizeof(*sem));
	if(!sem)
	{
		return NULL;
	}

	sem->count = count;
	sem->waiting = queue_create();
	if(!sem->waiting)
	{
		free(sem);
		return NULL;
	}

	return sem;
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */

	if(!sem || !queue_size(sem->waiting))
	{
		return -1;
	}

	queue_destroy(sem->waiting);
	free(sem);
	return 0;
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */
	if(!sem)
	{
		return -1;
	}

	if(sem->count == 0)
	{
		sem->count--;
	}
	else
	{
		queue_enqueue(sem->waiting, uthread_current());
		uthread_block();
	}

	return 0;
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */

	if(!sem)
	{
		return -1;
	}

	if(!queue_empty(sem->waiting))
	{
		struct uthread_tcb *t = queue_dequeue(sem->waiting, NULL);
		uthread_block(); 
	}
	else
	{
		sem->count++;
	}

	return 0;
}

