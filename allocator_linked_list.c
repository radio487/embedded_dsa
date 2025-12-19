/*
 * Fixed size pool allocator to store my own linked lists in .bss
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define POOL_SIZE 3
#define TEST_SIZE 4

struct node {
  int val;
  struct node *next;
};
struct block {
  struct node n;
  struct block *next;
};

struct block pool[POOL_SIZE];
struct block *free_list = pool + 0;

void init_pool(void) {
  for (int i = 0; i < POOL_SIZE-1; ++i) {
    pool[i].next = pool+i+1;
  }
  pool[POOL_SIZE-1].next = NULL;
}
bool pool_isfull(void) {
  return free_list == NULL;
}
// allocates a block but only returns the node pointer
struct node *allocate_block(void) {
  if (pool_isfull()) {
    return NULL;
  }
  struct block *b = free_list;
  free_list = free_list->next;
  return &(b->n);
}
// We need pointer arithmetic to recover the node's block address
void free_block(struct node *n) {
  // n is the first element of struct node, so they share the address
  struct block *b = (struct block *) n;
  b->next = free_list;
  free_list = b;
}

// With dummy head
struct node *init_linked_list(void) {
  struct node *head = allocate_block();
}

int main() {
  init_pool();
   
  printf("Success\n");
  return 0;
}
