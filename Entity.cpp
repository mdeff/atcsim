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



Entity::Entity(float cape, int velocity, Point initialPosition)
:
cape_(cape),
velocity_(velocity),
refPos_(initialPosition) // Entity initial position.
{
}



void Entity::checkForCollision(const Airplane* airplane) const {}
void Entity::checkForCollision(const ForbiddenZone* forbiddenZone) const {}
void Entity::checkForCollision(const Cloud* cloud) const {}



void Entity::computeMovement() {
  
  // Pi is needed to convert from degrees to gradiant. We could also have used
  // M_PI (defined in math.h) but it's not standard C++, althought POSIX.
  const float pi = std::atan(1.0f) * 4.0f;
  
  // Compute the new position based on current velocity, cape and game framerate.
  // Divide by 50 to convert airplane speed from km/h (around 800) to pixel/s.
  if (refPos_.x < WINDOWXSIZE && refPos_.x > 0 && refPos_.y < WINDOWYSIZE && refPos_.y > 0) {
    refPos_.x += float(velocity_) * float(std::cos(cape_*pi/180)) / 50.0f / float(FPS::getFPS());
    refPos_.y -= float(velocity_) * float(std::sin(cape_*pi/180)) / 50.0f / float(FPS::getFPS());
  }
  
}

