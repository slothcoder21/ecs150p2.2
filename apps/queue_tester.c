#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}


void test_queue_advanced(void)
{
    int data[5] = {1, 3, 6, 2, 4}, *ptr = NULL;
    queue_t q;

    fprintf(stderr, "*** TEST queue_advanced ***\n");
    
    q = queue_create();
    for (int i = 0; i < 5; i++) {
        queue_enqueue(q, &data[i]);
        queue_dequeue(q, (void**)&ptr);
        TEST_ASSERT(*ptr == data[i]);
    }

    int err = queue_destroy(q);
    TEST_ASSERT(err == 0);
}


void test_queue_destroy(void)
{
	int data = 2, *ptr = NULL;
	queue_t q;

	fprintf(stderr, "*** TEST queue_destroy ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	TEST_ASSERT(queue_destroy(q) == -1);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(queue_destroy(q) == 0);
}

void test_queue_delete(void)
{
	int data = 3, data2 = 2;
	queue_t q;

	fprintf(stderr, "*** TEST queue_error_detection ***\n");
	q = queue_create();

	queue_enqueue(q, &data);
	queue_enqueue(q, &data2);

	queue_delete(q, &data2);
	TEST_ASSERT(queue_length(q) == 1);

	int err = queue_delete(q, &data2);
	TEST_ASSERT(err == -1);
}


void test_queue_error_detection(void)
{
	int data = 3, data2 = 2, *ptr = NULL;
	queue_t q;

	fprintf(stderr, "*** TEST queue_error_detection ***\n");
	q = queue_create();
	int err = queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(err == -1);
	err = queue_dequeue(q, NULL);
	TEST_ASSERT(err == -1);

	queue_enqueue(q, &data);
	queue_enqueue(q, &data2);
}


void example_queue_function(queue_t queue, void *data)
{
	fprintf(stderr, "%d\t", *(int*)data + queue_length(queue));
}


void test_queue_iterate(void)
{
	int data = 3, data2 = 2, data3 = 4;
	queue_t q;
	
	fprintf(stderr, "*** TEST queue_iterate ***\n");
	q = queue_create();
	queue_enqueue(q, &data);
	queue_enqueue(q, &data2);
	queue_enqueue(q, &data3);
	int err = queue_iterate(q, example_queue_function);
	fprintf(stderr, "\n");
	TEST_ASSERT(err == 0);
}

/* Callback function that increments items */
static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42)
        queue_delete(q, data);
    else
        *a += 1;
}

void test_iterate_delete(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;

	fprintf(stderr, "*** TEST iterate_delete ***\n");

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
		queue_enqueue(q, &data[i]);
	}

    /* Increment every item of the queue, delete item '42' */
    queue_iterate(q, iterator_inc);
    TEST_ASSERT(data[0] == 2);
    TEST_ASSERT(queue_length(q) == 9);
}


int main(void)
{
	test_create();
	test_queue_simple();
    test_queue_advanced();
	test_queue_destroy();
	test_queue_delete();
	test_queue_error_detection();
	test_queue_iterate();
	test_iterate_delete();

	return 0;
}
