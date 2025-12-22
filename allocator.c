#include <stdio.h>
#include <stdbool.h>

#define POOL_SIZE 256

struct node {
  union {
    struct {
      struct node *l;
      struct node *r;
    };
    struct node *next;
  };
  int val;
};

struct node pool[POOL_SIZE];
struct node *free_list = pool + 0;

// Allocator
void init_pool(void) {
  for (int i = 0; i < POOL_SIZE-1; ++i) {
    pool[i].next = pool + i + 1;
  }
  pool[POOL_SIZE-1].next = NULL;
}
bool pool_isempty(void) {
  return free_list == NULL;
}
struct node *allocate(void) {
  if (pool_isempty()) {
    return NULL;
  }
  struct node *n = free_list;
  free_list = free_list->next;
  return n;
}
void free_node(struct node *n) {
  n->next = free_list;
  free_list = n;
}

// BST
struct node *init_bst(int val) {
  struct node *h = allocate();
  if (h == NULL) {
    return NULL;
  }
  h->val = val;
  h->l = NULL;
  h->r = NULL;
  return h;
}
void insert_bst(struct node *h, int val) {
  if (val <= h->val) {
    if (h->l == NULL) {
      struct node *n = allocate();
      if (n == NULL) {
        return;
      }
      n->val = val;
      n->l = NULL;
      n->r = NULL;
      h->l = n;
      return;
    }
    else {
      insert_bst(h->l, val);
      return;
    } 
  }
  else {
    if (h->r == NULL) {
      struct node *n = allocate();
      if (n == NULL) {
        return;
      }
      n->val = val;
      n->l = NULL;
      n->r = NULL;
      h->r = n;
      return;
    }
    else {
      insert_bst(h->r, val);
    }
  }
}
void inorder(struct node *h) {
  if (h->l != NULL) {
    inorder(h->l);
  }
  printf("%d\n", h->val);
  if (h->r != NULL) {
    inorder(h->r);
  }
}

int main() {
  init_pool();
  int a[10] = {1, 2, 10, -2, 0, 11, -14, 7, 8, -20};
  
  struct node *h = init_bst(a[0]);
  for (int i = 1; i < 10; ++i) {
    insert_bst(h, a[i]);
  }
  inorder(h);

  printf("Success\n");
  return 0;
}
