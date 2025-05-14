/*
 * Preemptive Yielding Test
 *
 * This program tests preemptive yielding with an infinite loop
 * in thread1. With preemption, it should be possible to yield
 * the loop to print:
 * 
 * thread2
 * thread3
 *
 * thread1 should never print.
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <uthread.h>

void thread3(void *arg)
{
	(void)arg;

	uthread_yield();
	printf("thread3\n");
}

void thread2(void *arg)
{
	(void)arg;

	uthread_create(thread3, NULL);
	uthread_yield();
	printf("thread2\n");
}

void thread1(void *arg)
{
	(void)arg;

	uthread_create(thread2, NULL);
	
	while(1);

	uthread_yield();
	printf("thread1\n");
	uthread_yield();
}

int main(void)
{
	uthread_run(false, thread1, NULL);
	return 0;
}
