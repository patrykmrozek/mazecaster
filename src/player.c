#include "player.h"

void init_player(Player* player) {
  *player = (Player)
  {
    WIDTH/2,
    HEIGHT/2,
    PLAYER_WIDTH,
    PLAYER_HEIGHT,
    COLOR_WHITE
  };
}  
