/*
 * Fixed size pool allocator to store my own linked lists in .bss to implement a stack. Of course, this is just an exercise to implement dynamic data structures without malloc. In a real scenario, this solution would be redundant in the sense that I could just use a global array to implement a stack.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define POOL_SIZE 64

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
  if (head == NULL) {
    return NULL;
  }
  head->val = -1;
  head->next = NULL;
  return head;
}
bool ll_isempty(struct node *head) {
  return head->next == NULL;
}
bool ll_push(struct node *head, int val) {
  struct node *n = allocate_block();
  if (n == NULL) {
    return false;
  }
  n->val = val;
  n->next = head->next;
  head->next = n;
  return true;
}
int ll_pop(struct node *head) {
  if (ll_isempty(head)) {
    return -1;
  }
  struct node *n = head->next;
  int val = n->val;
  head->next = n->next;
  free_block(n);
  
  return val;
}

int main() {
  init_pool();
  struct node *head = init_linked_list();
  struct node *p;
  int ll_size = 10;
  
  printf("Here\n");
  for (int i = 0; i < ll_size; ++i) {
    if (ll_push(head, i)) {
      ;
    }
    else {
      while(1) {
        printf("Allocation failed\n");
      }
    }
  }
  for (p = head->next; p != NULL; p = p->next) {
    printf("%d\n", p->val);
  }

  printf("Success\n");
  return 0;
}
