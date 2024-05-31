#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

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

	return 0;
}
