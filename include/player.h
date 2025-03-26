#ifndef PLAYER_H
#define PLAYER_H

#include "window.h"

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 20
#define COLOR_WHITE 0xffffffff


typedef struct {
  double x, y, w, h;
  Uint32 color;
} Player;

void init_player(Player* player);
#endif
