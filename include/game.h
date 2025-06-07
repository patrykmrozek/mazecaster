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

void init(SDL_Window* window, SDL_Renderer* renderer, Player player, Map* map);
void update(SDL_Renderer* renderer, Player* player, Map* map);
void render(SDL_Renderer* renderer, Player* player, Map* map);
void destroy(SDL_Renderer* renderer, SDL_Window* window, Map* map);



#endif
