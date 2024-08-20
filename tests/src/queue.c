#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main()
{
	printf("QUEUE TESTS\n");
	struct Queue rq;
	printf("Start capacity: 3\n");
	rq = Queue_new(sizeof(int), 3);
	printf("Queuing 0-4\n");
	for(int i = 0; i < 5; i++)
	{
		Queue_queue(&rq, &i);
	}

	printf("Dequeuing and printing 5 times\n");
	for(int i = 0; i < 5; i++)
	{
		int num;
		Queue_next(&rq, &num);
		printf("%d\n", num);
	}
	printf("\n");

	printf("Queuing 0-11\n");
	for(int i = 0; i < 12; i++)
	{
		Queue_queue(&rq, &i);
	}

	printf("Dequeuing and printing 12 times\n");
	for(int i = 0; i < 12; i++)
	{
		int num;
		Queue_next(&rq, &num);
		printf("%d\n", num);
	}
	printf("\n");
	Queue_free(&rq);

	printf("\nStart capacity: 1\n");
	rq = Queue_new(sizeof(int), 1);
	printf("Queuing 0 5 times\n");
	for(int i = 0; i < 5; i++)
	{
		int zero = 0;
		Queue_queue(&rq, &zero);
	}
	printf("Queuing 1\n");
	int one = 1;
	Queue_queue(&rq, &one);
	printf("Dequeuing and printing 6 times\n");
	for(int i = 0; i < 6; i++)
	{
		int num;
		Queue_next(&rq, &num);
		printf("%d\n", num);
	}
	printf("\n");

	printf("Testing failure states\n");
	for (int i = 0; i < 5; i++) {
		if (Queue_next(&rq, NULL) != QUEUE_EMPTY) {
			printf("Failed to return QUEUE_EMPTY\n");
		}
	}
	printf("\n");

	return 0;
}
