#include <stdio.h>
#include <stdlib.h>



typedef struct{
       
int capacity;
int size;
int *data;


} Array;


void array_init(Array *arr){

	arr->capacity = 5;
	arr->size = 0;

	int *temp = malloc(sizeof(int) * arr->capacity);

	if(temp != NULL){

		arr->data = temp;

	}else{
		free(temp);
	}


}


void array_add(Array *arr, int x){
	
	if(arr->size == arr->capacity){

		arr->capacity += 10;

		int *temp = realloc(arr->data, sizeof(int) * arr->capacity);

		if(temp == NULL){
			printf("no mem");
		}else{
			arr->data = temp;
		}

	}

	arr->size++;

	(arr->data)[arr->size - 1] = x;

	

}

int array_get(Array *arr, int x){


	if(x < arr->size)
		return (arr->data)[x];

	return 1;
}

int main (void){

	Array arr;


	array_init(&arr);	

	array_add(&arr, 1);
	array_add(&arr, 2);
	
	printf("get: %d\n",  array_get(&arr, 0));

	


	for(int i = 0; i < arr.size; i++){

		printf("%d, ", arr.data[i]);
		
	}

	printf("\n");
	
	printf("capacity: %d\nsize: %d\n", arr.capacity, arr.size);


	free(arr.data);


	return 0;
}
