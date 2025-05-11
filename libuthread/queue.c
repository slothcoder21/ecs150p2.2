#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct queue {
	/* TODO Phase 1 */

	/* 
	 * If we need O(1) operations, the best data structure for this
	 * would probably be a linked list, since we don't need access
	 * to the middle elements of the list.
	 */

	node_t *first;
	node_t *last
	int length;
};

typedef struct queue_node {
	void *data;
	node_t *next;
} node_t;

queue_t queue_create(void)
{
	/* TODO Phase 1 */
	node_t *node_ptr = malloc(sizeof(node_t));
	queue_t *queue_ptr = malloc(sizeof(queue_t));
	queue_ptr->first = node_ptr;
	queue_ptr->last = node_ptr;
	queue_ptr->length = 1;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
}

