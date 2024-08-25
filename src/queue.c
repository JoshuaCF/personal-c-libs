#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct Queue Queue_new(size_t item_size, unsigned int capacity) {
	struct Queue queue;

	queue.front = 0;
	queue.back = 0;
	queue.capacity = capacity;
	queue.item_size = item_size;
	queue.data = malloc(item_size * capacity);
	queue.full = false;

	return queue;
}
enum QueueNextSuccess Queue_next(struct Queue* queue, void* out) {
	if (queue->front == queue->back && !queue->full) return QUEUE_EMPTY;

	void* next_item = queue->data + queue->front * queue->item_size;
	queue->front = (queue->front + 1) % queue->capacity;
	queue->full = false;

	memcpy(out, next_item, queue->item_size);
	return QUEUE_OK;
}
void Queue_realloc(struct Queue* queue) {
	unsigned int new_capacity = queue->capacity * 2;
	void* new_data = malloc(new_capacity * queue->item_size);

	// Moving the remaining part to the end and the beginning part to the start would leave a large gap
	// in the middle, which is probably fine, but we can take the time to put the entire thing in 
	// contiguously. Performance of moving should be the same, could *possibly* help with caching.
	// Additionally, reallocations should only happen when full, so the entire queue's range will always be copied.
	// Regardless, reassignment of front and back will account for true size, allowing early reallocs.
	unsigned int remaining = queue->capacity - queue->front;
	memcpy(new_data, queue->data + queue->front * queue->item_size, remaining * queue->item_size);
	memcpy(new_data + remaining * queue->item_size, 
		queue->data, (queue->capacity - remaining) * queue->item_size);
	unsigned int item_count = queue->back - queue->front;
	if (queue->back < queue->front) item_count += queue->capacity;
	if (item_count == 0 && queue->full) item_count = queue->capacity;
	queue->front = 0;
	queue->back = item_count;

	free(queue->data);

	queue->data = new_data;
	queue->capacity = new_capacity;
	queue->full = false;
}
void Queue_queue(struct Queue* queue, void* item) {
	if (queue->full) Queue_realloc(queue);

	void* addr = queue->data + queue->back * queue->item_size;
	memcpy(addr, item, queue->item_size);
	queue->back = (queue->back + 1) % queue->capacity;
	queue->full = queue->back == queue->front;
}
void Queue_free(struct Queue* queue) {
	free(queue->data);
}
