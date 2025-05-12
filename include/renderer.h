#ifndef RENDERER_H
#define RENDERER_H

#include "player.h"
#include "window.h"
#include "map.h"

void draw_player(SDL_Renderer* renderer, Player* player, Map* map, SDL_Rect* map_rect);
void draw_map(SDL_Renderer* renderer, Map* map, int tile_draw_size);
SDL_Texture* cache_map(SDL_Renderer* renderer, Map* map, int tile_draw_size, SDL_Rect* out_rect);
void draw_bg(SDL_Renderer* renderer);
void draw_3d(SDL_Renderer* renderer, int colNum, float rayDist, int pixels, float rayA, Player* player, Map* map);

#endif 
