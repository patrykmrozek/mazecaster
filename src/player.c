#include "player.h"

void init_player(Player* player, Map* map) {
  *player = (Player)
  {
    .x = map->tile_size + (map->tile_size/2),
    .y = map->tile_size + (map->tile_size/2),
    .dx = PDX_INIT,
    .dy = PDY_INIT,
    .a = deg_to_rad(0),
    .size = PLAYER_SIZE,
    COLOR_WHITE
  }; 
}  


