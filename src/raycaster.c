#include "raycaster.h"

void cast_rays(SDL_Renderer* renderer, Player* player) {
  //DDA ALGORITHM
  //finds which squares a line hits
  //first checks all horizontal grid lines from player in the direction of a ray for all rays 
  //alg stops if a wall is detected
  //same is done for all vertical grid lines

  int dof; // depth of field 
  float rayX, rayY, rayA; //ray x, y, angle
  float offsetX, offsetY; //the distance to the next line
  int mapX, mapY; // determine which cell in the map the ray is

  //store the distances from player to the end of ray for:
  float distH;//horizontal rays
  float distV;//vertical rays
  float distT; //will hold the shorter of the two rays
  float hx, hy, vx, vy; //store x and y of horiontal and vertical checks seperately
  rayA = player->a - (PI/6); //rays start 30 degrees to the left
  rayX = player->x;
  rayY = player->y;
  
  //normalize angles 
  rayA = fmod(rayA, 2*PI);
  if (rayA < 0) {rayA += 2*PI;}

  for (int ray=0; ray<60; ray++) {
    //sin(0)=0 and sin(PI)=0, so to prevent div by 0
    //fabsf calculates the floating absolute value, and in this case if it falls within the epsilon threshold,
    //it can be ruled as zero and therefore the ray is pointing approx directly left or right, and skipped
    if (fabs(sin(rayA)) > 0.001f) {
      dof = 0; //initilaize to 0, will be incrememnted every interation
      float aTan = -1.0f / tan(rayA); //calculates inverse of tan

      //HORIZONTAL LINE CHECKS 
      if (rayA > PI) { //if angle of ray is above 180deg, looking up
        rayY = floor(player->y / TILE_SIZE) * TILE_SIZE - 0.001f; //find ray y pos
        rayX = (player->y - rayY) * aTan + player->x; //find ray x pos
        offsetY = -TILE_SIZE; //calculate y offset
        offsetX = -offsetY * aTan; // calculate x offset
      }
      if (rayA < PI) { //if angle of ray is below 180deg, looking down
        rayY = ceil(player->y / TILE_SIZE) * TILE_SIZE;
        rayX = (player->y - rayY) * aTan + player->x;
        offsetY = TILE_SIZE;
        offsetX = -offsetY * aTan;
      }
      while (dof<8) { //just check within the bounds of the dof
        //need to translate wall hit coordinates to location in the map matrix
        mapX = (int)(rayX/TILE_SIZE);
        mapY = (int)(rayY/TILE_SIZE);
        // if the current map tile at mapX and mapY is within the map matrix
        if (mapX >= 0 && mapY >= 0 && mapX < MAP_WIDTH && mapY < MAP_HEIGHT) {
          //if it has hit a wall
          if (MAP[mapY][mapX] == 1) {
   //         printf("MAPx: %d, MAPy: %d\n", mapX, mapY);
            dof = 8; //break the while loop
          } else { // otherwise check the next horizontal grid line
            rayX += offsetX;
            rayY += offsetY;
            dof += 1;
          }
        } else {
          dof = 8;
        }
      }
    }
    distH = dist(player->x, player->y, rayX, rayY); //dist from player to end of horizontal-checking ray
    hx = rayX;
    hy = rayY;
    /*
        //draw ray from player to the end of the ray
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        SDL_RenderDrawLine(
          renderer,
          player->x + (player->size/2),
          player->y + (player->size/2),
          hx,
          hy
        );
  */

  //VERTICAL LINE CHECKS
  if (fabs(cos(rayA)) > 0.001f) {
      dof = 0;
      float nTan = -tan(rayA); //negative tan
      //start at the next grid line (floor + TILE_SIZE)
      if (rayA < PI2 || rayA > 3*PI2) { //if angle of ray is below 90deg OR above 270deg, looking right
        rayX = floor(player->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE; //x position of the ray
        rayY = (player->x - rayX) * nTan + player->y; //y pos of ray
        offsetX = TILE_SIZE; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      //start at the previous grid line (floor)
      if (rayA > PI2 && rayA < 3*PI2) { //if angle of ray is above 90deg and below 270deg, left
        rayX = floor(player->x / TILE_SIZE) * TILE_SIZE - 0.0001f; //x position of the ray 
        rayY = (player->x - rayX) * nTan + player->y; //y position of the ray
        offsetX = -TILE_SIZE; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      while (dof<8) {
        //printf("Angle: %.2f° nTan: %.2f offsetX: %.2f offsetY: %.2f\n", rayA * 180/PI, nTan, offsetX, offsetY);
        //printf("Start: (%.2f,%.2f) End: (%.2f,%.2f)\n", player->x, player->y, rayX, rayY);
        //need to translate wall hit coordinates to location in the map matrix
        mapX = (int)(rayX/TILE_SIZE);
        mapY = (int)(rayY/TILE_SIZE);
        // if the current map tile at mapX and mapY is within the map matrix
        if (mapX >= 0 && mapY >= 0 && mapX < MAP_WIDTH && mapY < MAP_HEIGHT) {
          //if it has hit a wall
          if (MAP[mapY][mapX] == 1) { 
            dof = 8;
          } else { //otherwise check the next vertcal grid line
            rayX += offsetX;
            rayY += offsetY;
            dof += 1;
          }
        } else {
          dof = 8;
        }
      }
    }
    distV = dist(player->x, player->y, rayX, rayY);//dist from player to end of vertical-checking ray
    vx = rayX;
    vy = rayY;
        
 /* 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderDrawLine(
          renderer,
          player->x + (player->size/2),
          player->y + (player->size/2),
          vx,
          vy
        );
    
*/
    //draws the shortest ray between the horizontal checker and the vertical checker  
    //printf("distH: %f, distV: %f\n", distH, distV);
    if (distH > distV) {
      distT = distV;
      SDL_SetRenderDrawColor(renderer, 200, 0, 255, 0);
      SDL_RenderDrawLine(
        renderer,
        player->x + (player->size/2),
        player->y + (player->size/2),
        vx,
        vy
      );
    } else {
      distT = distH;
      SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
      SDL_RenderDrawLine(
        renderer,
        player->x + (player->size/2),
        player->y + (player->size/2),
        hx,
        hy
      );
    }

  //render 3d scene 
  draw_3d(renderer, ray, distT, 8, rayA, player);

  rayA += (PI / 180); //add 1 degree in radians to the rays angle

  //normalize angles 
  rayA = fmod(rayA, 2*PI);
  if (rayA < 0) {rayA += 2*PI;}
  }
}

