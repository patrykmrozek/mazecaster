#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "state.h"
#include "window.h"
#include "player.h"
#include "inputs.h"
#include "map.h"
#include "utils.h"

typedef struct font {
  TTF_Font* main;
  TTF_Font* desc;
} font_t;


typedef struct game {
  game_state_t state;
  SDL_Window* window;
  SDL_Renderer* renderer;
  map_t* map;
  player_t player;
  SDL_Texture* cached_map;
  SDL_Rect map_rect;
  input_state_t* input;
  font_t font;
  bool map_visible;
  bool running;
} game_t;


// functions for each state along with an init and destroy
void game_init(game_t* game);
//void game_restart(game_t* game);
void game_update(game_t* game, f64 delta_time);
void game_render(game_t* game);
void game_destroy(game_t* game);


#endif
