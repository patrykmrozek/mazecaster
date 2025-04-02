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


void draw_3d(SDL_Renderer* renderer, int colNum, float rayDist, int pixels, float rayA, Player* player) {
  /* 
  colNum - represents the current ray ('ray' value from for loop in cast_rays)
  rayDist - the shortest distance betweem distV and distH (the ray that will be rendered)
  pixels - how many pixels from left to right each ray will draw
  */
  float angleDiff = player->a - rayA; // diff between player angle and ray angle
  //the rays that are out furthest from the player angle are going to have a greater distance
  //making them smaller (causing the fisheye effect)
  //normalize angleDiff
  if (angleDiff < 0) {angleDiff += PI*2;}
  if (angleDiff > PI*2) {angleDiff -= PI*2;}
  //fixes fisheye effect by making all rays of equal distance
  rayDist = rayDist * cos(angleDiff);
  float lineH = (TILE_SIZE*(5*HEIGHT)/6) / rayDist; // the further away the rayDist, the smaller the wall height will be 
  if (lineH > (5*HEIGHT)/6) {lineH = (5*HEIGHT)/6;}
  float lineO = (HEIGHT/2) - lineH/2; //line offset, so that render is centered vertically on the screen 

  for (int i=0; i<pixels; i++) {
    SDL_RenderDrawLine(
      renderer,
      (colNum*pixels) + (WIDTH/2) + i, // offsets the scene to the right of the incrememnted
      lineO,
      (colNum*pixels) + (WIDTH/2) + i,
      lineH + lineO
    );
  }
  
}
