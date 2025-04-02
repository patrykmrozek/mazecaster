#include "renderer.h"
#include "map.h"

void draw_player(SDL_Renderer* renderer, Player* player) {
  SDL_Rect playerRect = {player->x, player->y, player->size, player->size};
  SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
  SDL_RenderFillRect(renderer, &playerRect);

  /*
  //draw a line in the direction the player is facing
  float lineLength = 20.0f;
  //calulate the point in which the player is facing with length lineLength
  double endX = player->x + (player->size/2) + cos(player->a) * lineLength;
  double endY = player->y + (player->size/2) + sin(player->a) * lineLength;
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
  SDL_RenderDrawLine(
    renderer,
    player->x+(player->size/2),
    player->y+(player->size/2),
    endX,
    endY
  );
  */

}

void draw_map(SDL_Renderer* renderer) {
  for (int y=0; y<MAP_HEIGHT; y++) {
    for (int x=0; x<MAP_WIDTH; x++) {
      // rect is going to be the block size * the block num
      SDL_Rect wall = {x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE};
      // if the current block is 1 (a wall), draw a white rect 
      if (MAP[y][x]==1) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //set color to white
        SDL_RenderFillRect(renderer, &wall);
      }
    }
  }
}
