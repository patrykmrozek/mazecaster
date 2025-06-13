#include "raycaster.h"

void cast_rays(SDL_Renderer* renderer, player_t* player, Map* map, SDL_Rect* map_rect) {
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
  int pixels = 5; //how many pixels each ray will take up
  int num_rays = (WIDTH/2)/pixels; //number of rays required to fill up WIDTH/2 of the screen 
  float fov = deg_to_rad(60); //fov = 60degrees in radianas
  float step = fov/num_rays; //how much each ray will step 
  rayX = player->x;
  rayY = player->y;
   for (int ray=0; ray<num_rays; ray++) {
    rayA = player->a - fov/2 + ray * step; //starts half of the fov to the left, and steps right for each step
     
    //normalize angles 
    rayA = fmod(rayA, 2*PI);
    if (rayA < 0) {rayA += 2*PI;}

    //sin(0)=0 and sin(PI)=0, so to prevent div by 0
    //fabsf calculates the floating absolute value, and in this case if it falls within the epsilon threshold,
    //it can be ruled as zero and therefore the ray is pointing approx directly left or right, and skipped
    if (fabs(sin(rayA)) > 0.001f) {
      dof = 0; //initilaize to 0, will be incrememnted every interation
      float aTan = -1.0f / tan(rayA); //calculates inverse of tan

      //HORIZONTAL LINE CHECKS 
      if (rayA > PI) { //if angle of ray is above 180deg, looking up
        rayY = floor(player->y / map->tile_size) * map->tile_size - 0.001f; //find ray y pos
        rayX = (player->y - rayY) * aTan + player->x; //find ray x pos
        offsetY = -map->tile_size; //calculate y offset
        offsetX = -offsetY * aTan; // calculate x offset
      }
      if (rayA < PI) { //if angle of ray is below 180deg, looking down
        rayY = ceil(player->y / map->tile_size) * map->tile_size;
        rayX = (player->y - rayY) * aTan + player->x;
        offsetY = map->tile_size;
        offsetX = -offsetY * aTan;
      }
      while (dof<map->width) { //just check within the bounds of the dof
        //need to translate wall hit coordinates to location in the map matrix
        mapX = (int)(rayX/map->tile_size);
        mapY = (int)(rayY/map->tile_size);
        // if the current map tile at mapX and mapY is within the map matrix
        if (mapX >= 0 && mapY >= 0 && mapX < map->width && mapY < map->height) {
          //if it has hit a wall
          if (map->grid[mapY][mapX] == 1) {
   //         printf("map->gridx: %d, map->gridy: %d\n", mapX, mapY);
            dof = map->width; //break the while loop
          } else { // otherwise check the next horizontal grid line
            rayX += offsetX;
            rayY += offsetY;
            dof += 1;
          }
        } else {
          dof = map->width;
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
      //start at the next grid line (floor + map->tile_size)
      if (rayA < PI2 || rayA > 3*PI2) { //if angle of ray is below 90deg OR above 270deg, looking right
        rayX = floor(player->x / map->tile_size) * map->tile_size + map->tile_size; //x position of the ray
        rayY = (player->x - rayX) * nTan + player->y; //y pos of ray
        offsetX = map->tile_size; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      //start at the previous grid line (floor)
      if (rayA > PI2 && rayA < 3*PI2) { //if angle of ray is above 90deg and below 270deg, left
        rayX = floor(player->x / map->tile_size) * map->tile_size - 0.0001f; //x position of the ray 
        rayY = (player->x - rayX) * nTan + player->y; //y position of the ray
        offsetX = -map->tile_size; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      while (dof<map->width) {
        //printf("Angle: %.2f° nTan: %.2f offsetX: %.2f offsetY: %.2f\n", rayA * 180/PI, nTan, offsetX, offsetY);
        //printf("Start: (%.2f,%.2f) End: (%.2f,%.2f)\n", player->x, player->y, rayX, rayY);
        //need to translate wall hit coordinates to location in the map matrix
        mapX = (int)(rayX/map->tile_size);
        mapY = (int)(rayY/map->tile_size);
        // if the current map tile at mapX and mapY is within the map matrix
        if (mapX >= 0 && mapY >= 0 && mapX < map->width && mapY < map->height) {
          //if it has hit a wall
          if (map->grid[mapY][mapX] == 1) { 
            dof = map->width;
          } else { //otherwise check the next vertcal grid line
            rayX += offsetX;
            rayY += offsetY;
            dof += 1;
          }
        } else {
          dof = map->width;
        }
      }
    }
    distV = dist(player->x, player->y, rayX, rayY);//dist from player to end of vertical-checking ray
    vx = rayX;
    vy = rayY;
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    /*
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
    
    //normalization divisor
    float ndivw = (float)(map->width * map->tile_size);
    float ndivh = (float)(map->height * map->tile_size);
    
    //normalize player x and y
    float npx = player->x / ndivw;
    float npy = player->y / ndivh;
    //normalize vx and vy
    float nvx = vx/ndivw;
    float nvy = vy/ndivh;
    //normalize hx and hy
    float nhx = hx/ndivw;
    float nhy = hy/ndivh;

    //translated player coords
    int tpx = map_rect->x + (int)(npx * map_rect->w);
    int tpy = map_rect->y + (int)(npy * map_rect->h);

    int tvx = map_rect->x + (int)(nvx * map_rect->w);
    int tvy = map_rect->y + (int)(nvy * map_rect->h);

    int thx = map_rect->x + (int)(nhx * map_rect->w);
    int thy = map_rect->x + (int)(nhy * map_rect->h);
 
    float brightness;


    if (distH > distV) {
      distT = distV;
      brightness = 1.0f - (distT/((dof/1.2)*map->tile_size));
      if (brightness<0) brightness=0;
      if (brightness>1) brightness=1;
  
      SDL_SetRenderDrawColor(renderer, 200*brightness, 0, 255*brightness, 0);
      SDL_RenderDrawLine(renderer, tpx, tpy, tvx, tvy);
      
    } else {
      distT = distH;
      brightness = 1.0f - (distT/((dof/1.2)*map->tile_size));
      if (brightness<0) brightness=0;
      if (brightness>1) brightness=1;

      SDL_SetRenderDrawColor(renderer, 255*brightness, 0, 255*brightness, 0);
      SDL_RenderDrawLine(renderer, tpx, tpy, thx, thy);

    }

   //printf("DIST: %f\n", distT);

  //render 3d scene 
  draw_3d(renderer, ray, distT, pixels, rayA, player, map);

  rayA += deg_to_rad(step); //add 1 degree in radians to the rays angle

  //normalize angles 
  rayA = fmod(rayA, 2*PI);
  if (rayA < 0) {rayA += 2*PI;}
  }
}

