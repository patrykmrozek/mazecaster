#include "inputs.h"


void input_init(InputState_t* input) {
  memset(input, 0, sizeof(InputState_t)); //initializes InputState_t so all arrays start off at 0
}

void input_process(InputState_t* input, SDL_Event* event) {
  if (event->type == SDL_KEYDOWN && !(event->key.repeat)) { //if a key has been pressed (not repeated)
    SDL_Scancode key = event->key.keysym.scancode; //key = scancode of the key pressed
    input->keys_down[key] = true; //set the scancode in the key_down array to true
    input->keys_pressed[key] = true; //set the scancode in th ekeys_pressed array to true
  } else if (event->type == SDL_KEYUP) {
    SDL_Scancode key = event->key.keysym.scancode;
    input->keys_down[key] = false;
    input->keys_released[key] = true;
  }
}

void input_update(InputState_t* input) { //updates only keys pressed and released arrays
  memset(input->keys_pressed, 0, sizeof(input->keys_pressed)); //reset all values in keys_pressed arr to 0
  memset(input->keys_released, 0, sizeof(input->keys_released)); //reset all values in keys_released arr to 0
}

bool is_key_down(InputState_t* input, SDL_Scancode key) {
  return input->keys_down[key];
}

bool is_key_pressed(InputState_t* input, SDL_Scancode key) {
  return input->keys_pressed[key];
}
bool is_key_released(InputState_t* input, SDL_Scancode key) {
  return input->keys_released[key];
}


/*
void get_user_inputs(SDL_Window* window, Player* player, double deltaT) {
  const Uint8* keystate = SDL_GetKeyboardState(NULL);
  float speed = 150.0f * deltaT; // movement speed
  float turnSpeed = 2.0f * deltaT;

  //
  if (keystate[SDL_SCANCODE_W]) {
    player->x += player->dx * speed;
    player->y += player->dy * speed;
  };

  if (keystate[SDL_SCANCODE_S]) {
    player->x -= player->dx * speed;
    player->y -= player->dy * speed;
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
      
    player->dx=cos(player->a);
    player->dy=sin(player->a);
  }

  if (keystate[SDL_SCANCODE_RIGHT]) {
    player->a+=turnSpeed;
    if (player->a > 2*PI){ // if player angle goes above 360(2PI), reset to zero 
      player->a -= 2*PI;
    }

    player->dx=cos(player->a);
    player->dy=sin(player->a);
  }
  
}
*/
