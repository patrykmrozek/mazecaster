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
    double delta_time = calc_delta_time();

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        game.running = false;
      }
      input_process(game.input, &event); //while there is an event, process it
      //printf("%d\n", game.input->keys_pressed[SDL_SCANCODE_P]);
    }
    game_update(&game, delta_time);
    game_render(&game);

    //input_update clears keys that have been pressed for one frame, so it must be called after the game functions
    input_update(game.input);
   // printf("FPS: %f\n", 1.0/delta_time);
  }

  game_destroy(&game);
  return 0;
}
