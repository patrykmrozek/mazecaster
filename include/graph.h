#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdint.h>
#include "linkedlist.h" 

typedef struct {
  uint8_t elt; //1 or 0
} Vertex;

typedef struct {
  Vertex* vertices; //pointer to an array fo vertex struct
                    //vertices and their neighbours can be accessed through shared index i
  dll** adj_lists; //pointer to an array of dll*
                   //adj_lists[i] holds DLL to all neighbours of vertex i
  int num_vertices;
} Graph;


Graph* create_graph(int num_vertices);
void destroy_graph(Graph* graph);
bool add_edge(Graph* graph, int v1_index, int v2_index);
void print_graph(Graph* graph);


#endif
