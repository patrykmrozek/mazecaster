#include "inputs.h"

void get_user_inputs(SDL_Window* window, Player* player) {
  const Uint8* keystate = SDL_GetKeyboardState(NULL);
  float speed = 2.0f; // movement speed
  float turnSpeed = 0.05f;
  //
  if (keystate[SDL_SCANCODE_W]) {
    player->x += player->dx;
    player->y += player->dy;
  };

  if (keystate[SDL_SCANCODE_S]) {
    player->x -= player->dx;
    player->y -= player->dy;
  }

  
  if (keystate[SDL_SCANCODE_A]) { //players going to move at a 90 deg angle to the left (-90)
    float strafe_angle = player->a - PI/2; 
    player->x += cos(strafe_angle)*speed;
    player->y += sin(strafe_angle)*speed;
  }

  if (keystate[SDL_SCANCODE_D]) { // 90 deg to the right +90
    float strafe_angle = player->a + PI/2;
    player->x += cos(strafe_angle)*speed;
    player->y += sin(strafe_angle)*speed;
  }

  if (keystate[SDL_SCANCODE_LEFT]) {
    player->a-=turnSpeed;
    if (player->a < 0) { // if player angle goes below zero, reset to 360(2PI)
      player->a += 2*PI;
    } 
      
    player->dx=cos(player->a)*speed;
    player->dy=sin(player->a)*speed;
  }

  if (keystate[SDL_SCANCODE_RIGHT]) {
    player->a+=turnSpeed;
    if (player->a > 2*PI){ // if player angle goes above 360(2PI), reset to zero 
      player->a -= 2*PI;
    }

    player->dx=cos(player->a)*speed;
    player->dy=sin(player->a)*speed;
  }
  
}
