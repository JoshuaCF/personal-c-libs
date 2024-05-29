#pragma once


#include <stdbool.h>

struct _RawQueue {
	unsigned int front;
	unsigned int back;
	unsigned int capacity;
	unsigned int item_size;
	void* data;
	bool full;
};

struct _RawQueue _RawQueue_new(unsigned int item_size, unsigned int capacity);
void* _RawQueue_next(struct _RawQueue* raw_queue);
void _RawQueue_queue(struct _RawQueue* raw_queue, void* item);
void _RawQueue_realloc(struct _RawQueue* raw_queue);
void _RawQueue_free(struct _RawQueue* raw_queue);
