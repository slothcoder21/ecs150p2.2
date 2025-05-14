/* uthread.c: User-level threads library implementation */

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ucontext.h>              

#include "private.h"              
#include "uthread.h"              
#include "queue.h"                
#include "context.c"

// Possible thread states
enum tcb_state { READY, RUNNING, BLOCKED, TERMINATED };

/* Thread control block which stores thread state and context */
struct uthread_tcb {
    void          *stack_ptr;  // pointer to allocated stack (NULL for main)
    uthread_ctx_t  context;    // saved execution context
    enum tcb_state state;      // current state
};

// Global scheduler state
static queue_t              thread_q    = NULL;  // queue of threads
static struct uthread_tcb  *current_thread = NULL;  // currently running thread
static struct uthread_tcb  *main_ctx        = NULL;  // main scheduler context

/* Return pointer to the running thread's TCB */
struct uthread_tcb *uthread_current(void) {
    return current_thread;
}

/* Yield execution: mark current thread READY and switch to scheduler */
void uthread_yield(void) {
    struct uthread_tcb *t = uthread_current();
    assert(t != NULL);
    t->state = READY;
    queue_enqueue(thread_q, t);
    uthread_ctx_switch(&t->context, &main_ctx->context);
}

/* Exit current thread: mark TERMINATED and switch to scheduler */
void uthread_exit(void) {
    struct uthread_tcb *t = uthread_current();
    assert(t != NULL);
    t->state = TERMINATED;
    uthread_ctx_switch(&t->context, &main_ctx->context);
}

/* Create a new thread running func(arg) */
int uthread_create(uthread_func_t func, void *arg) {
    preempt_disable();

    struct uthread_tcb *t = malloc(sizeof *t);
    if (!t) {
        preempt_enable();
        return -1;
    }

    t->stack_ptr = uthread_ctx_alloc_stack();
    if (!t->stack_ptr) {
        free(t);
        preempt_enable();
        return -1;
    }

    t->state = READY;
    uthread_ctx_init(&t->context, t->stack_ptr, func, arg);
    queue_enqueue(thread_q, t);

    preempt_enable();
    return 0;
}

/* Start threading system: create initial thread and run scheduler */
int uthread_run(bool preempt, uthread_func_t func, void *arg) {
    // Start periodic timer if preemption requested
    preempt_start(preempt);

    // Initialize thread queue
    thread_q = queue_create();
    if (!thread_q) {
        preempt_stop();
        return -1;
    }

    // Allocate TCB for main context (scheduler)
    main_ctx = malloc(sizeof *main_ctx);
    if (!main_ctx) {
        queue_destroy(thread_q);
        preempt_stop();
        return -1;
    }
    main_ctx->stack_ptr = NULL;
    main_ctx->state     = RUNNING;

    // Capture the current (main) context
    getcontext(&main_ctx->context);

    // Create the user thread
    if (uthread_create(func, arg) != 0) {
        free(main_ctx);
        queue_destroy(thread_q);
        preempt_stop();
        return -1;
    }

    /* Main scheduler loop: run until no threads remain */
    while (queue_length(thread_q) > 0) {
        struct uthread_tcb *t = NULL;

        preempt_disable();
        queue_dequeue(thread_q, (void**)&t);
        preempt_enable();

        if (!t)
            continue;

        if (t->state == READY) {
            current_thread = t;
            t->state       = RUNNING;

            // Switch from scheduler to thread
            uthread_ctx_switch(&main_ctx->context, &t->context);

            // Upon return, thread has yielded or exited
            current_thread = NULL;

            if (t->state == READY) {
                // Thread yielded: requeue
                preempt_disable();
                queue_enqueue(thread_q, t);
                preempt_enable();
            } else if (t->state == TERMINATED) {
                // Thread exited: clean up
                uthread_ctx_destroy_stack(t->stack_ptr);
                free(t);
            }
        }
    }

    // Clean up scheduler
    queue_destroy(thread_q);
    preempt_stop();
    free(main_ctx);
    return 0;
}

/* Block the current thread: switch to scheduler */
void uthread_block(void) {
    struct uthread_tcb *t = uthread_current();
    assert(t != NULL);
    t->state = BLOCKED;
    uthread_ctx_switch(&t->context, &main_ctx->context);
}

/* Unblock a thread: mark READY and enqueue it */
void uthread_unblock(struct uthread_tcb *t) {
    if (!t || t->state != BLOCKED)
        return;
    t->state = READY;
    preempt_disable();
    queue_enqueue(thread_q, t);
    preempt_enable();
}
