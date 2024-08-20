#pragma once


#include <stdbool.h>

struct Queue {
	unsigned int front;
	unsigned int back;
	unsigned int capacity;
	unsigned int item_size;
	void* data;
	bool full;
};

enum QueueNextSuccess { QUEUE_OK, QUEUE_EMPTY };

struct Queue Queue_new(unsigned int item_size, unsigned int capacity);
enum QueueNextSuccess Queue_next(struct Queue* queue, void* out);
void Queue_queue(struct Queue* queue, void* item);
void Queue_realloc(struct Queue* queue);
void Queue_free(struct Queue* queue);
