#include "game.h"

void game_init(game_t* game) {
  game->state = STATE_PLAYING;
  game->window = init_window();
  game->renderer = get_renderer(game->window);
  game->map = generate_maze(5);
  game->map_rect = get_map_rect(game->map);
  game->cached_map = cache_map(game->renderer, game->map);
  init_player(&game->player, game->map);
  game->input = malloc(sizeof(InputState_t));
  input_init(game->input);
  game->running = true;

  SDL_RaiseWindow(game->window);
  SDL_PumpEvents();
}


void game_update(game_t* game) {
  double deltaTime = calc_delta_time();
  move_player(&game->player, game->input, deltaTime);
  if (has_exit(game->player, *game->map)) {
    game->state = STATE_GAMEOVER;
  }
}


void game_render(game_t* game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);//clear screen
    SDL_RenderCopy(game->renderer, game->cached_map, NULL, &game->map_rect);//copy map texture to renderer instead of redrawing every frame
    draw_player(game->renderer, &game->player, game->map, &game->map_rect);
    //printf("X: %f, Y: %f\n", player.x, player.y);
    //printf("ROW: %f, COL: %f\n", floor(player.y / map->tile_size), floor(player.x / map->tile_size));
    draw_bg(game->renderer);
    //printf("X: %f, Y: %f ANGLE: %f\n", player.x, player.y, player.a);
    cast_rays(game->renderer, &game->player, game->map, &game->map_rect);
    SDL_RenderPresent(game->renderer);
}


void game_destroy(game_t* game) {
  free(game->input);
  destroy_map(game->map);
  SDL_DestroyTexture(game->cached_map);
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  
}



