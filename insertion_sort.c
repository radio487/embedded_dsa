#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 16

void populate_array(int *a, int size, int max) {
  srand(123);
  for (int i = 0; i < size; ++i) {
     a[i] = rand() % (max +1);
  }
}
void print_array(int *a, int size) {
  for (int i = 0; i < size; ++i) {
     printf("%d\n", a[i]);
  }
}
void insertion_sort(int *a, int size) {
  int i, j, k;
  for (i = 1; i < size; ++i) {
    k = a[i];
    for (j = i-1; j >= 0 && k < a[j]; --j) {
      a[j+1] = a[j];
    }
    a[j+1] = k;
  }
}

int main() {
  int a[ARR_SIZE], max = 10;

  populate_array(a, ARR_SIZE, max);
  print_array(a, ARR_SIZE);
  printf("------\n");
  insertion_sort(a, ARR_SIZE);
  print_array(a, ARR_SIZE);

  return 0;
}
