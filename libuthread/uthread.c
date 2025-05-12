#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "context.c"
#include "uthread.h"
#include "queue.h"

enum tcb_state {
	READY,
	RUNNING,
	BLOCKED,
	TERMINATED
};

/*
 * Define uthread_tcb as a struct with
 * - A stack pointer
 * - A state enum variable
 * - Execution context of the thread
 */
struct uthread_tcb {
	/* TODO Phase 2 */
	void *stack_ptr;
	enum tcb_state state;
	uthread_ctx_t context;
};

static queue_t thread_q;
static struct uthread_tcb *main_ctx;
static struct uthread_tcb *current_thread;

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/3 */
	return current_thread;
}

void uthread_yield(void)
{
	/* TODO Phase 2 */
	struct uthread_tcb *current = uthread_current();
	current->state = READY;
	uthread_ctx_switch(&current->context, &main_ctx->context);
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
	struct uthread_tcb *current = uthread_current();
	current->state = TERMINATED;
	uthread_ctx_switch(&current->context, &main_ctx->context);
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	struct uthread_tcb *thread = malloc(sizeof(struct uthread_tcb)); 

	if (!thread) {
		return -1;
	}

	thread->stack_ptr = uthread_ctx_alloc_stack();
	thread->state = READY;

	uthread_ctx_init(&thread->context, thread->stack_ptr, func, arg);

	queue_enqueue(thread_q, thread);
	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	if (preempt) {
		
	}

	thread_q = queue_create();

	main_ctx = malloc(sizeof(struct uthread_tcb));
	main_ctx->stack_ptr = uthread_ctx_alloc_stack();

	struct uthread_tcb *init_thread = malloc(sizeof(struct uthread_tcb)); 
	init_thread->stack_ptr = uthread_ctx_alloc_stack();
	uthread_ctx_init(&init_thread->context, init_thread->stack_ptr, func, arg);

	queue_enqueue(thread_q, init_thread);

	while(queue_destroy(thread_q) != 0) {
		queue_dequeue(thread_q, (void**)&current_thread);
		if (current_thread->state == READY) {
			current_thread->state = RUNNING;
			main_ctx->state = READY;
			uthread_ctx_switch(&main_ctx->context, &current_thread->context);
			main_ctx->state = RUNNING;
			if (current_thread->state == READY || current_thread->state == BLOCKED) 
				queue_enqueue(thread_q, current_thread);
			else {
				uthread_ctx_destroy_stack((current_thread)->stack_ptr);
				free(current_thread);
			}
		}
		else if ((current_thread)->state == TERMINATED) {
			uthread_ctx_destroy_stack((current_thread)->stack_ptr);
			free(current_thread);
		}
		else if ((current_thread)->state == BLOCKED)
			queue_enqueue(thread_q, current_thread);
	}

	return 0;
}

void uthread_block(void)
{
	/* TODO Phase 3 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 3 */
	(void)uthread;
}

