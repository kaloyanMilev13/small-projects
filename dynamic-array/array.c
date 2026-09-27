#include "array.h"
#include <stdlib.h>
#include <stdio.h>

int array_init(Array *arr){

	int *temp = malloc(sizeof(int) * START_CAPACITY);

	if(temp != NULL){

		arr->data = temp;
		arr->capacity = START_CAPACITY;
		arr->size = START_SIZE;
		return 1;

	}

	//else
	free(temp);
	arr->data = NULL;
	return 0;
	


}


void array_add(Array *arr, int x){

	if(arr->size < arr->capacity){ //should it be size + 1?

		arr->size++;
		(arr->data)[arr->size - 1] = x;

	}else if(arr->size == arr->capacity){

		int *temp = realloc(arr->data, sizeof(int) * (arr->capacity + 10));

		if(temp == NULL){
			printf("no memory");
			return;
		}else{

			arr->capacity += 10;
			arr->size++;
			arr->data = temp;
			(arr->data)[arr->size - 1] = x;

		}
	}
}


int array_get(Array *arr, int x, int *val){


	if(x >= 0 && x < arr->size){

		*val = (arr->data)[x];
		return 1;
	}else{
		printf("Error getting index of element");
		return 0;
	}

}

void array_remove(Array *arr, int x){

	if(x >= 0 && x < arr->size){

		for(int i = x + 1; i < arr->size; i++){

			(arr->data)[i - 1] = (arr->data)[i];

		}

		//(arr->data)[arr->size - 1] = 0;
		arr->size--;

	}

}

void array_free(Array *arr){

	arr->capacity = 0;
	arr->size = 0;

	free(arr->data);
	arr->data = NULL;

}


void array_print(Array *arr){

	for(int i = 0; i < arr->size; i++){

		printf("%d, ", (arr->data)[i]);

	}

	printf("\n");



}

