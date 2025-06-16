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
 

void game_update_menu(game_t* game, f64 delta_time) {
  if (is_key_pressed(game->input, SDL_SCANCODE_RETURN)) {
    printf("\t[[PLAYING]]\nPRESS [P] TO PAUSE\nPRESS [Q] OR [ESC] TO EXIT TO MENU\n\n");
    game->state = STATE_PLAYING;
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_Q) || is_key_pressed(game->input, SDL_SCANCODE_ESCAPE)) {
    printf("\tEXITING GAME\n");
    game->running = 0;
  }
}
void game_render_menu(game_t* game) {
  const char menu_text[] = "MENU";
  draw_menu(game->renderer, game->font, menu_text);
}


void game_update_playing(game_t* game, f64 delta_time) {
  move_player(&game->player, game->input, delta_time);
  if (has_exit(game->player, *game->map)) {
    printf("\t[[GAMEOVER]]\nPRESS [ENTER] OR [R] TO RESTART\nPRESS [Q] OR [ESC] TO EXIT TO MENU\n\n");
    game->state = STATE_GAMEOVER;
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_P)) {
    printf("\t[[PAUSED]]\nPRESS [P] OR [ENTER] TO UNPAUSE\nPRESS[R] TO RESTART\nPRESS [Q] OR [ESC] TO EXIT TO MENU\n\n");
    game->state = STATE_PAUSED;
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_Q) || is_key_pressed(game->input, SDL_SCANCODE_ESCAPE)) {
    printf("\t[[MENU]]\nPRESS [ENTER] TO PLAY\nPRESS [Q] OR [ESC] TO EXIT THE GAME\n\n");
    game_init(game);
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

void game_update_paused(game_t* game, f64 delta_time) {
  if (is_key_pressed(game->input, SDL_SCANCODE_P) || is_key_pressed(game->input, SDL_SCANCODE_RETURN)) {
    printf("\t[[PLAYING]]\nPRESS [P] TO PAUSE\nPRESS [Q] OR [ESC] TO EXIT TO MENU\n\n"); 
    game->state = STATE_PLAYING;
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_Q) || is_key_pressed(game->input, SDL_SCANCODE_ESCAPE)) {
    printf("\t[[MENU]]\nPRESS [ENTER] TO PLAY\nPRESS [Q] OR [ESC] TO EXIT THE GAME\n\n");
    game_init(game);
  }
  /*
  if (is_key_pressed(game->input, SDL_SCANCODE_R)) {
    printf("\t[[PLAYING]]\nPRESS [P] TO PAUSE\nPRESS [Q] OR [ESC] TO EXIT TO MENU\n\n");
    game_restart(game);
  }
  */


}

void game_render_paused(game_t* game) {
  const char pause_text[] = "PAUSED";
  draw_menu(game->renderer, game->font, pause_text);
}

void game_update_gameover(game_t* game, f64 delta_time) {
   if (is_key_pressed(game->input, SDL_SCANCODE_Q) || is_key_pressed(game->input, SDL_SCANCODE_ESCAPE)) {
    printf("\t[[MENU]]\nPRESS [ENTER] TO PLAY\nPRESS [Q] OR [ESC] TO EXIT THE GAME\n\n");
    game_init(game);
    //game_restart(game);
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_RETURN) || is_key_pressed(game->input, SDL_SCANCODE_R)) {
    printf("\t[[PLAYING]]\nPRESS [P] TO PAUSE\nPRESS [Q] OR [ESC] TO EXIT TO MENU\n\n"); 
    game_init(game);
    game->state = STATE_PLAYING;
  }


}
void game_render_gameover(game_t* game) {
  const char gameover_text[] = "GAMEOVER";
  draw_menu(game->renderer, game->font, gameover_text);
}


