#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "dyntable_impl.h"

static float decrease_factor = 0.25;

typedef struct dynamicTable {
	int capacity;
	int size;
	int  arr[0];
} dynamicTable;


void* make_new_dynamic_table(int n) {
	dynamicTable* dt = (dynamicTable*)malloc(sizeof(dynamicTable) + (sizeof(int) * n));
	dt -> capacity = n;
	dt -> size = 0;
	return dt;
}

void push_back(void **dt, int item) {

	dynamicTable *Dt = *dt;
	if (Dt->size == Dt->capacity) {
		//we need to increase by 1.5
		int curr_capacity = Dt -> capacity;
		int newCapacity = ceil(curr_capacity * 1.5);
		int size = Dt -> size;

		dynamicTable* temp = realloc(Dt, sizeof(dynamicTable) + sizeof(int) * newCapacity);
		temp ->capacity = newCapacity;
		temp ->size = size;

		//maybe while realloc Dt might have to undergo a malloc because of no extendable memory in that space so we cant directly assume Dt still points to *dt
		
			//following commented lines were used to test the copyCount in the tests file . 
		//if (Dt->arr != newArr)
		//	copyCount++;

		*dt = temp;
		Dt = *dt;



	}

	Dt -> arr[Dt->size++] = item;

}

void pop_back(void**dt) {


	dynamicTable*Dt = *dt;

	if (Dt->size == 0)
		return;

	Dt -> size -= 1;



	if (Dt -> size <= (Dt -> capacity * decrease_factor)) {

		int size = Dt ->size;
		int newCapacity  = ceil(1.5 * decrease_factor * Dt -> capacity);
		dynamicTable *temp = realloc(Dt, sizeof(dynamicTable) + sizeof(int) * newCapacity);
		temp -> capacity = newCapacity;
		temp ->size = size;
		
			//following commented lines were used to test the copyCount in the tests file . 
		//if (Dt->arr != newArr)
		//	copyCount++;
		
		*dt = temp;
		Dt = *dt;

	}



}

