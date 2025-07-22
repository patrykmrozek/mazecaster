#include "player.h"

void init_player(player_t* player, map_t* map) {
  *player = (player_t)
  {
    .pos = (vec2_t){ (map->tile_size + (map->tile_size/2)), (map->tile_size + (map->tile_size/2))},
    .dx = PDX_INIT,
    .dy = PDY_INIT,
    .a = deg_to_rad(45),
    .size = PLAYER_SIZE,
    .speed = PLAYER_SPEED_WALK,
    .sens = 2.0f,
    .is_sprinting = false,
    .color = COLOR_RED
  }; 
}



bool hit_wall(vec2_t* pos, map_t* map) {
  int row = floor(pos->y / map->tile_size);
  int col = floor(pos->x / map->tile_size);

  if (map->grid[row][col] == 1) {
    //printf("HIT WALL\n");
    return true;
  }
  return false;
}


void move_left(player_t* player, map_t* map, double delta_time) {
  float strafe_angle = player->a - PI/2; 
  vec2_t new_pos = {
    player->pos.x + cos(strafe_angle) * player->speed * delta_time,
    player->pos.y + sin(strafe_angle) * player->speed * delta_time
  };
 
  //simluates player x movement
  vec2_t new_pos_x = {new_pos.x, player->pos.y};
  //simulates player y movement
  vec2_t new_pos_y = {player->pos.x,  new_pos.y};
   
  //if the x movement doesnt hits a wall, update x
  if (!hit_wall(&new_pos_x, map)) {
    player->pos.x = new_pos_x.x;
  }
  //if the y movement doesnt hits a wall, update y
  if (!hit_wall(&new_pos_y, map)) {
    player->pos.y = new_pos_y.y;
  }
}

void move_right(player_t* player, map_t* map, double delta_time) {
  float strafe_angle = player->a + PI/2;
  vec2_t new_pos = {
    player->pos.x + cos(strafe_angle) * player->speed * delta_time,
    player->pos.y + sin(strafe_angle) * player->speed * delta_time
  };
    
  vec2_t new_pos_x = {new_pos.x, player->pos.y};
  vec2_t new_pos_y = {player->pos.x,  new_pos.y};
  
  if (!hit_wall(&new_pos_x, map)) {
    player->pos.x = new_pos_x.x;
  }
  if (!hit_wall(&new_pos_y, map)) {
    player->pos.y = new_pos_y.y;
  }
}

void move_forward(player_t* player, map_t* map, double delta_time) {

  vec2_t new_pos = {
    player->pos.x + player->dx * player->speed * delta_time,
    player->pos.y + player->dy * player->speed * delta_time
  };

  //isonaltes new x and y positions
  vec2_t new_pos_x = {new_pos.x, player->pos.y};
  vec2_t new_pos_y = {player->pos.x,  new_pos.y};
  
  
  if (!hit_wall(&new_pos_x, map)) {
    player->pos.x = new_pos_x.x;
  }
  if (!hit_wall(&new_pos_y, map)) {
    player->pos.y = new_pos_y.y;
  }
}

void move_backward(player_t* player, map_t* map, double delta_time) {
  vec2_t new_pos = {
    player->pos.x - player->dx * player->speed * delta_time,
    player->pos.y - player->dy * player->speed * delta_time
  };

  vec2_t new_pos_x = {new_pos.x, player->pos.y};
  vec2_t new_pos_y = {player->pos.x,  new_pos.y};
  
  
  if (!hit_wall(&new_pos_x, map)) {
    player->pos.x = new_pos_x.x;
  }
  if (!hit_wall(&new_pos_y, map)) {
    player->pos.y = new_pos_y.y;
  }
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


void move_player(player_t* player, map_t* map, input_state_t* input, double delta_time) {
  if (input->keys_down[SDL_SCANCODE_W]) {
    move_forward(player, map, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_S]) {
    move_backward(player, map, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_A]) {
    move_left(player, map, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_D]) {
    move_right(player, map, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_LEFT]) {
    look_left(player, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_RIGHT]) {
    look_right(player, delta_time);
  }
  if (input->keys_down[SDL_SCANCODE_LSHIFT] && !player->is_sprinting) {
    player->is_sprinting = true;
    player->speed = PLAYER_SPEED_SPRINT;
  } else if (input->keys_released[SDL_SCANCODE_LSHIFT] && player->is_sprinting) {
    player->is_sprinting = false;
    player->speed = PLAYER_SPEED_WALK;
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

 
