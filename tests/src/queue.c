#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

DECL_QUEUE(long long, ll)

int main()
{
	printf("QUEUE TESTS\n");
	struct _RawQueue rq;
	printf("Start capacity: 3\n");
	rq = _RawQueue_new(sizeof(int), 3);
	printf("Queuing 0-4\n");
	for(int i = 0; i < 5; i++)
	{
		_RawQueue_queue(&rq, &i);
	}

	printf("Dequeuing and printing 5 times\n");
	for(int i = 0; i < 5; i++)
	{
		int num = *(int*)_RawQueue_next(&rq);
		printf("%d\n", num);
	}
	printf("\n");

	printf("Queuing 0-11\n");
	for(int i = 0; i < 12; i++)
	{
		_RawQueue_queue(&rq, &i);
	}

	printf("Dequeuing and printing 12 times\n");
	for(int i = 0; i < 12; i++)
	{
		int num = *(int*)_RawQueue_next(&rq);
		printf("%d\n", num);
	}
	printf("\n");
	_RawQueue_free(&rq);

	printf("\nStart capacity: 1\n");
	rq = _RawQueue_new(sizeof(int), 1);
	printf("Queuing 0 5 times\n");
	for(int i = 0; i < 5; i++)
	{
		int zero = 0;
		_RawQueue_queue(&rq, &zero);
	}
	printf("Queueing 1\n");
	int one = 1;
	_RawQueue_queue(&rq, &one);
	printf("Dequeuing and printing 6 times\n");
	for(int i = 0; i < 6; i++)
	{
		int num = *(int*)_RawQueue_next(&rq);
		printf("%d\n", num);
	}
	printf("\n");

	printf("\nStart capacity: 5, using macro\n");
	llQueue llq = llQueue_new(5);
	printf("Queuing long longs 0-9\n");
	for(long long i = 0; i < 10; i++)
	{
		llQueue_queue(&llq, i);
	}
	printf("Dequeuing and printing 12 times\n");
	for(int i = 0; i < 12; i++)
	{
		long long ret;
		switch(llQueue_next(&llq, &ret))
		{
			case QUEUE_ERR:
				printf("Got QUEUE_ERR when dequeuing\n");
				break;
			case QUEUE_OK:
				printf("%lld\n", ret);
				break;
		}
	}
	llQueue_free(&llq);

	return 0;
}
