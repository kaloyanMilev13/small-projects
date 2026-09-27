#include <stdio.h>
#include "array.h"


int main(void)
{
    Array arr;

    printf("========================================\n");
    printf("        Dynamic Array - Test\n");
    printf("========================================\n\n");


    /* Initialization */
    printf("[1] Initialization\n");
    if (!array_init(&arr)) {
        printf("    ERROR: Failed to initialize array.\n");
        return 1;
    }

    printf("    Initial size:     %d\n", arr.size);
    printf("    Initial capacity: %d\n\n", arr.capacity);


    /* Adding elements */
    printf("[2] Adding elements\n");

    for (int i = 1; i <= 16; i++) {
        array_add(&arr, i * 10);
    }

    printf("    Added 16 elements:\n    ");
    array_print(&arr);

    printf("    Size:     %d\n", arr.size);
    printf("    Capacity: %d\n\n", arr.capacity);


    /* Getting elements */
    printf("[3] Getting elements\n");

    int value;

    if (array_get(&arr, 0, &value)) {
        printf("    Index 0  -> %d\n", value);
    }

    if (array_get(&arr, 5, &value)) {
        printf("    Index 5  -> %d\n", value);
    }

    if (array_get(&arr, 15, &value)) {
        printf("    Index 15 -> %d\n", value);
    }

    printf("\n");


    /* Invalid indexes */
    printf("[4] Testing invalid indexes\n");

    if (!array_get(&arr, -1, &value)) {
        printf("    Index -1 -> correctly rejected\n");
    }

    if (!array_get(&arr, arr.size, &value)) {
        printf("    Index %d -> correctly rejected\n", arr.size);
    }

    printf("\n");


    /* Removing elements */
    printf("[5] Removing elements\n");

    printf("    Before removal:\n    ");
    array_print(&arr);

    array_remove(&arr, 0);
    array_remove(&arr, 5);
    array_remove(&arr, arr.size - 1);

    printf("    After removing indexes 0, 5 and last:\n    ");
    array_print(&arr);

    printf("    Size:     %d\n", arr.size);
    printf("    Capacity: %d\n\n", arr.capacity);


    /* Invalid removals */
    printf("[6] Testing invalid removals\n");

    array_remove(&arr, -1);
    array_remove(&arr, arr.size);

    printf("    Array remains valid:\n    ");
    array_print(&arr);

    printf("\n");


    /* Cleanup */
    printf("[7] Freeing array\n");

    array_free(&arr);

    printf("    Size:     %d\n", arr.size);
    printf("    Capacity: %d\n", arr.capacity);
    printf("    Data:     %s\n", arr.data == NULL ? "NULL" : "NOT NULL");

    printf("\n========================================\n");
    printf("        All tests completed\n");
    printf("========================================\n");

    return 0;
}







/*
#include <stdio.h>
#include "array.h"


int main (void){

	Array arr;

	if(!array_init(&arr)){

		printf("Error during init!");

	}else{
		array_add(&arr, 1);
		array_add(&arr, 2);
		array_add(&arr, 3);
		array_add(&arr, 4);
		array_add(&arr, 5);
		array_add(&arr, 6);

		array_print(&arr);

		int value;

		if(array_get(&arr, 100, &value)){

			printf("get: %dth element = %d\n", 3, value);
		}


		printf("\nremove: %dth element \n", 2);

		array_remove(&arr, 2);

		array_print(&arr);

		printf("capacity: %d\nsize: %d\n", arr.capacity, arr.size);

		array_free(&arr);

		return 0;

	}
}*/
