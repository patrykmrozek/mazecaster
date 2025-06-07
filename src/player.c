#include "player.h"

void init_player(Player* player, Map* map) {
  *player = (Player)
  {
    .x = map->tile_size + (map->tile_size/2),
    .y = map->tile_size + (map->tile_size/2),
    .dx = PDX_INIT,
    .dy = PDY_INIT,
    .a = deg_to_rad(45),
    .size = PLAYER_SIZE,
    COLOR_RED
  }; 
}

bool has_exit(Player player, Map map) {
  //player position in relation to the map matrix
  int player_row = floor(player.y / map.tile_size);
  int player_col = floor(player.x / map.tile_size);

  //if the player is on the exit cell
  if (player_row == map.exit.x && player_col == map.exit.y) {
    return true;
  }
  return false;
}

 
