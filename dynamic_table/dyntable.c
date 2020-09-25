#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "dyntable_impl.h"

static float decrease_factor = 0.25;

typedef struct dynamicTable {
	int *arr;
	int capacity;
	int size;

} dynamicTable;


void* make_new_dynamic_table(int n) {
	if (n == 0)
		return NULL;
	dynamicTable* dt = malloc(sizeof(dynamicTable));
	if (dt == NULL) {
		//printf("unable to allocate memory on heap!\n");
		return NULL;
	}
	dt -> capacity = n;
	dt -> size = 0;
	dt -> arr = malloc(sizeof(int) * n);
	return dt;
}

void push_back(void** dt, int item) {



	dynamicTable*Dt = *dt;
	if (Dt == NULL) return;
	// printf("push item : %d\n", item);
	// printf("size %d\n", Dt->size);
	if (Dt-> size == Dt ->capacity) {
		//we need to increase by 1.5
		int newCapacity = (int)ceil((double)Dt -> capacity * 1.5);
		int* newArr = realloc(Dt->arr, (int)(sizeof(int) * newCapacity));
		if (newArr == NULL) {
			//printf("unable to allocate memory on heap!\n");
			return;
		}

		//following commented lines were used to test the copyCount in the tests file .
		//if (Dt->arr != newArr)
		//	copyCount+= oldSize;


		Dt = *dt;
		Dt-> arr = newArr;
		Dt-> capacity = newCapacity;

	}

	Dt -> arr[Dt->size] = item;
	Dt -> size = Dt -> size + 1;
}

void pop_back(void**dt) {




	dynamicTable*Dt = *dt;
	// printf("POP %d\n", Dt->size);
	if (Dt == NULL) return;

	if (Dt->size == 0)
		return;

	// printf( "Pop: %d\n" , Dt->arr[Dt->size - 1]);
	Dt -> size  = Dt -> size - 1;

	if (Dt -> size <= (Dt -> capacity * decrease_factor)) {
		int newCapacity  = ceil(1.5 * decrease_factor * Dt -> capacity);
		int* newArr = realloc(Dt->arr, (int)(sizeof(int) * newCapacity));
		if (newArr == NULL) {
			printf("unable to allocate memory on heap!\n");
			return;
		}

		//following commented lines were used to test the copyCount in the tests file .
		//if (Dt->arr != newArr)
		//	copyCount+=oldSize;


		// we do this as Dt might have been changed inside realloc if it didnt extend memory and internally created new memory and copied contents
		Dt = *dt;
		Dt-> arr = newArr;
		Dt-> capacity = newCapacity;

	}



}


//following lines were just used as personal testging and not part of the submission

// int main() {

// 	dynamicTable * dt = make_new_dynamic_table(1);
// 	for (int i = 0; i < 10; i++) {
// 		push_back((void**)&dt, 5);
// 		printf("%d  %d\n", dt -> size, dt -> capacity);
// 	}

// 	printf("PopBack\n");
// 	for (int  i = 0; i < 9; i++) {
// 		pop_back((void**)&dt);
// 		// printf("%d  %d\n", dt -> size, dt -> capacity);


// 	}
// 	return 0;
// }
