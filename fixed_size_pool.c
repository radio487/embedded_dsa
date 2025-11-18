#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// in element numbers
#define POOL_SIZE 10
#define BLOCK_SIZE 100

struct block {
  struct block *next;
  // I choose chars for no good reason
  char str[BLOCK_SIZE];
};

struct block pool[POOL_SIZE];
struct block *f_list = pool+0;

void init_pool(void) {
  struct block *b;
  int i = 1;

  for (b = f_list; i < POOL_SIZE; b = b->next) {
    b->next = pool+i;
    i++;
  }
  b->next = NULL;
}
bool free_list_isempty(void) {
  return f_list == NULL;
}
struct block *allocate_block(void) {
  struct block *b = f_list;
  if (free_list_isempty()) {
    return NULL;
  }
  else {
     f_list = f_list->next;
     return b;
  }
}
void free_list_free(struct block *b) {
  b->next = f_list;
  f_list = b;
}

int main() {
  struct block *b;

  init_pool();
  b = allocate_block();
  allocate_block();
  allocate_block();
  allocate_block();
  free_list_free(b);
  free_list_free(b);
  free_list_free(b);
  allocate_block();
  
  return 0;
}
