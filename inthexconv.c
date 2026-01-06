#include <stdio.h>

#define INTS 11

char *int2hex(unsigned int x) {
  char symbols[] = "0123456789abcdef";
  char s[30];  
  int i = 0;
  do {
    s[i++] = symbols[(x & 0xf)];
    x >>= 4;
  } while (x);
  return s;
}

int main () {
  for (int i = 0; i < INTS; ++i) {
    printf("%s\n", int2hex(i));
  }

  return 0;
}
