/*
* Detect a four byte sequence in a stream
* IN CONSTRUCTION I NEED A hex to string program
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define TARGET 0x00AD01B2
#define STREAM 0x1223BF58A19DD00AD01B25761E8FF21AB445

bool process_byte(uint8_t b) {
  static uint32_t c = 0;
  
  c = (c << 8) | b;
  return c == TARGET;
}

int main () {
  int i = 0;

  while (!process_byte((STREAM << (i*8)) & 0xFF)) {
    ;
  }
  
  printf("Found it\n");
  return 0;
}
