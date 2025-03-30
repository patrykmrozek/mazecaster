#include "utils.h"

double deg_to_rad(double degrees) {
  double radians = degrees * (M_PI / 180);
  return radians;
}

double calc_delta_time() {
  static Uint32 prevTime = 0; //preserved between func calls

  Uint32 currTime = SDL_GetTicks(); // returns number of ms since SDL library init
  
  //if first call, return 60fps (1/60)
  if (prevTime == 0) {
    prevTime = currTime;
    return 1/60;
  }

  double dTime = (currTime - prevTime) / 1000.; //convert to secs 
  prevTime = currTime;

  // had issues with dTime being 0, causing supposed infinite FPS due to division by 0
  // need to set a minimum threshold for deltaTime as SDL_GetTicks may be called twice at the same time
  if (dTime <= 0.001) {
    dTime = 0.001;
  }
  return dTime;
}
