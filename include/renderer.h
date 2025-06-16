#ifndef RENDERER_H
#define RENDERER_H

#include "player.h"
#include "window.h"
#include "map.h"
#include "types.h"

void draw_player(SDL_Renderer* renderer, player_t* player, map_t* map, SDL_Rect* map_rect);
SDL_Texture* cache_map(SDL_Renderer* renderer, map_t* map);
void draw_bg(SDL_Renderer* renderer);
void draw_3d(SDL_Renderer* renderer, usize colNum, f32 rayDist, u8 pixels, f32 rayA, player_t* player, map_t* map);
void draw_menu(SDL_Renderer* renderer, TTF_Font* font, const char* text);

#endif 
