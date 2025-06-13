#ifndef INPUTS_H
#define INPUTS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "window.h"

#define MAX_KEYS SDL_NUM_SCANCODES //sets MAX_KEYS to the max possible number of keys defined in SDL

typedef struct {
  //index in arrays correlate directly to the sdl scancodes
  bool keys_down[MAX_KEYS];
  bool keys_pressed[MAX_KEYS];
  bool keys_released[MAX_KEYS];
} input_state_t;


void input_init(input_state_t* input);
void input_process(input_state_t* input, SDL_Event* event);
void input_update(input_state_t* input);
bool is_key_down(input_state_t* input, SDL_Scancode key);
bool is_key_pressed(input_state_t* input, SDL_Scancode key);
bool is_key_released(input_state_t* input, SDL_Scancode key);

#endif
