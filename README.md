# mazecaster
A simple raycasting engine written in C using SDL2 that generates and renders 3D-style mazes for the player to explore.

## Features
- **Raycasting Engine:** Implements classic raycasting techniques for 3D-like rendering.
- **Maze Generation:** Procedurally generates mazes.
- **Real-Time rendering:** 3D-style rendering using SDL2.
- **Player Movement:** Maze navigation.

## Requirements
- CMake (3.10+)
- Git
- GCC

## Dependencies
- [SDL](https://github.com/libsdl-org/SDL)
- [SDL_TTF](https://github.com/libsdl-org/SDL_ttf)


## How to build
```console
git clone https://github.com/patrykmrozek/mazecaster.git
cd mazecaster
mkdir build
cd build
cmake ..
make
./mazecaster
```

## Controls
- **WASD** for player movement
- **R/L Arrow Keys** to look around
- **M** to toggle minimap
- **P** to pause/unpause
- **ESC** to quit to menu
- **R** to restart (when paused)

## Status 
Work in progress - bugs expected

## License
MIT License

> Copyright (c) 2025 Patryk Mrozek

> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:

> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.

> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.


