#include "renderer.h"

void draw_player(SDL_Renderer* renderer, Player* player, Map* map, SDL_Rect* map_rect) {

  //normalize player c and y to (0, 1) of original maze
  float nx = player->x / (float)(map->width * map->tile_size);
  float ny = player->y / (float)(map->height * map->tile_size);

  //maps normalized position into screen coordinates, relative to map_rect
  int px = map_rect->x + (int)(nx * map_rect->w);
  int py = map_rect->y + (int)(ny * map_rect->h);
  
  //scales player size based on scaling of minimap
  float p_size = map_rect->w/map->width/2;

  //printf("Player world: %.1f, %.1f\n", player->x, player->y);
  //printf("Player minimap: %d, %d\n", px, py);

  SDL_Rect playerRect = {px-(p_size/2), py-(p_size/2), p_size, p_size};
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

void draw_map(SDL_Renderer* renderer, Map* map, int tile_draw_size) {
  int offset_x = (WIDTH/2 - (map->width*tile_draw_size)) /2;
  int offset_y = (HEIGHT - map->height*tile_draw_size) /2;
  for (int y=0; y<map->height; y++) {
    for (int x=0; x<map->width; x++) {
      // rect is going to be the block size * the block num
      SDL_Rect tile = {
        offset_x + x*tile_draw_size,
        offset_y + y*tile_draw_size,
        tile_draw_size,
        tile_draw_size
      };
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); //set color to white
        SDL_RenderFillRect(renderer, &tile);
      // if the current block is 1 (a wall), draw a white rect 
      if (map->grid[y][x]==1) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //set color to white
        SDL_RenderFillRect(renderer, &tile);
      } 
    }
  }
}


//instead of drawing map every frame, cache it to a texture and copy texture to the renderer every frame
SDL_Texture* cache_map(SDL_Renderer* renderer, Map* map) {
  
  int tile_draw_size = WIDTH / map->width;
  if (HEIGHT / map->height < tile_draw_size) {
    tile_draw_size = HEIGHT / map->height;
  }
  // Clamp to max tile size (e.g. 16)
  if (tile_draw_size > 16) {
      tile_draw_size = 16;
  }
    //draw_map(renderer, map, tile_draw_size);

  //scales map without distortion
  /*float map_aspect = (float)map->width/map->height;
  
  SDL_Rect map_rect;
  map_rect.w = WIDTH/2;
  map_rect.h = (int)(map_rect.w/map_aspect);
  map_rect.x = 0;
  map_rect.y = (HEIGHT - map_rect.h)/2;
*/

  int width = map->width * tile_draw_size;
  int height = map->height * tile_draw_size;

  SDL_Texture* map_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET,
    width,
    height
  );

  if (!map_texture) {
    printf("map texture failed\n");
    return NULL;
  }

  SDL_SetRenderTarget(renderer, map_texture); //set target to map texture
  SDL_RenderClear(renderer);
  
  for (int y = 0; y < map->height; y++) {
    for (int x = 0; x < map->width; x++) {
       SDL_Rect wall = {
          x*tile_draw_size,
          y*tile_draw_size,
          tile_draw_size,
          tile_draw_size
        };
      if (map->grid[y][x] == 1) { 
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &wall);
      }
      else if (map->grid[y][x] == 2) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &wall); 
      }
    }
  }

  SDL_SetRenderTarget(renderer, NULL); //reset rendering back to screen

  return map_texture;

}

void draw_bg(SDL_Renderer* renderer) {
  SDL_Rect floor = {
    WIDTH/2,
    HEIGHT/2,
    WIDTH/2,
    HEIGHT/2
  };

  SDL_Rect roof = {
    WIDTH/2,
    0,
    WIDTH/2,
    HEIGHT/2
  };
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
  SDL_RenderFillRect(renderer, &floor);
  SDL_SetRenderDrawColor(renderer, 150, 0, 100, 50);
  SDL_RenderFillRect(renderer, &roof);
}


void draw_3d(SDL_Renderer* renderer, int colNum, float rayDist, int pixels, float rayA, Player* player, Map* map) {
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
  float lineH = (map->tile_size*HEIGHT) / rayDist; // the further away the rayDist, the smaller the wall height will be 
  if (lineH > HEIGHT) {lineH = HEIGHT;}
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
