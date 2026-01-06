/*
 * FIFO queue implementation using a circular buffer
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// There are two implementations: either keep SIZE-1 elements max, or explicitly count number of elements. We choose the first, so 19 elements max
#define SIZE 20

struct fifo {
  uint16_t ipush;
  uint16_t ipop;
  int data[SIZE];
};

void fifo_init(struct fifo *f) {
  f->ipush = 0;
  f->ipop = 0;
}
bool fifo_isempty(struct fifo *f) {
  return f->ipush == f->ipop;
}
bool fifo_isfull(struct fifo *f) {
  return (f->ipush + 1)%SIZE == f->ipop;
}
// false denotes a full queue
bool fifo_push(struct fifo *f, int val) {
  if (fifo_isfull(f)) {
    return false;
  }
  else{
    f->data[f->ipush] = val;
    f->ipush = (f->ipush + 1)%SIZE;
    return true;
  }
}
// false denotes a empty queue
// popped value stored in val
bool fifo_pop(struct fifo *f, int *val) {
  if (fifo_isempty(f)) {
    return false;
  }
  else{
    *val = f->data[f->ipop];
    f->ipop = (f->ipop + 1)%SIZE;
    return true;
  }
}

int main() {
  static struct fifo f;
  int val;

  fifo_init(&f);
  for (int i = 0; i < SIZE; ++i) {
    fifo_push(&f, i);
  }
  for (int i = 0; i < SIZE; ++i) {
    fifo_pop(&f, &val);
    printf("%d\n", val);
  }
  return 0;
}
