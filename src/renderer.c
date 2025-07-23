#include "renderer.h"

void draw_player(SDL_Renderer* renderer, player_t* player, map_t* map, SDL_Rect* map_rect) {

  //normalize player c and y to (0, 1) of original maze
  f32 nx = player->pos.x / (float)(map->width * map->tile_size);
  f32 ny = player->pos.y / (float)(map->height * map->tile_size);

  //maps normalized position into screen coordinates, relative to map_rect
  u16 px = map_rect->x + (int)(nx * map_rect->w);
  u16 py = map_rect->y + (int)(ny * map_rect->h);
  
  //scales player size based on scaling of minimap
  f32 p_size = map_rect->w/map->width/2;

  //printf("player_t world: %.1f, %.1f\n", player->pos.x, player->pos.y);
  //printf("player_t minimap: %d, %d\n", px, py);

  SDL_Rect playerRect = {px-(p_size/2), py-(p_size/2), p_size, p_size};
  SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
  SDL_RenderFillRect(renderer, &playerRect);

  /*
  //draw a line in the direction the player is facing
  float lineLength = 20.0f;
  //calulate the point in which the player is facing with length lineLength
  double endX = player->pos.x + (player->size/2) + cos(player->a) * lineLength;
  double endY = player->pos.y + (player->size/2) + sin(player->a) * lineLength;
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
  SDL_RenderDrawLine(
    renderer,
    player->pos.x+(player->size/2),
    player->pos.y+(player->size/2),
    endX,
    endY
  );
  */

}

//instead of drawing map every frame, cache it to a texture and copy texture to the renderer every frame
SDL_Texture* cache_map(SDL_Renderer* renderer, map_t* map) {
  
  u8 tile_draw_size = WIDTH / map->width;
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

  u8 width = map->width * tile_draw_size;
  u8 height = map->height * tile_draw_size;

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

void draw_bg(SDL_Renderer* renderer, bool map_visible) {
  
  int draw_offset_left = (map_visible) ? (WIDTH/2) : 0;
  int draw_offset_right = (map_visible) ? (WIDTH/2) : WIDTH;
  
  SDL_Rect floor = {
    draw_offset_left,
    HEIGHT/2,
    draw_offset_right,
    HEIGHT/2
  };

  SDL_Rect roof = {
    draw_offset_left,
    0,
    draw_offset_right,
    HEIGHT/2
  };
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
  SDL_RenderFillRect(renderer, &floor);
  SDL_SetRenderDrawColor(renderer, 150, 0, 100, 50);
  SDL_RenderFillRect(renderer, &roof);
}


void draw_3d(SDL_Renderer* renderer, bool map_visible, usize colNum, f32 rayDist, u8 pixels, f32 rayA, player_t* player, map_t* map) {
  /* 
  colNum - represents the current ray ('ray' value from for loop in cast_rays)
  rayDist - the shortest distance betweem distV and distH (the ray that will be rendered)
  pixels - how many pixels from left to right each ray will draw
  */ 
  f32 angleDiff = player->a - rayA; // diff between player angle and ray angle
  //the rays that are out furthest from the player angle are going to have a greater distance
  //making them smaller (causing the fisheye effect)
  //normalize angleDiff
  if (angleDiff < 0) {angleDiff += PI*2;}
  if (angleDiff > PI*2) {angleDiff -= PI*2;}
  //fixes fisheye effect by making all rays of equal distance
  rayDist = rayDist * cos(angleDiff);
  f32 lineH = (map->tile_size*HEIGHT) / rayDist; // the further away the rayDist, the smaller the wall height will be 
  if (lineH > HEIGHT) {lineH = HEIGHT;}
  f32 lineO = (HEIGHT/2) - lineH/2; //line offset, so that render is centered vertically on the screen 
  
  int draw_offset = (map_visible) ? (WIDTH/2) : 0;

  for (int i=0; i<pixels; i++) {
    SDL_RenderDrawLine(
      renderer,
      (colNum*pixels) + draw_offset + i, // offsets the scene to the right of the incrememnted
      lineO,
      (colNum*pixels) + draw_offset + i,
      lineH + lineO
    );
    }  
}

void draw_menu(SDL_Renderer* renderer, TTF_Font* font_main, TTF_Font* font_desc, const char* text_main, const char* text_description) {

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50); //black with lowered opacity to dim the screen
  SDL_Rect screen_rect = {0, 0, WIDTH, HEIGHT};
  SDL_RenderFillRect(renderer, &screen_rect);


  //const char text[] = "MENU";
  SDL_Color text_color = {255, 255, 255, 255};

  if (!font_main) {
        printf("font_main failed\n");
    }
  
  SDL_Surface* text_main_surface = TTF_RenderText_Solid(font_main, text_main, text_color);
  if (!text_main_surface) {
    printf("TEXT MAIN SURFACE FAILED: %s\n", SDL_GetError());
    return;
  }
  SDL_Texture* text_main_texture = SDL_CreateTextureFromSurface(renderer, text_main_surface);
  if (!text_main_texture) {
    printf("TEXT MAIN TEXTURE FAILED\n");
    SDL_FreeSurface(text_main_surface);
    return;
  }

  //SDL_Surface* text_description_surface = TTF_RenderText_Solid(font, text_description, text_color);
  int wrap_width = WIDTH - (WIDTH/10); //margin for text wrapping
  SDL_Surface* text_description_surface = TTF_RenderText_Blended_Wrapped(font_desc, text_description, text_color, wrap_width);
  if (!text_description_surface) {
    printf("TEXT DESCRIPTION FAILED\n");
    SDL_FreeSurface(text_main_surface);
    SDL_DestroyTexture(text_main_texture);
    return;
  }
  SDL_Texture* text_description_texture = SDL_CreateTextureFromSurface(renderer, text_description_surface);
  if (!text_description_texture) {
    printf("TEXT DESCRIPTION TEXTURE FAILED\n");
    SDL_FreeSurface(text_main_surface);
    SDL_DestroyTexture(text_main_texture);
    SDL_FreeSurface(text_description_surface);
    return;
  }


  //centering main text
  SDL_Rect text_main_rect = {
    (WIDTH - text_main_surface->w) / 2,
    (HEIGHT - text_main_surface->h) / 2-20,
    text_main_surface->w,
    text_main_surface->h
  };

  SDL_Rect text_description_rect = {
    (WIDTH - text_description_surface->w) / 2,
    text_main_rect.y + text_main_rect.h + (HEIGHT/10),
    text_description_surface->w,
    text_description_surface->h
  };
  
  SDL_FreeSurface(text_main_surface);
  SDL_FreeSurface(text_description_surface); 

  SDL_RenderCopy(renderer, text_main_texture, NULL, &text_main_rect); //render main texture 
  SDL_RenderCopy(renderer, text_description_texture, NULL, &text_description_rect); //render texture
  SDL_RenderPresent(renderer); //show tecture on the screen 
  
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
  SDL_DestroyTexture(text_main_texture); 
  SDL_DestroyTexture(text_description_texture);
}


