#ifndef RENDERER_H
#define RENDERER_H

#include "player.h"
#include "window.h"

void draw_player(SDL_Renderer* renderer, Player* player);
void draw_map(SDL_Renderer* renderer);

#endif 
