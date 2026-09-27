#ifndef ARRAY_H

#define ARRAY_H

#define START_CAPACITY 5
#define START_SIZE 0


typedef struct{

	int capacity;
	int size;
	int *data;


} Array;


int array_init(Array *arr);

void array_add(Array *arr, int x);

int array_get(Array *arr, int x, int *val);

void array_remove(Array *arr, int x);

void array_free(Array *arr);

void array_print(Array *arr);

#endif
