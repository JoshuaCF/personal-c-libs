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

enum QueueNextSuccess { QUEUE_OK, QUEUE_ERR };

#define DECL_QUEUE(type, typename) \
	typedef struct _RawQueue typename##Queue; \
	typename##Queue typename##Queue_new(unsigned int capacity) \
	{ \
		return _RawQueue_new(sizeof(type), capacity); \
	} \
	enum QueueNextSuccess typename##Queue_next(typename##Queue* queue, type * out) \
	{ \
		type * retPtr = (type *) _RawQueue_next(queue); \
		if(retPtr == 0) return QUEUE_ERR; \
		*out = *retPtr; \
		return QUEUE_OK; \
	} \
	void typename##Queue_queue(typename##Queue* queue, type item) \
	{ \
		_RawQueue_queue(queue, &item); \
	} \
	void typename##Queue_free(typename##Queue* queue) \
	{ \
		_RawQueue_free(queue); \
	}
