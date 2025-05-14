/*
 * Thread creation and exiting test
 *
 * Tests the creation of multiples threads and the fact that a parent thread
 * should get returned to before its child is executed. The way the printing,
 * thread creation and exiting is done, the program should output:
 *
 * thread3
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
	uthread_exit();
	printf("thread2\n");
}

void thread1(void *arg)
{
	(void)arg;

	uthread_create(thread2, NULL);
	uthread_exit();
	printf("thread1\n");
}

int main(void)
{
	uthread_run(false, thread1, NULL);
	return 0;
}
