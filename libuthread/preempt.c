#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100
#define MICROSEC_PERIOD 1000000.0 / HZ

void preempt_timer_handler(int);

static bool preempt_active = false;
static struct itimerval preempt_timer = {
	.it_interval = {
		.tv_sec = 0.0,
		.tv_usec = MICROSEC_PERIOD
	},
	.it_value = {
		.tv_sec = 0.0,
		.tv_usec = MICROSEC_PERIOD
	}
};

static struct sigaction sigstorage;
static struct sigaction sa = {
			.sa_handler = preempt_timer_handler,
			.sa_flags = 0
};
static struct itimerval timer_storage;
static sigset_t sig_block_set;

void preempt_timer_handler(int signum)
{
	(void)signum;
	uthread_yield();
}

void preempt_disable(void)
{
	if (preempt_active) {
		sigprocmask(SIG_BLOCK, &sig_block_set, NULL);
	}
}

void preempt_enable(void)
{
	if (preempt_active) {
		sigprocmask(SIG_UNBLOCK, &sig_block_set, NULL);
	}
}

void preempt_start(bool preempt)
{
	if ((preempt_active = preempt)) {
		sigemptyset(&sig_block_set);
		sigaddset(&sig_block_set, SIGVTALRM);
		sigprocmask(SIG_BLOCK, &sig_block_set, NULL);
		sa.sa_mask = sig_block_set;
		preempt_timer.it_interval.tv_usec = MICROSEC_PERIOD;
		preempt_timer.it_value.tv_usec = MICROSEC_PERIOD;
		setitimer(ITIMER_VIRTUAL, &preempt_timer, &timer_storage);
		sigaction(SIGVTALRM, &sa, &sigstorage);
	}
}

void preempt_stop(void)
{
	/* TODO Phase 4 */
	if (preempt_active) {
		setitimer(ITIMER_VIRTUAL, &timer_storage, NULL);
		sigaction(SIGVTALRM, &sigstorage, NULL);
		preempt_active = false;
	}
}
