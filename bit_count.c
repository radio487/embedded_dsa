/*
 * Three variants. The first iterates all the bits by comparing with 1, and right shifting each round. Scales linearly with the amount of bits in the int.
 *
 * The second is from Brian Kerningham (it can be found in a K&R exercise) and uses a clever way to set the least significant non-zero bit to zero to abort the loop in a way that scales linearly with the number of set bits.
 *
 * The third is a lookup table that trades speed for memory. I will compute the table with Kerningham's algorithm
 */

#include <stdio.h>
#include <stdint.h>

#define TEST_INTS 40
#define TABLE_SIZE 256

static uint8_t lookup_table[TABLE_SIZE];

uint8_t bitcount_naive(uint32_t a) {
  uint8_t c = 0;
  while (a) {
    if (a & 1) {
      c++;
    }
    a>>=1;
  }
  return c;
}
int bitcount_kerningham(uint32_t a) {
  uint8_t c = 0;
  while (a) {
    c += 1;
    a &= a - 1;
  }
  return c;
}
void compute_table(uint8_t *t) {
  for (int i = 0; i < TABLE_SIZE; ++i) {
    t[i] = bitcount_kerningham(i);
  }
}
int bitcount_table(uint32_t a) {
  uint8_t c = 0;
  while (a) {
    c += lookup_table[a & 0xFF]; 
    a >>= 8;
  }
  return c;
}

int main() {
  
  compute_table(lookup_table);

  for (int i = 0; i < TEST_INTS; ++i) {
    printf("%b\n", i);  
    printf("%d\n", bitcount_naive(i));  
    printf("%d\n", bitcount_kerningham(i));  
    printf("%d\n", bitcount_table(i));  
    printf("------\n");
  }

  return 0;
}
