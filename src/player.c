#include "player.h"

void init_player(Player* player) {
  *player = (Player)
  {
    .x = WIDTH/2,
    .y = HEIGHT/2,
    .dx = PDX_INIT,
    .dy = PDY_INIT,
    .a = 0,
    .size = PLAYER_SIZE,
    COLOR_WHITE
  };
}  


