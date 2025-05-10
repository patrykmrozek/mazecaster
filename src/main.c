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
  /*
  Graph* graph = create_graph(10);
  printf("graph created\n");
  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 0, 3);
  add_edge(graph, 1, 5);
  add_edge(graph, 6, 0);
  add_edge(graph, 2, 3);
  add_edge(graph, 7, 0);
  printf("edges added\n");
  print_graph(graph);
  destroy_graph(graph);
  printf("graph destroyed\n");
  */

  /*
  Stack* stack = create_stack(10);
  push(stack, 5);
  push(stack, 7);
  int peek_v = 0;
  peek(stack, &peek_v);
  printf("%d \n", peek_v);
  destroy_stack(stack);
*/

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
    get_user_inputs(window, &player, deltaTime);
    cast_rays(renderer, &player);
    SDL_RenderPresent(renderer);

    //printf("FPS: %f\n", 1.0/deltaTime);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
