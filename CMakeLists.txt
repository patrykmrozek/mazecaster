
cmake_minimum_required(VERSION 3.10)
project(raycast C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories(${INC_DIR})

set(SRC_FILES
    ${SRC_DIR}/main.c
    ${SRC_DIR}/game.c
    ${SRC_DIR}/player.c
    ${SRC_DIR}/map.c
    ${SRC_DIR}/window.c
    ${SRC_DIR}/renderer.c
    ${SRC_DIR}/raycaster.c
    ${SRC_DIR}/utils.c
    ${SRC_DIR}/inputs.c
    ${SRC_DIR}/stack.c
    ${SRC_DIR}/linkedlist.c
    ${SRC_DIR}/graph.c
    ${SRC_DIR}/state.c
    ${SRC_DIR}/types.c
)

add_executable(raycast ${SRC_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

target_include_directories(raycast PRIVATE ${INC_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(raycast PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} m)

