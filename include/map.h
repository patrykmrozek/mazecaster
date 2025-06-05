#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "window.h"
#include "graph.h"
#include "stack.h"

/*
// extern pretty much tells the compiler that the following variable exists somewhere
// variables defined in header files cause linker errors
extern int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern const int TILE_SIZE;

extern const int MAP[][8];
*/

typedef struct {
  int** grid; //map->grid[row][col]
  int width;
  int height;
  int tile_size;
} Map;

Map* generate_maze(int n);
void _generate_maze(Map* map, bool* visited, int row, int col, int size, int n);
Graph* map_to_graph(Map* map, Graph* graph);
void generate_maze_exit(Map* map, Graph* graph);
void _dfs(Graph* g, bool marked[], int v, int* final_cell);
bool is_exit(Map* map, int i, int j);
void destroy_map(Map* map);

#endif

