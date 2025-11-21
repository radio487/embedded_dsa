/*
 * Clever code snippet. If an int is a power of two it will have one 1 on binary. Subtracting 1 to the number necessarily moves the bits location in the binary representation. Thus a bitwise and yields zero.
 */

#include <stdio.h>

int pow_two(unsigned int a) {
  // we need to avoid a = 0 corner case hence the &&
  return a && !(a & (a-1));
}

int main() {
  unsigned int a = 1;
  for (int i = 0; i < 20; ++i) {
    printf("%d\n", pow_two(a));
    a *= 2;
  } 
}
