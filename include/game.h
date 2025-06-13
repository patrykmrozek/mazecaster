#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "window.h"
#include "player.h"
#include "renderer.h"
#include "raycaster.h"
#include "inputs.h"
#include "map.h"
#include "utils.h"


typedef enum {
  STATE_MENU,
  STATE_PLAYING,
  STATE_PAUSED,
  STATE_GAMEOVER,
  STATE_COUNT //since count is the last item in the enum it will correctly index states
} gameState_t;


typedef struct game {
  gameState_t state;
  SDL_Window* window;
  SDL_Renderer* renderer;
  Map* map;
  player_t player;
  SDL_Texture* cached_map;
  SDL_Rect map_rect;
  InputState_t* input;
  bool running;
} game_t;


//define function pointer types, these will allow for dynamically calling update and render functions depending on current gameState
typedef void (*gameUpdateFunc)(game_t*, double);
typedef void (*gameRenderFunc)(game_t*);


//state handler struct 
typedef struct {
  gameUpdateFunc update;
  gameRenderFunc render;
} gameStateHandler_t;


//telling the compiler that stateHandlers exists somewhere
extern gameStateHandler_t stateHandlers[STATE_COUNT];

// functions for each state along with an init and destroy
// initialize game 
void game_init(game_t* game);
//STATE_MENU functions
void game_update_menu(game_t* game, double deltaTime);
void game_render_menu(game_t* game);
//STATE_PLAYING functions
void game_update_playing(game_t* game, double deltaTime);
void game_render_playing(game_t* game);
//STATE_PAUSED functions
void game_update_paused(game_t* game, double deltaTime);
void game_render_paused(game_t* game);
//STATE_GAMEOVER functions
void game_update_gameover(game_t* game, double deltaTime);
void game_render_gameover(game_t* game);
//destroy game
void game_destroy(game_t* game);


#endif
