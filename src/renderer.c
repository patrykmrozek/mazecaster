#include "renderer.h"

void draw_player(SDL_Renderer* renderer, Player* player) {
  SDL_Rect playerRect = {player->x, player->y, player->w, player->h};
  SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
  SDL_RenderFillRect(renderer, &playerRect);
}

 
