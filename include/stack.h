#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int* collection;
  int capacity;
  int size;
} Stack;

Stack* create_stack(int capacity);
void destroy_stack(Stack* stack);
bool is_full(Stack* stack);
bool is_empty(Stack* stack);
bool pop(Stack* stack, int* item);
bool push(Stack* stack, int item);
bool peek(Stack* stack, int* item);

#endif
