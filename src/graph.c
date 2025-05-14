#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* create_graph(int num_vertices) {
  if (num_vertices <= 0) return NULL;

  Graph* graph = malloc(sizeof(Graph));
  if (graph==NULL) {
    printf("Error allocating graph\n"); 
    return NULL;
  }

  //allocates memory for 'num_vertices' amount of vertices
  //sets elt values to 0 (calloc initializes to 0)
  graph->vertices = calloc(num_vertices, sizeof(Vertex));
  if (graph->vertices==NULL) {
    printf("Error allocating vertices\n");
    free(graph);
    return NULL;
  };
  
  //allocates memory an adj_list per vertex, all set to the size of a dll pointer
  //initially all NULL from calloc
  graph->adj_lists = calloc(num_vertices, sizeof(dll*));
  if (graph->adj_lists==NULL) {
    printf("Error allocating adj_lists\n");
    free(graph);
    free(graph->vertices);
    return NULL;
    }
  
  graph->num_vertices = num_vertices;

  return graph;
}

void destroy_graph(Graph* graph) {
  if (graph==NULL) return;

  //free all individual dll's if they exist
  for (int i=0; i<graph->num_vertices; i++) {
    if (graph->adj_lists[i] != NULL) {
      free_dll(graph->adj_lists[i]);
    }
  }

  free(graph->adj_lists);
  free(graph->vertices);
  free(graph);
}


bool add_edge(Graph* graph, int v1_index, int v2_index) {
  if ((v1_index >= graph->num_vertices || v1_index < 0) ||
      (v2_index >= graph->num_vertices || v2_index < 0)) return false;

  if (graph->adj_lists[v1_index]==NULL) {
    graph->adj_lists[v1_index] = create_dll();
  }
  if (graph->adj_lists[v2_index]==NULL) {
    graph->adj_lists[v2_index] = create_dll();
  }

/*
  printf("Before checking: is %d in %d's list? %s\n",
       v1_index, v2_index,
       list_contains(graph->adj_lists[v2_index], v1_index) ? "yes" : "no");

  printf("Before checking: is %d in %d's list? %s\n", v2_index, v1_index,
         list_contains(graph->adj_lists[v1_index], v2_index) ? "yes" : "no");
*/

  //if the dll at v1_index does not contain v2_index, add it
  if (!list_contains(graph->adj_lists[v1_index], v2_index)) {
    add_last(graph->adj_lists[v1_index], v2_index);
  }
  if (!list_contains(graph->adj_lists[v2_index], v1_index)) {
    add_last(graph->adj_lists[v2_index], v1_index);
  }

  return true;

}

void print_graph(Graph* graph) {

  if (graph == NULL) {
    printf("graph is NULL\n");
    return;
  }
  
  for (int i = 0; i < graph->num_vertices; i++) {
    printf("vertex %d -> ", i);
    print_dll(graph->adj_lists[i]);
    printf("\n");
  }
}
