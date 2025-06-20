#include "game.h"

void game_init(game_t* game) {
  game->state = STATE_MENU;
  game->window = init_window();
  game->renderer = get_renderer(game->window);
  game->map = generate_maze(5);
  game->map_rect = get_map_rect(game->map);
  game->cached_map = cache_map(game->renderer, game->map);
  init_player(&game->player, game->map);
  game->input = malloc(sizeof(input_state_t));
  input_init(game->input);
  game->font.main = load_font_main();
  game->font.desc = load_font_desc();
  game->map_visible = true;
  game->running = true;

  SDL_RaiseWindow(game->window);
  SDL_PumpEvents();
}
/*
void game_restart(game_t* game) {
  game->state = STATE_PLAYING;
  game->map = generate_maze(5);
  game->map_rect = get_map_rect(game->map);
  game->cached_map = cache_map(game->renderer, game->map);
  init_player(&game->player, game->map);
}
*/

void game_update(game_t* game, f64 delta_time) {
  state_handlers[game->state].update(game, delta_time);
}

void game_render(game_t* game) {
  state_handlers[game->state].render(game);
}

void game_destroy(game_t* game) {
  free(game->input);
  destroy_map(game->map);
  TTF_CloseFont(game->font.main);
  TTF_CloseFont(game->font.desc);
  SDL_DestroyTexture(game->cached_map);
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  
}



