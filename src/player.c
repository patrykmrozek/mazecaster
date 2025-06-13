#include "player.h"

void init_player(player_t* player, map_t* map) {
  *player = (player_t)
  {
    .pos = (vec2_t){ (map->tile_size + (map->tile_size/2)), (map->tile_size + (map->tile_size/2))},
    .dx = PDX_INIT,
    .dy = PDY_INIT,
    .a = deg_to_rad(45),
    .size = PLAYER_SIZE,
    .speed = 150.0f,
    .sens = 2.0f,
    COLOR_RED
  }; 
}



void move_left(player_t* player, double delta_time) {
  float strafe_angle = player->a - PI/2; 
  player->pos.x += cos(strafe_angle) * player->speed * delta_time;
  player->pos.y += sin(strafe_angle) * player->speed * delta_time;
}

void move_right(player_t* player, double delta_time) {
  float strafe_angle = player->a + PI/2;
  player->pos.x += cos(strafe_angle) * player->speed * delta_time;
  player->pos.y += sin(strafe_angle) * player->speed * delta_time;
}

void move_forward(player_t* player, double delta_time) {
  player->pos.x += player->dx * player->speed * delta_time;
  player->pos.y += player->dy * player->speed * delta_time;
}

void move_backward(player_t* player, double delta_time) {
  player->pos.x -= player->dx * player->speed * delta_time;
  player->pos.y -= player->dy * player->speed * delta_time;
}

void look_left(player_t* player, double delta_time) {
  player->a -= (player->sens * delta_time);
    if (player->a < 0) { // if player angle goes below zero, reset to 360(2PI)
      player->a += 2*PI;
    } 
      
    player->dx=cos(player->a);
    player->dy=sin(player->a);
}

void look_right(player_t* player, double delta_time) {
  player->a += (player->sens * delta_time);
    if (player->a > 2*PI){ // if player angle goes above 360(2PI), reset to zero 
      player->a -= 2*PI;
    }

    player->dx=cos(player->a);
    player->dy=sin(player->a);
}

void move_player(player_t* player, input_state_t* input, double delta_time) {
  if (input->keys_down[SDL_SCANCODE_W]) {
    move_forward(player, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_S]) {
    move_backward(player, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_A]) {
    move_left(player, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_D]) {
    move_right(player, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_LEFT]) {
    look_left(player, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_RIGHT]) {
    look_right(player, delta_time);
  }
}

bool has_exit(player_t player, map_t map) {
  //player position in relation to the map matrix
  int player_row = floor(player.pos.y / map.tile_size);
  int player_col = floor(player.pos.x / map.tile_size);

  //if the player is on the exit cell
  if (player_row == map.exit.x && player_col == map.exit.y) {
    return true;
  }
  return false;
}

 
