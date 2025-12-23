/*
* Hash map implementation. I use chaining to deal with collision. For simplicity we use mod hashing, although if the microcontroller has no hardware for division another hash function should be used
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 20

struct data {
  struct data *next;
  int key;
  int val;
};
struct data* hm[SIZE];

// Dummy nodes at the head of the lists
void hm_init(void) {
  for (int i = 0; i < SIZE; ++i) {
    // On the next version I will avoid malloc for my own fixed sized memory pool
    hm[i] = malloc(sizeof(struct data));
    // Dummy key and value
    hm[i]->key = -1;
    hm[i]->val = -1;
    hm[i]->next = NULL;
  }
}
int hash(int key) {
  return key % SIZE;
}
// In a LIFO fashion
void ll_insert(struct data *head, struct data *d) {
  d->next = head->next;
  head->next = d;
}
void hm_insert(struct data *d) {
  ll_insert(hm[hash(d->key)], d);
}
int hm_search(int key) {
  struct data *d;
  for (d = hm[hash(key)]; d != NULL; d = d->next) {
    if (d->key == key) {
      return d->val;
    }
  }
  // failure
  return -1;
}

int main() {
  struct data d0, d1;
  d0.key = 10;
  d0.val = 11;
  d1.key = 12;
  d1.val = 15;

  hm_init();
  hm_insert(&d0);
  hm_insert(&d1);
  for (int i = 0; i < 20; ++i) {
    printf("key=%d, val=%d\n", i, hm_search(i));
  }

  printf("Success\n");
  return 0;
}
