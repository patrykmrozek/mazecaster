#ifndef PLAYER_H
#define PLAYER_H

#include "window.h"
#include "utils.h"
#include "map.h"

#define PLAYER_SIZE 10
#define PDX_INIT cos(player->a)*3
#define PDY_INIT sin(player->a)*3

//define new type - color - color in rgba format
typedef struct {
  Uint8 r, g, b, a;
} Color;

#define COLOR_WHITE (Color){255, 255, 255, 255}

typedef struct {
  //x, y, deltaX, deltaY, angle, size
  double x, y, dx, dy, a, size;
  Color color;
} Player;

void init_player(Player* player, Map* map);

#endif
