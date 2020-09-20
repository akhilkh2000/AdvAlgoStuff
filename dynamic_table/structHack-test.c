#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "dyntable_impl.h"

static float decrease_factor = 0.25;
double push_threshold_factor = 0.75;
double pop_threshold_factor = 0.35;

int copyCount = 0;

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
	float threshold = Dt -> size / (float) Dt -> capacity;
	if (threshold >= push_threshold_factor) {
		//we need to increase by 1.5
		int curr_capacity = Dt -> capacity;
		int newCapacity = ceil(curr_capacity * 1.5);
		int size = Dt -> size;

		dynamicTable* temp = realloc(Dt, sizeof(dynamicTable) + sizeof(int) * newCapacity);
		if (temp == NULL) {
			//printf("unable to allocate memory on heap!\n");
			return;
		}
		if (temp != Dt) // that means internally copy operation took place as there was no space to extend memory there
			copyCount++;
		temp ->capacity = newCapacity;
		temp ->size = size;

		//maybe while realloc Dt might have to undergo a malloc because of no extendable memory in that space so we cant directly assume Dt still points to *dt

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

	float threshold = Dt -> size / (float) Dt -> capacity;

	if (threshold <= pop_threshold_factor) {

		int size = Dt ->size;
		int newCapacity  = ceil(1.5 * decrease_factor * Dt -> capacity);
		dynamicTable *temp = realloc(Dt, sizeof(dynamicTable) + sizeof(int) * newCapacity);
		if (temp == NULL) {
			//printf("unable to allocate memory on heap!\n");
			return;
		}
		if (temp != Dt) // that means internally copy operation took place as there was no space to extend memory there
			copyCount++;

		temp -> capacity = newCapacity;
		temp ->size = size;
		*dt = temp;
		Dt = *dt;

	}



}


int getCount() {
	copyCount++;
}