#ifndef STATE_H 
#define STATE_H


#include <SDL2/SDL.h>
#include <stdio.h>

#include "types.h"
#include "renderer.h"
#include "raycaster.h"

typedef enum game_state {
  STATE_MENU,
  STATE_PLAYING,
  STATE_PAUSED,
  STATE_GAMEOVER,
  STATE_COUNT //since count is the last item in the enum it will correctly index states
} game_state_t;

struct game; //forward declaration

//state handler struct 
typedef struct game_state_handler {
  //function pointers, these will allow for dynamically calling update and render functions depending on current gameState
  void (*update)(struct game* game, f64 delta_time);
  void (*render)(struct game* game);
} game_state_handler_t;


//telling the compiler that stateHandlers exists somewhere
extern game_state_handler_t state_handlers[STATE_COUNT];

//STATE_MENU functions
void game_update_menu(struct game* game, f64 delta_time);
void game_render_menu(struct game* game);
//STATE_PLAYING functions
void game_update_playing(struct game* game, f64 delta_time);
void game_render_playing(struct game* game);
//STATE_PAUSED functions
void game_update_paused(struct game* game, f64 delta_time);
void game_render_paused(struct game* game);
//STATE_GAMEOVER functions
void game_update_gameover(struct game* game, f64 delta_time);
void game_render_gameover(struct game* game);



#endif
