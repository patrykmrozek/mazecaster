#ifndef RENDERER_H
#define RENDERER_H

#include "player.h"
#include "window.h"
#include "map.h"

void draw_player(SDL_Renderer* renderer, player_t* player, Map* map, SDL_Rect* map_rect);
SDL_Texture* cache_map(SDL_Renderer* renderer, Map* map);
void draw_bg(SDL_Renderer* renderer);
void draw_3d(SDL_Renderer* renderer, int colNum, float rayDist, int pixels, float rayA, player_t* player, Map* map);

#endif 
