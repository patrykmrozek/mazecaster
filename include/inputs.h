#ifndef INPUTS_H
#define INPUTS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "window.h"

#define MAX_KEYS SDL_NUM_SCANCODES //sets MAX_KEYS to the max possible number of keys defined in SDL

typedef struct {
  bool keys_down[MAX_KEYS];
  bool keys_pressed[MAX_KEYS];
  bool keys_released[MAX_KEYS];
} InputState_t;


//void get_user_inputs(SDL_Window* window, Player* player, double deltaT);

void input_init(InputState_t* input);
void input_process(InputState_t* input, SDL_Event* event);
void input_update(InputState_t* input);
bool is_key_down(InputState_t* input, SDL_Scancode key);
bool is_key_pressed(InputState_t* input, SDL_Scancode key);
bool is_key_released(InputState_t* input, SDL_Scancode key);

#endif
