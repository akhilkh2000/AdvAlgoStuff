#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "dyntable_impl.h"

int count = 0;

struct dt
{
  int capacity;
  int size;
  int *arr;
};

void *make_new_dynamic_table(int n)
{
  struct dt *temp = malloc(sizeof(struct dt));
  temp->capacity = n;
  temp->size = 0;
  temp->arr = malloc(sizeof(int) * n);
  return temp;
}

void push_back(void **dtp, int data)
{
  struct dt *ptr = *dtp;
  float check = ptr->size / (float) ptr->capacity;
  if (check > 0.75)
  {
    count++;
    int curr_capacity = ptr->capacity;
    int new_capacity = ceil(1.5 * curr_capacity);
    //printf("increasing capacity from %d to %d when there are %d elements\n", curr_capacity, new_capacity, ptr->size);
    int *temp = malloc(sizeof(int) * new_capacity);
    for (int i = 0; i < ptr->size; i++)
    {
      temp[i] = ptr->arr[i];
    }
    free(ptr->arr);
    ptr->arr = temp;
    ptr->capacity = new_capacity;
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
  float check = ptr->size / (float) ptr->capacity;
  if (check < 0.35)
  {
    count++;
    int new_capacity = ceil(1.5 * 0.35 * ptr->capacity);

    //printf("decreasing capacity from %d to %d when there are %d elements\n", ptr->capacity, new_capacity, ptr->size);

    int *temp = malloc(sizeof(int) * ptr->size);
    for (int i = 0; i < ptr->size; i++)
    {
      temp[i] = ptr->arr[i];
    }
    ptr->capacity = new_capacity;
  }
}

int getCount() {return count;}

/*

int main()
{
  clock_t time_taken;
  time_taken = clock();
  struct dt *temp = make_new_table(2);

  for (int i = 0; i < 100000; i++)
  {
    push_back(&temp, i);
    // printf("%d, %d\n", temp->size, temp->capacity);
  }

  // printf("%d is the size after 100 pushs\n", sizeof(*temp));

  // printf("Printing array\n");
  // for (int i = 0; i < 50; i++)
  // {
  //   printf("%d --> %d\n", i, temp->arr[i]);
  // }

  printf("Popping elements\n");
  for (int i = 0; i < 100000; i++)
  {
    pop_back(&temp);
    // printf("%d, %d\n", temp->size, temp->capacity);
  }

  time_taken = clock() - time_taken;
  double ans = ((double)time_taken / CLOCKS_PER_SEC);
  printf("fun() took %f seconds to execute \n", ans);
  return 0;
}

*/
