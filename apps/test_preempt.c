/*
 * Preemptive yielding test
 *
 * Tests the ability of the library scheduler to preemptively
 * yield a thread. thread1 contains a loop of computations that
 * can only be done at runtime, to avoid compiler optimization.
 * On at least the CSIF system, this should be slow enough for
 * the scheduler to yield to thread2, which finishes before thread1.
 * 
 * The expected output is:
 *
 * thread2
 * thread1: N
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <uthread.h>

void thread2(void *arg)
{
	(void)arg;
	printf("thread2\n");
}

void thread1(void *arg)
{
	(void)arg;

	uthread_create(thread2, NULL);
    int test_val = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100000; j++) {
            test_val = rand();
        }
        test_val = test_val % 24;
    }
	printf("thread1: %d\n", test_val);
}

int main(void)
{
    srand(time(NULL));
	uthread_run(true, thread1, NULL);
	return 0;
}
