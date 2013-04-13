/* 
 * File:   Entity.cpp
 * Author: michael
 * 
 * Created on 11. avril 2013, 17:50
 */

#include <cmath>    // For std::cos() and std::sin().

#include "Constants.h"
#include "Entity.h"
#include "FPS.h"



Entity::Entity(float cape, int velocity, int xInitial, int yInitial)
:
cape_(cape),
velocity_(velocity),
xRef_(float(xInitial)), // Entity initial position.
yRef_(float(yInitial))
{
}



void Entity::computeMovement() {
  
  // Pi is needed to convert from degrees to gradiant. We could also have used
  // M_PI (defined in math.h) but it's not standard C++, althought POSIX.
  const float pi = std::atan(1.0f) * 4.0f;
  
  // Compute the new position based on current velocity, cape and game framerate.
  // Divide by 50 to convert airplane speed from km/h (around 800) to pixel/s.
  if (xRef_ < WINDOWXSIZE && xRef_ > 0 && yRef_ < WINDOWYSIZE && yRef_ > 0) {
    xRef_ += float(velocity_) * float(cos(cape_*pi/180)) / 50.0f / float(FPS::getFPS());
    yRef_ -= float(velocity_) * float(sin(cape_*pi/180)) / 50.0f / float(FPS::getFPS());
  }
  
}

