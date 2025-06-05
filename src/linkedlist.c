#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

//private helper to create node
static Node* _create_node(int data, Node* prev, Node* next) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (!newNode) {
    perror("NODE - malloc error\n");
    return NULL;
  }
  
  newNode->data = data;
  newNode->prev = prev;
  newNode->next = next;

  return newNode;
}

dll* create_dll() {
  //allocate space for list
  dll* list = (dll*)malloc(sizeof(dll));
  if (!list) {
      perror("list - malloc error\n");
      return NULL;
    }
  
  //initialize head and tail
  list->head = _create_node(-1, NULL, NULL);
  list->tail = _create_node(-1, NULL, NULL);
  
  //if malloc failed, return null
  if (!list->head || !list->tail) {
        if (list->head) free(list->head);
        if (list->tail) free(list->tail);
        free(list);
        return NULL;
  }

  //set dummy values, connect head and tail
  list->head->next = list->tail;
  list->tail->prev = list->head;
  list->size = 0;

  return list;
}

// add a node after another given node
void add_after(dll* list, int item, Node* node) {
  if (!list || !node) return;
  if (node == list->tail) return;

  Node* newNode = _create_node(item, node, node->next);

  node->next->prev = newNode;
  node->next = newNode;
  list->size++;
}

//at node after the head
void add_first(dll* list, int item) {
  if (!list) return;
  add_after(list, item, list->head);
}

//add node before the tail
void add_last(dll* list, int item) {
  if (!list) return;
  //printf("Adding last: %d\n", item);
  add_after(list, item, list->tail->prev);
}

//just a more simplified add (at then end)
void add(dll* list, int item) {
    add_last(list, item);
  }

//returns node after head
Node* get_first(dll* list) {
    if (!list || list->size == 0) return NULL;
    return list->head->next;
  }

//returns node after last
Node* get_last (dll* list) {
    if (!list || list->size == 0) return NULL;
    return list->tail->prev;
  }

//removed node after head
void rm_first(dll* list) {
    if (!list || list->size == 0) return;

    Node* rm_node = list->head->next;
    list->head->next->next->prev = list->head;
    list->head->next = list->head->next->next;

    free(rm_node);
    list->size--;
  }

//removes node before tail
void rm_last(dll* list) {
    if (!list || list->size ==0) return;

    Node* rm_node = list->tail->prev;
    list->tail->prev->prev->next = list->tail;
    list ->tail->prev = list->tail->prev->prev;
    
    free(rm_node);
    list->size--;
  }


bool list_contains(dll* list, int value) {
  if (list==NULL) return false;

  Node* current = list->head;
  while (current != NULL) {
    //printf("checking node with value: %d\n", value);
    if (current->data == value) return true;
    current = current->next;
  }
  return false;
}

//prints out each node
void print_dll(dll* list) {
    if (!list) return;

    Node* n = list->head->next;
    printf("[-");
    while (n != list->tail) {
      printf("%d-", n->data);
      n = n->next;
    }
  printf("]");
  }

//frees up the allocated memory
void free_dll(dll* list) {
    if (!list) return;

    Node* curr = list->head->next;
    //all nodes from after head to before tail are free'd
    while (curr != list->tail) {
      Node* next = curr->next;//need to assign the next node before clearing the curr
    //avoids seg fault
      free(curr);
      curr = next;
    }
    
    if (list->head) free(list->head);
    if (list->tail) free(list->tail);
    free(list);
  }
