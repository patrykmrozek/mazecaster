#ifndef DLL_H
#define DLL_H

#include <stdbool.h>

typedef struct Node {
  int data;
  //must use struct Node* as the Node type hasnt been defined yet
  struct Node* prev;
  struct Node* next;
} Node;

typedef struct dll {
  Node* head;
  Node* tail;
  int size;
} dll;

dll* create_dll();
void add_after(dll* list, int item, Node* node);
void add_first(dll* list, int item);
void add_last(dll* list, int item);
void add(dll* list, int item);
Node* get_first(dll* list);
Node* get_last(dll* list);
void rm_first(dll* list);
void rm_last(dll* list);
bool list_contains(dll* list, int value);
void print_dll(dll* list);
void free_dll(dll* list);

#endif 
