#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "window.h"
#include "player.h"
#include "renderer.h"
#include "raycaster.h"
#include "inputs.h"
#include "map.h"
#include "utils.h"
#include "graph.h"
#include "game.h"

int main() {
  //seeds random generator with current time, avoids deterministic maze generation
  srand(time(NULL));

  SDL_Window* window = init_window();
  SDL_Renderer* renderer = get_renderer(window);
  Player player;
  Map* map = generate_maze(5);
  init_player(&player, map);
  SDL_RaiseWindow(window); //needed for the window to appear above all other windows
  SDL_PumpEvents();
   
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
  float map_aspect = (float)map->width/map->height;
  
  SDL_Rect map_rect;
  map_rect.w = WIDTH/2;
  map_rect.h = (int)(map_rect.w/map_aspect);
  map_rect.x = 0;
  map_rect.y = (HEIGHT - map_rect.h)/2;

  SDL_Texture* cached_map = cache_map(renderer, map, tile_draw_size, NULL);

  SDL_Event event;
  int program_running = 1;

  
  while (program_running /* && !(has_exit(player, *map)) */ ) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        program_running = 0;
      }  
    }
    double deltaTime = calc_delta_time();
    has_exit(player, *map);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);//clear screen
    SDL_RenderCopy(renderer, cached_map, NULL, &map_rect);//copy map texture to renderer instead of redrawing every frame
    draw_player(renderer, &player, map, &map_rect);
    //printf("X: %f, Y: %f\n", player.x, player.y);
    //printf("ROW: %f, COL: %f\n", floor(player.y / map->tile_size), floor(player.x / map->tile_size));
    draw_bg(renderer);
    //printf("X: %f, Y: %f ANGLE: %f\n", player.x, player.y, player.a);
    get_user_inputs(window, &player, deltaTime);
    cast_rays(renderer, &player, map, &map_rect);
    SDL_RenderPresent(renderer);

    //printf("FPS: %f\n", 1.0/deltaTime);
  }
  destroy_map(map);
  SDL_DestroyTexture(cached_map);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
