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

	node_t first;
	node_t last;
	int length;
};


/* 
 * A linked list node that contains an pointer to data 
 * and a pointer to the next node.
 * 
 * If this is the last node, points to NULL.
 */
struct queue_node {
	void *node_data;
	node_t next;
};

typedef struct queue_node* node_t;

queue_t queue_create(void)
{
	/* TODO Phase 1 */
	queue_t queue_ptr = malloc(sizeof(queue_t));
	if (!queue_ptr) {
		return NULL;
	}
	queue_ptr->first = NULL;
	queue_ptr->last = NULL;
	queue_ptr->length = 0;
	return queue_ptr;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
	if (!queue || queue->length > 0) {
		return -1;
	} else {
		free(queue);
		return 0;
	}
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if (!queue || !data) {
		return -1;
	}

	node_t new_node = malloc(sizeof(node_t));
	if (!new_node) {
		return -1;
	}

	new_node->node_data = data;
	queue->last->next = new_node;
	queue->last = new_node;
	queue->length++;

	if (queue->length == 0) {
		queue->first = new_node;
	}

	return 0;
};

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
	if (!queue || !data || queue->length == 0) {
		return -1;
	}

	*data = queue->first->node_data;
	
	node_t next_first = queue->first->next;
	free(queue->first);
	queue->first = next_first;
	queue->length--;

	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if (!queue || !data) {
		return -1;
	}

	node_t node_i = queue->first;
	node_t temp_prev = NULL;
	node_t temp_next = NULL;
	
	int found = -1;

	while (node_i) {
		temp_next = node_i->next;
		if (node_i->node_data == data) {
			free(node_i);
			if (!temp_prev) {
				queue->first = temp_next;
			} else {
				temp_prev->next = temp_next;
			}
			if (!temp_next) {
				queue->last = temp_prev;
			}

			found = 0;
			break;
		}

		temp_prev = node_i;
		node_i = temp_next;
		if (node_i) {
			
		}
	}

	return found;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	return queue->length;
}

