#ifndef PLAYER_H
#define PLAYER_H

#include "window.h"

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 20

//define new type - color - color in rgba format
typedef struct {
  Uint8 r, g, b, a;
} Color;

#define COLOR_WHITE (Color){255, 255, 255, 255}

typedef struct {
  double x, y, w, h;
  Color color;
} Player;

void init_player(Player* player);
#endif
