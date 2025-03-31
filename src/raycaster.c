#include "raycaster.h"

void cast_rays(SDL_Renderer* renderer, Player* player) {
  //DDA ALGORITHM
  //finds which squares a line hits
  //first checks all horizontal grid lines from player in the direction of a ray for all rays 
  //alg stops if a wall is detected
  //same is done for all vertical grid lines

  int dof; // depth of field (how many line checks)
  float rayX, rayY, rayA; //ray x, y, angle
  float offsetX, offsetY; //offset will be used per cell in the grid to reach the end of the following cell
  int mapX, mapY; // determine which cell in the map the ray is

  //store the distances from player to the end of ray for:
  float distH;//horizontal rays
  float distV;//vertical rays
  float hx, hy, vx, vy; //store x and y of horiontal and vertical checks seperately

  rayA = player->a;
  rayX = player->x;
  rayY = player->y;


  for (int i=0; i<1; i++) {
    //sin(0)=0 and sin(PI)=0, so to prevent div by 0
    //fabsf calculates the floating absolute value, and in this case if it falls within the epsilon threshold,
    //it can be ruled as zero and therefore the ray is pointing approx directly left or right, and skipped
    if (fabs(sin(rayA)) > 0.001f) {
      dof = 0; //initilaize to 0, will be incrememnted every interation
      float aTan = -cos(rayA) / sin(rayA); //calculates inverse of tan
      printf("RAY ANGLE: %f\n", rayA);
      printf("ATAN: %f\n", aTan);

      //HORIZONTAL LINE CHECKS 
      if (rayA > PI) { //if angle of ray is above 180deg, looking up
        // need to round the rays y position to the nearest TILE_SIZE
        rayY = round(player->y / TILE_SIZE) * TILE_SIZE; //y position of the ray
        rayX = (player->y - rayY) * aTan + player->x; //x position of the ray
        offsetY = -TILE_SIZE; //calculate y offset
        offsetX = -offsetY * aTan; // calculate x offset
      }
      if (rayA < PI) { //if angle of ray is below 180deg, looking down
        // need to round the rays y position to the nearest TILE_SIZE
        rayY = round(player->y / TILE_SIZE) * TILE_SIZE + TILE_SIZE; //y position of the ray
        rayX = (player->y - rayY) * aTan + player->x; //x position of the ray
        offsetY = TILE_SIZE; //calculate y offset
        offsetX = -offsetY * aTan; // calculate x offset
      }
      while (dof<8) { //just check within the bounds of the dof
        //need to translate wall hit coordinates to location in the map matrix
        mapX = (int)(rayX/TILE_SIZE);
        mapY = (int)(rayY/TILE_SIZE);
        // if the current map tile at mapX and mapY is within the map matrix
        if (mapX > 0 && mapY > 0 && mapX < MAP_WIDTH && mapY < MAP_HEIGHT) {
          //if it has hit a wall
          if (MAP[mapY][mapX] == 1) { // we hit a wall
            printf("MAPx: %d, MAPy: %d\n", mapX, mapY);
            dof = 8;
          } else { // otherwise extend the ray by offset x and y and increase dof
            rayX += offsetX;
            rayY += offsetY;
            dof += 1;
          }
        } else {
          dof = 8;
        }
      }
    }
    
    distH = distance_two_points(player->x, player->y, rayX, rayY);
    hx = rayX;
    hy = rayY;
        //draw ray from player to the end of the ray
        //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        //SDL_RenderDrawLine(
          //renderer,
          //player->x + (player->size/2),
          //player->y + (player->size/2),
          //rayX,
          //rayY
        //  );

  //VERTICAL LINE CHECKS
  if (fabs(sin(rayA)) > 0.001f) {
      dof = 0;
      float nTan = -tan(rayA); //negative tan
      printf("RAY ANGLE: %f\n", rayA);
      printf("ATAN: %f\n", nTan);

      if (rayA < PI2 || rayA > 3*PI2) { //if angle of ray is below 90deg OR above 270deg, looking right
        // need to round the rays x position to the nearest TILE_SIZE
        rayX = round(player->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE; //x position of the ray
        rayY = (player->x - rayX) * nTan + player->y; //y position of the ray
        offsetX = TILE_SIZE; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      if (rayA > PI2 && rayA < 3*PI2) { //if angle of ray is above 90deg and below 270deg, left
        // need to round the rays y position to the nearest TILE_SIZE
        rayX = round(player->x / TILE_SIZE) * TILE_SIZE; //x position of the ray
        rayY = (player->x - rayX) * nTan + player->y; //y position of the ray
        offsetX = -TILE_SIZE; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      while (dof<8) { //just check within the bounds of the dof
        //need to translate wall hit coordinates to location in the map matrix
        mapX = (int)(rayX/TILE_SIZE);
        mapY = (int)(rayY/TILE_SIZE);
        // if the current map tile at mapX and mapY is within the map matrix
        if (mapX > 0 && mapY > 0 && mapX < MAP_WIDTH && mapY < MAP_HEIGHT) {
          //if it has hit a wall
          if (MAP[mapY][mapX] == 1) { // we hit a wall
            printf("MAPx: %d, MAPy: %d\n", mapX, mapY);
            dof = 8;
          } else { // otherwise extend the ray by offset x and y and increase dof
            rayX += offsetX;
            rayY += offsetY;
            dof += 1;
          }
        } else {
          dof = 8;
        }
      }
    }
    distV = distance_two_points(player->x, player->y, rayX, rayY);
    vx = rayX;
    vy = rayY;
    

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);

    //draws the shortest ray between the horizontal checker and the vertical checker
    if (distH < distV) {
      //draw ray from player to the end of the ray
      SDL_RenderDrawLine(
        renderer,
        player->x + (player->size/2),
        player->y + (player->size/2),
        hx,
        hy
      );
    }else{
      SDL_RenderDrawLine(
        renderer,
        player->x + (player->size/2),
        player->y + (player->size/2),
        vx,
        vy
      );
    }
  }
}

