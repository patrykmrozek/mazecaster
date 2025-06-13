#ifndef PLAYER_H
#define PLAYER_H

#include "window.h"
#include "inputs.h"
#include "utils.h"
#include "map.h"
#include "types.h"

#define PLAYER_SIZE 10
#define PDX_INIT cos(player->a)*3
#define PDY_INIT sin(player->a)*3



//define new type - color - color in rgba format
typedef struct {
  Uint8 r, g, b, a;
} Color;

#define COLOR_WHITE (Color){255, 255, 255, 255}
#define COLOR_RED (Color){255, 0, 0, 255}

typedef struct {
  //vec2_t pos;
  f32 x, y;
  f64 dx, dy, a, size;
  f32 speed, sens;
  Color color;
} Player;

void init_player(Player* player, Map* map);
void move_left(Player* player, double delta);
void move_right(Player* player, double delta);
void move_forward(Player* player, double delta);
void move_backward(Player* player, double delta);
void look_left(Player* player, double delta);
void look_right(Player* player, double delta);
void move_player(Player* player, InputState_t* input, double delta);
bool has_exit(Player player, Map map);


#endif
