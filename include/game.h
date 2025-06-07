#ifndef GAME_H
#define GAME_H

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


typedef enum gameState{
  STATE_MENU,
  STATE_PLAYING,
  STATE_PAUSED,
  STATE_GAMEOVER
} gameState_t;

typedef struct game {
  gameState_t state;
  SDL_Window* window;
  SDL_Renderer* renderer;
  Map* map;
  Player player;
  SDL_Texture* cached_map;
  bool running;
} game_t;

void init(game_t* game);
void update(game_t* game);
void render(game_t* game);
void destroy(game_t* game);



#endif
