# ECS 150: Project #2 - Part 2 - User-level thread library #

Assignment Page: [https://canvas.ucdavis.edu/courses/975590/assignments/1433327]

## Phase 1: queue API ##

- Queue Implementation, described in `./libuthread/queue.h`
    - [X] Implement queue data structure `queue_t`
    - [X] Implement function `queue_create()`
    - [X] Implement function `queue_destroy()`
    - [X] Implement function `queue_enqueue()`
    - [X] Implement function `queue_dequeue()`
    - [X] Implement function `queue_delete()`
    - [X] Implement function `queue_iterate()`
    - [X] Implement function `queue_length()`
    - [X] Test function `queue_create()`
    - [X] Test function `queue_destroy()`
    - [X] Test function `queue_enqueue()`
    - [X] Test function `queue_dequeue()`
    - [X] Test function `queue_delete()`
    - [X] Test function `queue_iterate()`
    - [X] Test function `queue_length()`
- [X] Complete Makefile
- [X] Create a tester program `./apps/queue_tester.c`

## Phase 2: uthread API ##

- (Non-preemptive) Public API, described in `./libuthread/uthread.h`
    - [X] Implement public function `uthread_run()`
    - [X] Implement public function `uthread_yield()`
    - [X] Implement public function `uthread_create()`
    - [X] Implement public function `uthread_exit()`
    - [X] Test public function `uthread_run()`
    - [X] Test public function `uthread_yield()`
    - [X] Test public function `uthread_create()`
    - [X] Test public function `uthread_exit()`
- Private data structure
    - [X] Implement TCB data structure `struct uthread_tcb`
    - [X] Implement private function `uthread_block()`
    - [X] Implement private function `uthread_unblock()`
    - [X] Test private function `uthread_block()`
    - [X] Test private function `uthread_unblock()`

## Phase 3: semaphore API ##

Semaphore Implementation, described in `./libuthread/sem.h`
- [X] Implement function `sem_create()`
- [X] Implement function `sem_destroy()`
- [X] Implement function `sem_down()`
- [X] Implement function `sem_up()`
- [X] Test function `sem_create()`
- [X] Test function `sem_destroy()`
- [X] Test function `sem_down()`
- [X] Test function `sem_up()`

## Phase 4: preemption ##

Preemption Implementation, described in `./libuthread/private.h`
- [X] Implement function `preempt_disable()`
- [X] Implement function `preempt_enable()`
- [X] Implement function `preempt_start()`
- [X] Implement function `preempt_stop()`
- [X] Test function `preempt_disable()`
- [X] Test function `preempt_enable()`
- [X] Test function `preempt_start()`
- [X] Test function `preempt_stop()`
- [X] Create a tester program `./apps/test_preempt.c`