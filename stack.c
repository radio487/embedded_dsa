/*
 * Stack implementation using an array.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE 20

struct lifo {
  int data[SIZE];
  uint16_t ipush;
};

void init_lifo(struct lifo *s) {
  s->ipush = 0;
}
bool lifo_isempty(struct lifo *s) {
  return s->ipush == 0;
}
bool lifo_isfull(struct lifo *s) {
  return s->ipush == SIZE;
}
// bool return to signal if the stack is full
bool lifo_push(struct lifo *s, int val) {
  if (lifo_isfull(s)) {
    return false;
  }
  else {
    s->data[s->ipush] = val;
    s->ipush += 1;
    return true;
  }
}
// bool return to signal if the stack is empty
// popped value stored in val
bool lifo_pop(struct lifo *s, int *val) {
  if (lifo_isempty(s)) {
    return false;
  }
  else {
    *val = s->data[s->ipush-1];
    s->ipush--;
    return true;
  }
}

int main() {
  static struct lifo s;
  int val;
  
  init_lifo(&s);
  for (int i = 0; i < SIZE; ++i) {
    lifo_push(&s, i);
  }
  for (int i = 0; i < SIZE; ++i) {
    lifo_pop(&s, &val);
    printf("%d\n", val);
  }

  return 0;
}
