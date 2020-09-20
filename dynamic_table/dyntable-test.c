#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "dyntable_impl.h"

// static float 0.25 = 0.25;
// const float push_threshold_factor = 0.75;
// const float pop_threshold_factor = 0.5;


double push_threshold_factor = 0.75;
double pop_threshold_factor = 0.35;

int copyCount = 0;

typedef struct dynamicTable {
	int *arr;
	int capacity;
	int size;

} dynamicTable;

//1 0.25
//0.8 0.2
//0.7 0.6


void* make_new_dynamic_table(int n) {
	dynamicTable* dt = malloc(sizeof(dynamicTable));
	if (dt == NULL) {
		printf("unable to allocate memory on heap!\n");
		return NULL;
	}
	dt -> capacity = n;
	dt -> size = 0;
	dt -> arr = malloc(sizeof(int) * n);
	return dt;
}

void push_back(void** dt, int item) {



	dynamicTable*Dt = *dt;
	// printf("push item : %d\n", item);
	// printf("size %d\n", Dt->size);
	float threshold = Dt -> size / (float) Dt -> capacity;
	if (threshold >= push_threshold_factor) {
		//we need to increase by 1.5
		int newCapacity = (int)ceil((double)Dt -> capacity * 1.5);
		int* newArr = realloc(Dt->arr, (int)(sizeof(int) * newCapacity));
		if (newArr == NULL) {
			printf("unable to allocate memory on heap!\n");
			return;
		}
		// int i;
		// for (int i = 0; i < Dt -> size ; i++) {
		// 	newArr[i] = Dt -> arr[i];
		// }

		// free(Dt->arr);
		if (Dt->arr != newArr)
			copyCount++;

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

	if (Dt->size <= 0)
		return;

	// printf( "Pop: %d\n" , Dt->arr[Dt->size - 1]);
	Dt -> size  = Dt -> size - 1;

	float threshold = Dt -> size / (float) Dt -> capacity;

	if (threshold <= pop_threshold_factor) {
		int newCapacity  = ceil(1.5 * pop_threshold_factor * Dt -> capacity);
		int* newArr = realloc(Dt->arr, (int)(sizeof(int) * newCapacity));
		if (newArr == NULL) {
			printf("unable to allocate memory on heap!\n");
			return;
		}
		// int i;
		// for (int i = 0; i < Dt -> size ; i++) {
		// 	newArr[i] = Dt -> arr[i];
		// }

		// free(Dt->arr);
		if (Dt->arr != newArr)
			copyCount++;

		Dt = *dt;
		Dt-> arr = newArr;
		Dt-> capacity = newCapacity;

	}



}

int getCount() {
	return copyCount;
}

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