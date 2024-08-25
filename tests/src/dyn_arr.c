#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dyn_arr.h"

void print_array(int* data, size_t length) {
	for (size_t i = 0; i < length; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}
// Simple bubble-ish sort just to test the data structure
void sort_in_place(int* data, size_t length) {
	for (size_t max_index = length-1; max_index > 0; max_index--) {
		size_t index_largest_value = 0;
		int largest_value = data[0];
		for (size_t cur_index = 1; cur_index <= max_index; cur_index++) {
			int cur_value = data[cur_index];
			if (cur_value > largest_value) {
				index_largest_value = cur_index;
				largest_value = cur_value;
			}
		}
		data[index_largest_value] = data[max_index];
		data[max_index] = largest_value;
	}
}

int main() {
	srand(time(NULL));
	struct DynamicArray numbers = DynamicArray_new(sizeof(int), 5);
	for (int i = 0; i < 20; i++) {
		int number = rand() % 100;
		DynamicArray_push(&numbers, &number);
	}
	print_array(numbers.data, numbers.num_elements);
	sort_in_place(numbers.data, numbers.num_elements);
	print_array(numbers.data, numbers.num_elements);
	DynamicArray_remove(&numbers, 5);
	DynamicArray_remove(&numbers, 5);
	DynamicArray_remove(&numbers, 5);
	print_array(numbers.data, numbers.num_elements);

	DynamicArray_free(&numbers);
	return 0;
}
