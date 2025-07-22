#include "raycaster.h"

void cast_rays(SDL_Renderer* renderer, bool map_visible, player_t* player, map_t* map, SDL_Rect* map_rect) {
  //DDA ALGORITHM
  //finds which squares a line hits
  //first checks all horizontal grid lines from player in the direction of a ray for all rays 
  //alg stops if a wall is detected
  //same is done for all vertical grid lines

  u8 dof; // depth of field 
  f64 rayX, rayY, rayA; //ray x, y, angle
  f32 offsetX, offsetY; //the distance to the next line
  usize mapX, mapY; // determine which cell in the map the ray is

  //store the distances from player to the end of ray for:
  f32 distH;//horizontal rays
  f32 distV;//vertical rays
  f32 distT; //will hold the shorter of the two rays
  f32 hx, hy, vx, vy; //store x and y of horiontal and vertical checks seperately
  u8 pixels = 5; //how many pixels each ray will take up
  //if map_visible, there will be enough rays to fill half the screen
  //otherwise, there will be enough to fill the whole screen
  u8 num_rays = (map_visible) ? (WIDTH/2)/pixels : (WIDTH/pixels); //number of rays required to fill up WIDTH/2 of the screen 
  f32 fov = (map_visible) ? deg_to_rad(60) : deg_to_rad(80);
  f32 step = fov/num_rays; //how much each ray will step 
  rayX = player->pos.x;
  rayY = player->pos.y;
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
      f32 aTan = -1.0f / tan(rayA); //calculates inverse of tan

      //HORIZONTAL LINE CHECKS 
      if (rayA > PI) { //if angle of ray is above 180deg, looking up
        rayY = floor(player->pos.y / map->tile_size) * map->tile_size - 0.001f; //find ray y pos
        rayX = (player->pos.y - rayY) * aTan + player->pos.x; //find ray x pos
        offsetY = -map->tile_size; //calculate y offset
        offsetX = -offsetY * aTan; // calculate x offset
      }
      if (rayA < PI) { //if angle of ray is below 180deg, looking down
        rayY = ceil(player->pos.y / map->tile_size) * map->tile_size;
        rayX = (player->pos.y - rayY) * aTan + player->pos.x;
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
    distH = dist(player->pos.x, player->pos.y, rayX, rayY); //dist from player to end of horizontal-checking ray
    hx = rayX;
    hy = rayY;
    /*
        //draw ray from player to the end of the ray
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        SDL_RenderDrawLine(
          renderer,
          player->pos.x + (player->size/2),
          player->pos.y + (player->size/2),
          hx,
          hy
        );
  */

  //VERTICAL LINE CHECKS
  if (fabs(cos(rayA)) > 0.001f) {
      dof = 0;
      f32 nTan = -tan(rayA); //negative tan
      //start at the next grid line (floor + map->tile_size)
      if (rayA < PI2 || rayA > 3*PI2) { //if angle of ray is below 90deg OR above 270deg, looking right
        rayX = floor(player->pos.x / map->tile_size) * map->tile_size + map->tile_size; //x position of the ray
        rayY = (player->pos.x - rayX) * nTan + player->pos.y; //y pos of ray
        offsetX = map->tile_size; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      //start at the previous grid line (floor)
      if (rayA > PI2 && rayA < 3*PI2) { //if angle of ray is above 90deg and below 270deg, left
        rayX = floor(player->pos.x / map->tile_size) * map->tile_size - 0.0001f; //x position of the ray 
        rayY = (player->pos.x - rayX) * nTan + player->pos.y; //y position of the ray
        offsetX = -map->tile_size; //calculate y offset
        offsetY = -offsetX * nTan; // calculate x offset
      }
      while (dof<map->width) {
        //printf("Angle: %.2f° nTan: %.2f offsetX: %.2f offsetY: %.2f\n", rayA * 180/PI, nTan, offsetX, offsetY);
        //printf("Start: (%.2f,%.2f) End: (%.2f,%.2f)\n", player->pos.x, player->pos.y, rayX, rayY);
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
    distV = dist(player->pos.x, player->pos.y, rayX, rayY);//dist from player to end of vertical-checking ray
    vx = rayX;
    vy = rayY;
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    /*
        SDL_RenderDrawLine(
          renderer,
          player->pos.x + (player->size/2),
          player->pos.y + (player->size/2),
          vx,
          vy
        );
    
*/
    //draws the shortest ray between the horizontal checker and the vertical checker  
    //printf("distH: %f, distV: %f\n", distH, distV);
    
    //normalization divisor
    f32 ndivw = (float)(map->width * map->tile_size);
    f32 ndivh = (float)(map->height * map->tile_size);
    
    //normalize player x and y
    f32 npx = player->pos.x / ndivw;
    f32 npy = player->pos.y / ndivh;
    //normalize vx and vy
    f32 nvx = vx/ndivw;
    f32 nvy = vy/ndivh;
    //normalize hx and hy
    f32 nhx = hx/ndivw;
    f32 nhy = hy/ndivh;

    //translated player coords
    u16 tpx = map_rect->x + (int)(npx * map_rect->w);
    u16 tpy = map_rect->y + (int)(npy * map_rect->h);

    u16 tvx = map_rect->x + (int)(nvx * map_rect->w);
    u16 tvy = map_rect->y + (int)(nvy * map_rect->h);

    u16 thx = map_rect->x + (int)(nhx * map_rect->w);
    u16 thy = map_rect->x + (int)(nhy * map_rect->h);
 
    f32 brightness;

    if (distH > distV) {
      distT = distV;
      brightness = 1.0f - (distT/((dof/1.2)*map->tile_size));
      if (brightness<0) brightness=0;
      if (brightness>1) brightness=1;
  
      SDL_SetRenderDrawColor(renderer, 200*brightness, 0, 255*brightness, 0);
      if (map_visible) {
        SDL_RenderDrawLine(renderer, tpx, tpy, tvx, tvy);
      };
      
    } else {
      distT = distH;
      brightness = 1.0f - (distT/((dof/1.2)*map->tile_size));
      if (brightness<0) brightness=0;
      if (brightness>1) brightness=1;

      SDL_SetRenderDrawColor(renderer, 255*brightness, 0, 255*brightness, 0);
      if (map_visible) {
        SDL_RenderDrawLine(renderer, tpx, tpy, thx, thy);
      };

    }

   //printf("DIST: %f\n", distT);

  //render 3d scene 
  draw_3d(renderer, map_visible, ray, distT, pixels, rayA, player, map);

  rayA += deg_to_rad(step); //add 1 degree in radians to the rays angle

  //normalize angles 
  rayA = fmod(rayA, 2*PI);
  if (rayA < 0) {rayA += 2*PI;}
  }
}

