#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "inputs.h"
#include "game.h"

int main() {
  srand(time(NULL));

  game_t game; 
  SDL_Event event;

  game_init(&game);

  while (game.running) {
    double deltaTime = calc_delta_time();

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        game.running = false;
      }
      input_process(game.input, &event); //while there is an event, process it
    }
    input_update(game.input);
    game_update(&game, deltaTime);
    game_render(&game);
   // printf("FPS: %f\n", 1.0/deltaTime);
  }

  game_destroy(&game);
  return 0;
}
