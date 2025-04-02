#ifndef RENDERER_H
#define RENDERER_H

#include "player.h"
#include "window.h"

void draw_player(SDL_Renderer* renderer, Player* player);
void draw_map(SDL_Renderer* renderer);
void draw_3d(SDL_Renderer* renderer, int colNum, float rayDist, int pixels, float rayA, Player* player);

#endif 
