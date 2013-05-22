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
simPosition_(initialPosition),
selected_(false)
{
}



void Entity::checkForCollision(const Airplane* airplane, enum PosType posType) {}
void Entity::checkForCollision(const ForbiddenZone* forbiddenZone, enum PosType posType) {}
void Entity::checkForCollision(const Cloud* cloud, enum PosType posType) {}



void Entity::resetSimulation() {
  simPosition_ = realPosition_;
}



bool Entity::getSelected() const {
  return selected_;
}



void Entity::setSelected(bool selected) {
  selected_ = selected;
}



void Entity::changeCape(int x, int y) {
  printf("Change cape.\n");
}



void Entity::computeMovement(enum PosType posType, int gameFieldWidth, int gameFieldHeight) {
  
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
  if (position->x < gameFieldWidth && position->x > 0 &&
      position->y < gameFieldHeight && position->y > 0) {
    position->x += float(velocity_) * float(std::cos(cape_*pi/180))
                   / 50.0f / float(FPS::getFPS());
    position->y -= float(velocity_) * float(std::sin(cape_*pi/180))
                   / 50.0f / float(FPS::getFPS());
  }
  
}

