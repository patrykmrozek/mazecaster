#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "renderer.h"
#include "window.h"
#include "graph.h"
#include "stack.h"

// extern pretty much tells the compiler that the following variable exists somewhere
// variables defined in header files cause linker errors
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern const int TILE_SIZE;

extern const int MAP[][8];

int** generate_maze(int n);
void _generate_maze(int** maze, bool* visited, int row, int col, int size, int n);

#endif

