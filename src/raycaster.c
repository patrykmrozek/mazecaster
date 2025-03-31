#include "raycaster.h"

void cast_rays(SDL_Renderer* renderer, Player* player) {
  //sets the FOV to 66 degrees
  double planeX = 0;
  double planeY = 0.66;

  //DDA ALGORITHM
  //finds which squares a line hits
  //first checks all horizontal grid lines from player in the direction of a ray for all rays 
  //alg stops if a wall is detected
  //same is done for all vertical grid lines
 
  int dof; // depth of field (how many line checks)
  float rayX, rayY, rayA; //ray x, y, angle
  float offsetX, offsetY; //offset will be used per cell in the grid to reach the end of the following cell
  int mapX, mapY, mapPos; // determine which cell in the map the ray is
  
  rayA = player->a;

  for (int i=0; i<1; i++) {
    dof = 0; //initilaize to 0, will be incrememnted every interation
    float aTan = -1/tan(rayA); //calculates inverse of tan
    
    //HORIZONTAL LINE CHECKS 
    if (rayA > PI) { //if angle of ray is above 180deg, looking up
      // need to round the rays y position to the nearest TILE_SIZE
      rayY = round(player->y / TILE_SIZE) * TILE_SIZE; //y position of the ray
      rayX = (player->y - rayY) * aTan + player->x; //x position of the ray
      offsetY = -TILE_SIZE; //calculate y offset
      offsetX = -offsetY * aTan; // calculate x offset
    }
     if (rayA > PI) { //if angle of ray is below 180deg, looking down
      // need to round the rays y position to the nearest TILE_SIZE
      rayY = round(player->y / TILE_SIZE) * TILE_SIZE; //y position of the ray
      rayX = (player->y - rayY) * aTan + player->x; //x position of the ray
      offsetY = TILE_SIZE; //calculate y offset
      offsetX = -offsetY * aTan; // calculate x offset
    }

    if (rayA == PI || rayA == 0) { //if player is looking directly left or right
      rayX = player->x;
      rayY = player->y;
      dof = 8;
    }

    while (dof<8) { //just check within the bounds of the dof
      //check 
    }

    //VERTICAL LINE CHECKS

  }
  
  
}
