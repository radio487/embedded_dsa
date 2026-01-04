/*
* int to hex string
*/

#include <stdio.h>
#include <stdint.h>

#define TEST_INTS 20

void int_to_hex_string(uint32_t a, char *buff) {
  static const char hexchars[] = "0123456789ABCDEF";
  
  for (int i = 7; i >= 0; --i) {
    buff[i] = hexchars[a & 0xF];
    a >>= 4;
  }
  buff[8] = '\0';
}

int main () {
  char buffer[9];

  for (uint32_t i = 0; i < TEST_INTS; ++i) {
    int_to_hex_string(i, buffer);
    printf("number is = %d, string is %s\n-------\n", i, buffer);
  }

  return 0;
}
