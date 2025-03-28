#ifndef MAP_H
#define MAP_H

#include "renderer.h"
#include "window.h"

// extern pretty much tells the compiler that the following variable exists somewhere
// variables defined in header files cause linker errors
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern const int TILE_SIZE;

extern const int MAP[][8];


#endif

