#include <stdio.h>
#include "window.h"
#include "player.h"
#include "renderer.h"

int main() {
  
  SDL_Window* window = init_window();
  SDL_Surface* surface = get_surface(window);

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

    draw_player(surface, &player);
    SDL_UpdateWindowSurface(window);
  }
  return 0;
  SDL_Quit();
  SDL_DestroyWindowSurface(window);
}
