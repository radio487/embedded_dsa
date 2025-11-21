/*
 * Two variants. The first iterates all the bits by comparing with 1, and right shifting each round
 * Study the K&R method and its relation to two's complement.
 */
#include <stdio.h>

int bitcount1(unsigned int a) {
  int c = 0;
  while (a) {
    if (a & 1) {
      c++;
    }
    a>>=1;
  }
  return c;
}

int main() {
  int a = 8;
  printf("%b\n", a);  
  printf("%d\n", bitcount1(a));  

  return 0;
}
