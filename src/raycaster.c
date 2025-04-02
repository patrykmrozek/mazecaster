#include "raycaster.h"

void draw_3d(SDL_Renderer* renderer, int colNum, float rayDist, int pixels) {
  /* 
  colNum - represents the current ray ('ray' value from for loop in cast_rays)
  rayDist - the shortest distance betweem distV and distH (the ray that will be rendered)
  pixels - how many pixels from left to right each ray will draw
  */
  float lineH = (TILE_SIZE*320) / rayDist; // the further away the rayDist, the smaller the wall height will be 
  if (lineH > 320) {lineH = 320;}
  float lineO = (HEIGHT/2) - lineH/2; //line offset, 

  for (int i=0; i<pixels; i++) {
    SDL_RenderDrawLine(
      renderer,
      (colNum*pixels) + (WIDTH/2) + i, // offsets the scene to the right of the incrememnted
      lineO,
      (colNum*pixels) + (WIDTH/2) + i,
      lineH + lineO
    );
  }
  
}

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
        // need to round the rays y position to the nearest TILE_SIZE
        rayY = floor(player->y / TILE_SIZE) * TILE_SIZE - 0.001f; //floor and ceil makes sure the ray snaps to th right side of the wal
        rayX = (player->y - rayY) * aTan + player->x; //x position of the ray
        offsetY = -TILE_SIZE; //calculate y offset
        offsetX = -offsetY * aTan; // calculate x offset
      }
      if (rayA < PI) { //if angle of ray is below 180deg, looking down
        // need to round the rays y position to the nearest TILE_SIZE
        rayY = ceil(player->y / TILE_SIZE) * TILE_SIZE; //y position of the ray
        rayX = (player->y - rayY) * aTan + player->x; //x position of the ray
        offsetY = TILE_SIZE; //calculate y offset
        offsetX = -offsetY * aTan; // calculate x offset
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
    
    distH = dist(player->x, player->y, rayX, rayY);
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
  if (fabs(cos(rayA)) > 0.1f) {
      dof = 0;
      float nTan = -tan(rayA); //negative tan
     
      //start at the nect grid line (floor + TILE_SIZE)
      if (rayA < PI2 || rayA > 3*PI2) { //if angle of ray is below 90deg OR above 270deg, looking right
        // need to round the rays x position to the nearest TILE_SIZE
        rayX = floor(player->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE; //x position of the ray
        rayY = (player->x - rayX) * nTan + player->y;
        offsetX = TILE_SIZE; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }

      //start at the previous grid line (floor)
      if (rayA > PI2 && rayA < 3*PI2) { //if angle of ray is above 90deg and below 270deg, left
        // need to round the rays y position to the nearest TILE_SIZE
        rayX = floor(player->x / TILE_SIZE) * TILE_SIZE - 0.0001f; //x position of the ray 
        rayY = (player->x - rayX) * nTan + player->y; //y position of the ray
        offsetX = -TILE_SIZE; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      while (dof<8) { //just check within the bounds of the dof
        printf("Angle: %.2f° nTan: %.2f offsetX: %.2f offsetY: %.2f\n", rayA * 180/PI, nTan, offsetX, offsetY);
        printf("Start: (%.2f,%.2f) End: (%.2f,%.2f)\n", player->x, player->y, rayX, rayY);
        //need to translate wall hit coordinates to location in the map matrix
        mapX = (int)(rayX/TILE_SIZE);
        mapY = (int)(rayY/TILE_SIZE);
        // if the current map tile at mapX and mapY is within the map matrix
        if (mapX >= 0 && mapY >= 0 && mapX < MAP_WIDTH && mapY < MAP_HEIGHT) {
          //if it has hit a wall
          if (MAP[mapY][mapX] == 1) { 
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
    distV = dist(player->x, player->y, rayX, rayY);
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
  
    printf("distH: %f, distV: %f\n", distH, distV);
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
    draw_3d(renderer, ray, distT, 8);

  rayA += (PI / 180); //add 1 degree in radians to the rays angle
     
  //normalize angles 
  rayA = fmod(rayA, 2*PI);
  if (rayA < 0) {rayA += 2*PI;}



  }

}

