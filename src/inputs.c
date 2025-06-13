#include "inputs.h"


void input_init(input_state_t* input) {
  memset(input, 0, sizeof(input_state_t)); //initializes input_state_t so all arrays start off at 0
}

void input_process(input_state_t* input, SDL_Event* event) {
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

void input_update(input_state_t* input) { //updates only keys pressed and released arrays
  memset(input->keys_pressed, 0, sizeof(input->keys_pressed)); //reset all values in keys_pressed arr to 0
  memset(input->keys_released, 0, sizeof(input->keys_released)); //reset all values in keys_released arr to 0
}

bool is_key_down(input_state_t* input, SDL_Scancode key) {
  return input->keys_down[key];
}

bool is_key_pressed(input_state_t* input, SDL_Scancode key) {
  return input->keys_pressed[key];
}
bool is_key_released(input_state_t* input, SDL_Scancode key) {
  return input->keys_released[key];
}
