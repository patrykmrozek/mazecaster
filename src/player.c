#include "player.h"

void init_player(Player* player, Map* map) {
  *player = (Player)
  {
    .x = map->tile_size,
    .y = map->tile_size,
    .dx = PDX_INIT,
    .dy = PDY_INIT,
    .a = deg_to_rad(45),
    .size = PLAYER_SIZE,
    COLOR_WHITE
  }; 
}  


