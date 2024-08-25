#include <stdlib.h>
#include <string.h>

#include "dyn_arr.h"

struct DynamicArray DynamicArray_new(size_t item_size, unsigned int capacity) {
	struct DynamicArray array;
	array.capacity = capacity;
	array.item_size = item_size;
	array.num_elements = 0;
	array.data = malloc(item_size * capacity);
	return array;
}
void DynamicArray_push(struct DynamicArray* array, void* item) {
	if (array->capacity == array->num_elements) {
		array->data = realloc(array->data, array->capacity*array->item_size*2);
		array->capacity = array->capacity * 2;
	}

	size_t offset = array->item_size * array->num_elements;
	memcpy(array->data + offset, item, array->item_size);
	array->num_elements++;
}
void DynamicArray_remove(struct DynamicArray* array, size_t index) {
	array->num_elements--;
	if (array->num_elements == index) { return; }
	size_t offset_dest = array->item_size * index;
	size_t offset_src = array->item_size * (index + 1);
	memmove(
		array->data + offset_dest,
		array->data + offset_src,
		array->item_size * (array->num_elements - index)
	);
}
void DynamicArray_free(struct DynamicArray* array) {
	free(array->data);
}
