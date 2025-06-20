#ifndef RENDERER_H
#define RENDERER_H

#include "player.h"
#include "window.h"
#include "map.h"
#include "types.h"

void draw_player(SDL_Renderer* renderer, player_t* player, map_t* map, SDL_Rect* map_rect);
SDL_Texture* cache_map(SDL_Renderer* renderer, map_t* map);
void draw_bg(SDL_Renderer* renderer, bool map_visible);
void draw_3d(SDL_Renderer* renderer, bool map_visible, usize colNum, f32 rayDist, u8 pixels, f32 rayA, player_t* player, map_t* map);
void draw_menu(SDL_Renderer* renderer, TTF_Font* font_main, TTF_Font* font_desc, const char* text_main, const char* text_description);

#endif 
