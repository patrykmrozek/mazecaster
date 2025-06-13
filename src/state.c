#include "state.h"
#include "game.h"

//state handler table
//struct of function pointers that maps states to functions (avoids having to use if else or switch statements)
game_state_handler_t state_handlers[STATE_COUNT] = {
  [STATE_MENU] = {game_update_menu, game_render_menu},
  [STATE_PLAYING] = {game_update_playing, game_render_playing},
  [STATE_PAUSED] = {game_update_paused, game_render_paused},
  [STATE_GAMEOVER] = {game_update_gameover, game_render_gameover}
};


void game_update_menu(game_t* game, f64 deltaTime) {

}
void game_render_menu(game_t* game) {

}


void game_update_playing(game_t* game, f64 deltaTime) {
  move_player(&game->player, game->input, deltaTime);
  if (has_exit(game->player, *game->map)) {
    game->state = STATE_GAMEOVER;
  }
}

void game_render_playing(game_t* game) {
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

void game_update_paused(game_t* game, f64 deltaTime) {

}
void game_render_paused(game_t* game) {

}

void game_update_gameover(game_t* game, f64 deltaTime) {
  printf("GAMEOVER\n");
}
void game_render_gameover(game_t* game) {

}


