#include "utils.h"

f64 deg_to_rad(f32 degrees) {
  f64 radians = degrees * (PI / 180);
  return radians;
}

f64 calc_delta_time() {
  static u32 prevTime = 0; //preserved between func calls

  u32 currTime = SDL_GetTicks(); // returns number of ms since SDL library init
  
  //if first call, return 60fps (1/60)
  if (prevTime == 0) {
    prevTime = currTime;
    return 1/60;
  }

  f64 dTime = (currTime - prevTime) / 1000.; //convert to secs 
  prevTime = currTime;

  // had issues with dTime being 0, causing supposed infinite FPS due to division by 0
  // need to set a minimum threshold for deltaTime as SDL_GetTicks may be called twice at the same time
  if (dTime <= 0.001) {
    dTime = 0.001;
  }
  return dTime;
}

float dist(f32 x1, f32 y1, f32 x2, f32 y2) {
  f32 x_sqr = (x2-x1)*(x2-x1);
  f32 y_sqr = (y2-y1)*(y2-y1);
  f32 dist = sqrt(x_sqr+y_sqr);
  return dist;
}
