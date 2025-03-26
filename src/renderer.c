#include "renderer.h"

void draw_player(SDL_Surface* surface, Player* player) {
  SDL_Rect playerRect = {player->x, player->y, player->w, player->h};
  SDL_FillRect(surface, &playerRect, player->color);
}





