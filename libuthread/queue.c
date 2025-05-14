#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "private.h"
#include "sem.h"


struct queue_node;
typedef struct queue_node* node_t;

/* 
 * A linked list node that contains an pointer to data 
 * and a pointer to the next node.
 * 
 * If this is the last node, next points to NULL.
 */
struct queue_node {
	void *node_data;
	node_t next;
};

/* 
 * If we need O(1) operations, the best data structure for this
 * would probably be a linked list, since we don't need access
 * to the middle elements of the list.
 */
struct queue {
	node_t first;
	node_t last;
	int length;
};

queue_t queue_create(void)
{
    queue_t queue_ptr = malloc(sizeof *queue_ptr);

	if (!queue_ptr)
    {
        return NULL;
    }
	queue_ptr->first = NULL;
	queue_ptr->last = NULL;
	queue_ptr->length = 0;
	return queue_ptr;
}

int queue_destroy(queue_t queue)
{
	if (!queue || queue->length > 0)
		return -1;
	else {
		free(queue);
		return 0;
	}
}

int queue_enqueue(queue_t queue, void *data)
{
	if (!queue || data == NULL)
        return -1;

    struct queue_node *node = malloc(sizeof *node);
    if (!node) return -1;

    node->node_data = data;
    node->next = NULL;

    if (queue->last)
        queue->last->next = node;
    else
        queue->first = node;

    queue->last = node;
    queue->length++;
    return 0;
};

int queue_dequeue(queue_t queue, void **data)
{
	if(!queue || !data || queue->length == 0)
    {
        return -1;
    }

    struct queue_node *old = queue->first;
    *data = old->node_data;

    queue->first = old->next;
    free(old);
    queue->length--;

    if(queue->length == 0)
    {
        queue->last = NULL;
    }

    return 0; 
}

int queue_delete(queue_t queue, void *data)
{
	if (!queue || data == NULL)
        return -1;

    struct queue_node *prev = NULL, *cur = queue->first;
    while (cur) {
        if (cur->node_data == data) {
            if (prev)
                prev->next = cur->next;
            else
                queue->first = cur->next;

            if (cur->next == NULL)
                queue->last = prev;

            free(cur);
            queue->length--;
            return 0;
        }
        prev = cur;
        cur  = cur->next;
    }
    return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
	if (!queue || !func)
        return -1;
    struct queue_node *cur = queue->first;
    while (cur) {
        func(queue, cur->node_data);
        cur = cur->next;
    }
    return 0;
}

int queue_length(queue_t queue)
{
	return queue ? queue->length : -1;
}
