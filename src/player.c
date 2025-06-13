#include "player.h"

void init_player(player_t* player, map_t* map) {
  *player = (player_t)
  {
    .x = map->tile_size + (map->tile_size/2),
    .y = map->tile_size + (map->tile_size/2),
    .dx = PDX_INIT,
    .dy = PDY_INIT,
    .a = deg_to_rad(45),
    .size = PLAYER_SIZE,
    .speed = 150.0f,
    .sens = 2.0f,
    COLOR_RED
  }; 
}



void move_left(player_t* player, double delta) {
  float strafe_angle = player->a - PI/2; 
  player->x += cos(strafe_angle) * player->speed * delta;
  player->y += sin(strafe_angle) * player->speed * delta;
}

void move_right(player_t* player, double delta) {
  float strafe_angle = player->a + PI/2;
  player->x += cos(strafe_angle) * player->speed * delta;
  player->y += sin(strafe_angle) * player->speed * delta;
}

void move_forward(player_t* player, double delta) {
  player->x += player->dx * player->speed * delta;
  player->y += player->dy * player->speed * delta;
}

void move_backward(player_t* player, double delta) {
  player->x -= player->dx * player->speed * delta;
  player->y -= player->dy * player->speed * delta;
}

void look_left(player_t* player, double delta) {
  player->a -= (player->sens * delta);
    if (player->a < 0) { // if player angle goes below zero, reset to 360(2PI)
      player->a += 2*PI;
    } 
      
    player->dx=cos(player->a);
    player->dy=sin(player->a);
}

void look_right(player_t* player, double delta) {
  player->a += (player->sens * delta);
    if (player->a > 2*PI){ // if player angle goes above 360(2PI), reset to zero 
      player->a -= 2*PI;
    }

    player->dx=cos(player->a);
    player->dy=sin(player->a);
}

void move_player(player_t* player, input_state_t* input, double delta) {
  if (input->keys_down[SDL_SCANCODE_W]) {
    move_forward(player, delta);
  }
  if (input->keys_down[SDL_SCANCODE_S]) {
    move_backward(player, delta);
  }
  if (input->keys_down[SDL_SCANCODE_A]) {
    move_left(player, delta);
  }
  if (input->keys_down[SDL_SCANCODE_D]) {
    move_right(player, delta);
  }
  if (input->keys_down[SDL_SCANCODE_LEFT]) {
    look_left(player, delta);
  }
  if (input->keys_down[SDL_SCANCODE_RIGHT]) {
    look_right(player, delta);
  }
}

bool has_exit(player_t player, map_t map) {
  //player position in relation to the map matrix
  int player_row = floor(player.y / map.tile_size);
  int player_col = floor(player.x / map.tile_size);

  //if the player is on the exit cell
  if (player_row == map.exit.x && player_col == map.exit.y) {
    return true;
  }
  return false;
}

 
