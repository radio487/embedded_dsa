/*
* This one is more of a curiosity, but apparently xor can be used to swap without needing extra variables
* I have checked the generated assembly and the normal swap generates shorter code. Still, it is nice to know this trick.
* The reason it works is due to the following property of XOR
* a^b^b == a
*/

#include <stdio.h>

#define SIZE 10

void normal_swap(int *a, int i, int j) {
  int s = a[i];
  a[i] = a[j];
  a[j] = s;
}
void xor_swap(int *a, int i, int j) {
  a[i] ^= a[j];
  a[j] ^= a[i];
  a[i] ^= a[j];
}
void print_array(int *a, int size) {
  for (int i = 0; i < SIZE; ++i) {
    printf("%d\n", a[i]);
  }
  printf("------\n");
}

int main () {
  int a[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  print_array(a, SIZE);
  normal_swap(a, 2, 3);
  print_array(a, SIZE);
  xor_swap(a, 2, 3);
  print_array(a, SIZE);

  return 0;
}
