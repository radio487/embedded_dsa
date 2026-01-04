/*
 * Two variants. The first iterates all the bits by comparing with 1, and right shifting each round. Scales linearly with the amount of bits in the int.
 * The second is from Brian Kerningham (it can be found in a K&R exercise) and uses a clever way to set the least significant non-zero bit to zero to abort the loop in a way that scales linearly with the number of set bits.
 */

#include <stdio.h>

#define SIZE 20

int bitcount_naive(unsigned int a) {
  int c = 0;
  while (a) {
    if (a & 1) {
      c++;
    }
    a>>=1;
  }
  return c;
}
int bitcount_kerningham(unsigned int a) {
  int c = 0;
  while (a) {
    c += 1;
    a &= a - 1;
  }
  return c;
}

int main() {
  for (int i = 0; i < SIZE; ++i) {
    printf("%b\n", i);  
    printf("%d\n", bitcount_naive(i));  
    printf("%d\n", bitcount_kerningham(i));  
    printf("------\n");
  }

  return 0;
}
