# ECS 150: Project #2 - Part 2 - User-level thread library #

## Phase 1: queue API ##

- Queue Implementation, described in `./libuthread/queue.h`
    - [ ] Implement queue data structure `queue_t`
    - [ ] Implement public function `queue_create()`
    - [ ] Implement public function `queue_destroy()`
    - [ ] Implement public function `queue_enqueue()`
    - [ ] Implement public function `queue_dequeue()`
    - [ ] Implement public function `queue_iterate()`
    - [ ] Implement public function `queue_length()`
- [ ] Complete Makefile
- [ ] Create a tester program `./apps/queue_tester.c`

## Phase 2: uthread API ##

- (Non-preemptive) Public API, described in `./libuthread/uthread.h`
    - [ ] Implement public function `uthread_run()`
    - [ ] Implement public function `uthread_yield()`
    - [ ] Implement public function `uthread_create()`
    - [ ] Implement public function `uthread_exit()`
- Private data structure
    - [ ] Implement TCB data structure `struct uthread_tct`
    - [ ] Implement private function `uthread_block()`
    - [ ] Implement private function `uthread_unblock()`

## Phase 3: semaphore API ##

Semaphore Implementation, described in `./libuthread/sem.h`
- [ ] Implement function `sem_create()`
- [ ] Implement function `sem_destroy()`
- [ ] Implement function `sem_down()`
- [ ] Implement function `sem_up()`

## Phase 4: preemption ##

Preemption Implementation, described in `./libuthread/private.h`
- [ ] Implement function `preempt_disable()`
- [ ] Implement function `preempt_enable()`
- [ ] Implement function `preempt_start()`
- [ ] Implement function `preempt_stop()`
- [ ] Create a tester program `./apps/test_preempt.c`