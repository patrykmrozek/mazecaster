#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 1024
#define HEIGHT 512

SDL_Window* init_window();
SDL_Renderer* get_renderer(SDL_Window* window);
TTF_Font* load_font_main();
TTF_Font* load_font_desc();

#endif
