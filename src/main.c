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
  game_t game; 
  SDL_Event event;
  init(&game);

  while (game.running /* && !(has_exit(player, *map)) */ ) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        game.running = false;
      }  
    }

    update(&game);
    render(&game);
    //printf("FPS: %f\n", 1.0/deltaTime);
  }

  destroy(&game);
  return 0;
}
