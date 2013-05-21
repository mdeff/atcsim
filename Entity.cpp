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
realPosition_(initialPosition), // Entity initial position.
simPosition_(initialPosition)
{
}



void Entity::checkForCollision(const Airplane* airplane, enum PosType posType) const {}
void Entity::checkForCollision(const ForbiddenZone* forbiddenZone, enum PosType posType) const {}
void Entity::checkForCollision(const Cloud* cloud, enum PosType posType) const {}



void Entity::resetSimPosition() {
  simPosition_ = realPosition_;
}



void Entity::computeMovement(enum PosType posType) {
  
  Point* position;
  
  // Select the position to modify.
  switch (posType) {
    case realPosition:
      position = &realPosition_;
      break;
    case simPosition:
      position = &simPosition_;
  }
  
  // Pi is needed to convert from degrees to gradiant. We could also have used
  // M_PI (defined in math.h) but it's not standard C++, althought POSIX.
  const float pi = std::atan(1.0f) * 4.0f;
  
  // Compute new position based on current velocity, cape and game framerate.
  // Divide by 50 to convert airplane speed from km/h (around 800) to pixel/s.
  if (position->x < WINDOWXSIZE && position->x > 0 &&
      position->y < WINDOWYSIZE && position->y > 0) {
    position->x += float(velocity_) * float(std::cos(cape_*pi/180))
                   / 50.0f / float(FPS::getFPS());
    position->y -= float(velocity_) * float(std::sin(cape_*pi/180))
                   / 50.0f / float(FPS::getFPS());
  }
  
}

