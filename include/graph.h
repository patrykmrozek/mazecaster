#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdint.h>
#include "linkedlist.h" 

typedef struct vertex{
  uint8_t elt; //1 or 0
} vertex_t;

typedef struct graph {
  vertex_t*  vertices; //pointer to an array fo vertex struct
                    //vertices and their neighbours can be accessed through shared index i
  dll** adj_lists; //pointer to an array of dll*
                   //adj_lists[i] holds DLL to all neighbours of vertex i
  int num_vertices;
} graph_t;


graph_t* create_graph(int num_vertices);
void destroy_graph(graph_t* graph);
bool add_edge(graph_t* graph, int v1_index, int v2_index);
void print_graph(graph_t* graph);


#endif
