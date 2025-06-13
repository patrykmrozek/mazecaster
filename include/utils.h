#ifndef UTILS_H
#define UTILS_H

#include "window.h"
#include "types.h"

#include <math.h>
#define PI 3.1415926535f
#define PI2 PI/2 

f64 deg_to_rad(f32 degrees);
f64 calc_delta_time();
f32 dist(f32 x1, f32 y1, f32 x2, f32 y2);

#endif  
