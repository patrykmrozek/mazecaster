#include "inputs.h"

void get_user_inputs(SDL_Window* window, Player* player) {
  const Uint8* keystate = SDL_GetKeyboardState(NULL);
  if (keystate[SDL_SCANCODE_W]) player->y -= 1;
  if (keystate[SDL_SCANCODE_A]) player->x -= 1;
  if (keystate[SDL_SCANCODE_S]) player->y += 1;
  if (keystate[SDL_SCANCODE_D]) player->x += 1;
  
}
