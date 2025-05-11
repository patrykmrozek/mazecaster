#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "window.h"
#include "player.h"
#include "renderer.h"
#include "raycaster.h"
#include "inputs.h"
#include "map.h"
#include "utils.h"
#include "graph.h"

int main() {

  SDL_Window* window = init_window();
  SDL_Renderer* renderer = get_renderer(window);
  Player player;
  Map* map = generate_maze(10);
  init_player(&player, map);
  SDL_RaiseWindow(window); //needed for the window to appear above all other windows
  SDL_PumpEvents();

  SDL_Event event;
  int program_running = 1;
  
  while (program_running) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        program_running = 0;
      }  
    }
    double deltaTime = calc_delta_time();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);//clear screen
    
  int tile_draw_size = WIDTH / map->width;
  if (HEIGHT / map->height < tile_draw_size) {
    tile_draw_size = HEIGHT / map->height;
  }
  // Clamp to max tile size (e.g. 16)
  if (tile_draw_size > 16) {
      tile_draw_size = 16;
  }
    draw_map(renderer, map, tile_draw_size);
    draw_player(renderer, &player, map, tile_draw_size);
    //printf("X: %f, Y: %f ANGLE: %f\n", player.x, player.y, player.a);
    get_user_inputs(window, &player, deltaTime);
    cast_rays(renderer, &player, map);
    SDL_RenderPresent(renderer);

    //printf("FPS: %f\n", 1.0/deltaTime);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
