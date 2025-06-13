#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "player.h"
#include "window.h"
#include "map.h"
#include "renderer.h"
#include "utils.h"

void cast_rays(SDL_Renderer* renderer, player_t* player, Map* map, SDL_Rect* map_rect);

#endif

