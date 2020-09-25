#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dyntable_impl.h"

struct dt
{
  int capacity;
  int size;
  //---------------------
  //long count;
  //---------------------
  int *arr;
};

void *make_new_dynamic_table(int n)
{
  struct dt *temp = malloc(sizeof(struct dt));
  temp->capacity = n;
  temp->size = 0;
  //-------------------------
  //temp->count = 0;
  //-------------------------
  temp->arr = malloc(sizeof(int) * n);
  return temp;
}

void push_back(void **dtp, int data)
{
  struct dt *ptr = *dtp;
  if (ptr->capacity == ptr->size)
  //-------------if conditions for different thresholds----------------------
  //float check = ptr->size / (float) ptr->capacity;
  //if(check > 0.9)
  //------------------------------------------------------------------------

  {
    int curr_capacity = ptr->capacity;
    int new_capacity = ceil(1.5 * curr_capacity);
    int *temp = malloc(sizeof(int) * new_capacity);
    for (int i = 0; i < ptr->size; i++)
    {
      temp[i] = ptr->arr[i];
    }
    free(ptr->arr);
    ptr->arr = temp;
    ptr->capacity = new_capacity;
    //---------------------------------------
    //ptr->count += ptr->size;
    //---------------------------------------
  }
  ptr->arr[ptr->size++] = data;
}

void pop_back(void **dtp)
{
  struct dt *ptr = *dtp;
  if (ptr->size <= 0)
  {
    return;
  }
  ptr->size--;
  if (ptr->size <= 0.25 * ptr->capacity)
  //-------------if conditions for different thresholds----------------------
  //if(ptr->size <= 0.2 * ptr->capacity)
  //------------------------------------------------------------------------

  {
    int new_capacity = ceil(1.5 * 0.25 * ptr->capacity);
    /*-------------------------------------------------------*/
    //int new_capacity = ceil(1.5 * 0.2 * ptr->capacity);
    /*-------------------------------------------------------*/
    int *temp = malloc(sizeof(int) * ptr->size);
    for (int i = 0; i < ptr->size; i++)
    {
      temp[i] = ptr->arr[i];
    }
    ptr->capacity = new_capacity;
    //---------------------------------------
    //ptr->count += ptr->size;
    //---------------------------------------
  }
}

/*

long get_count(void ** dtp) {
	struct dt* ptr = *dtp;
	return ptr->count;
}

*/
