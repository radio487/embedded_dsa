/*
 * EDIT
 * Fixed size memory pool with an array stack as the free list
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define BLOCKSIZE 200
#define POOLSIZE 128

struct block {
  char data[BLOCKSIZE];
};
uint32_t ipush = 0;
int free_list[POOLSIZE];
struct block pool[POOLSIZE];

// We implement a stack to handle pool block handling
bool free_list_isempty(void) {
  return ipush == 0;
}
bool free_list_isfull(void) {
  return ipush == POOLSIZE;
}
bool free_list_push(int val) {
  if (free_list_isfull()) {
    return false;
  }
  else {
    free_list[ipush++] = val;
    return true;
  }
}
bool free_list_pop(int *val) {
  if (free_list_isempty()) {
    return false;
  }
  else {
    *val = free_list[--ipush];
    return true;
  }
}

// We now implement the pool block handling
void init_pool() {
  for (int i = 0; i < POOLSIZE; ++i) {
    free_list_push(i);
  }
}
struct block *allocate_block(void) {
  int val;
  // Failure check
  if (!free_list_pop(&val)) {
    return NULL;
  }
  return pool + val;
}
// making this boolean and allocate_block not is 
// inconsistent but for this simple approach it's fine
bool free_block(struct block *b) {
  if (!free_list_push(b-pool)) {
    return false;
  }
  return true;
}

int main() {
  struct block *b0, *b1, *b2, *b3;
  init_pool();
  b0 = allocate_block(); 
  b1 = allocate_block(); 
  b2 = allocate_block(); 
  free_block(b1);
  b1 = allocate_block(); 


  return 0;
}
