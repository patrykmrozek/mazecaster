#include <stdio.h>
#include "window.h"
#include "player.h"
#include "renderer.h"
#include "inputs.h"
#include "map.h"
#include "utils.h"

int main() {
  
  SDL_Window* window = init_window();
  SDL_Renderer* renderer = get_renderer(window);
  Player player;
  init_player(&player);

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
    draw_map(renderer);
    draw_player(renderer, &player);
    //printf("X: %f, Y: %f ANGLE: %f\n", player.x, player.y, player.a);
    get_user_inputs(window, &player);
    SDL_RenderPresent(renderer);

    printf("FPS: %f\n", 1.0/deltaTime);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
