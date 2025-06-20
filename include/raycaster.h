#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "player.h"
#include "window.h"
#include "map.h"
#include "renderer.h"
#include "utils.h"
#include "types.h"

void cast_rays(SDL_Renderer* renderer, bool map_visible, player_t* player, map_t* map, SDL_Rect* map_rect);

#endif

