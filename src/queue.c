#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct _RawQueue _RawQueue_new(unsigned int item_size, unsigned int capacity)
{
	struct _RawQueue raw_queue;

	raw_queue.front = 0;
	raw_queue.back = 0;
	raw_queue.capacity = capacity;
	raw_queue.item_size = item_size;
	raw_queue.data = malloc(item_size * capacity);
	raw_queue.full = false;

	return raw_queue;
}
void* _RawQueue_next(struct _RawQueue* raw_queue)
{
	if(raw_queue->front == raw_queue->back && !raw_queue->full) return NULL;

	void* next_item = raw_queue->data + raw_queue->front * raw_queue->item_size;
	raw_queue->front = (raw_queue->front + 1) % raw_queue->capacity;
	raw_queue->full = false;

	return next_item;
}
void _RawQueue_queue(struct _RawQueue* raw_queue, void* item)
{
	if(raw_queue->full) _RawQueue_realloc(raw_queue);

	void* addr = raw_queue->data + raw_queue->back * raw_queue->item_size;
	memcpy(addr, item, raw_queue->item_size);
	raw_queue->back = (raw_queue->back + 1) % raw_queue->capacity;
	raw_queue->full = raw_queue->back == raw_queue->front;
}
void _RawQueue_realloc(struct _RawQueue* raw_queue)
{
	unsigned int new_capacity = raw_queue->capacity * 2;
	void* new_data = malloc(new_capacity * raw_queue->item_size);

	// Moving the remaining part to the end and the beginning part to the start would leave a large gap
	// in the middle, which is probably fine, but we can take the time to put the entire thing in 
	// contiguously. Performance of moving should be the same, could *possibly* help with caching.
	// Additionally, reallocations should only happen when full, so the entire queue's range will always be copied.
	// Reassignment of front and back will, however, account for true size, allowing early reallocs.
	unsigned int remaining = raw_queue->capacity - raw_queue->front;
	memcpy(new_data, raw_queue->data + raw_queue->front * raw_queue->item_size, remaining * raw_queue->item_size);
	memcpy(new_data + remaining * raw_queue->item_size, 
		raw_queue->data, (raw_queue->capacity - remaining) * raw_queue->item_size);
	unsigned int item_count = raw_queue->back - raw_queue->front;
	if(raw_queue->back < raw_queue->front) item_count += raw_queue->capacity;
	if(item_count == 0 && raw_queue->full) item_count = raw_queue->capacity;
	raw_queue->front = 0;
	raw_queue->back = item_count;

	free(raw_queue->data);

	raw_queue->data = new_data;
	raw_queue->capacity = new_capacity;
	raw_queue->full = false;
}
void _RawQueue_free(struct _RawQueue* raw_queue)
{
	free(raw_queue->data);
}
