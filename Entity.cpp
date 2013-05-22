/* 
 * File:   Entity.cpp
 * Author: michael
 * 
 * Created on 11. avril 2013, 17:50
 */

#include <cmath>
#include <algorithm>    // For std::cos() and std::sin().

#include "Constants.h"
#include "Entity.h"
#include "Framerate.h"



Entity::Entity(float cape, int velocity, Point initialPosition)
:
currentCape_(cape),
targetCape_(cape),
velocity_(velocity),
realPosition_(initialPosition), // Entity initial position.
simPosition_(initialPosition),
selected_(false)
{
}



void Entity::checkForCollision(const Airplane* airplane, enum PosType posType) {}
void Entity::checkForCollision(const ForbiddenZone* forbiddenZone, enum PosType posType) {}
void Entity::checkForCollision(const Airway* airway, enum PosType posType) {}
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



void Entity::setTargetCape(Point point) {
  // cape = sin ( dx / dy )
  float dx = point.x - realPosition_.x;
  float dy = realPosition_.y - point.y;
  targetCape_ = 180/PI * std::atan(dy / dx);
  // Arctan return angle of +-90°, we want 0° to 360°.
  if (dx < 0)
    targetCape_ = targetCape_ + 180;
  else if (dy < 0)
    targetCape_ = targetCape_ + 360;
}



void Entity::computeMovement(enum PosType posType, int gameFieldWidth, int gameFieldHeight) {
  
  // Select the position to modify.
  Point* position;
  switch (posType) {
    case realPosition:
      position = &realPosition_;
      break;
    case simPosition:
      position = &simPosition_;
  }
  
  // Compute new position based on current velocity, cape and game framerate.
  if (position->x < gameFieldWidth && position->x > 0 &&
      position->y < gameFieldHeight && position->y > 0) {
    position->x += float(velocity_) * std::cos(currentCape_*PI/180.0f)
                   / SPEEDCONVERT / float(Framerate::getFPS());
    position->y -= float(velocity_) * std::sin(currentCape_*PI/180.0f)
                   / SPEEDCONVERT / float(Framerate::getFPS());
  }
  
}



void Entity::updateCape() {
  
  // Determine if a zero-crossing is shorter.
  if (std::abs(currentCape_+360.0f-targetCape_) < std::abs(currentCape_-targetCape_))
    currentCape_ += 360.0f;
  else if (std::abs(currentCape_-360.0f-targetCape_) < std::abs(currentCape_-targetCape_))
    currentCape_ -= 360.0f;
  
  // Increment or decrement the current cape, with a bound to target cape.
  // Consider framerate for computation.
  float delta(DELTAANGLE / float(Framerate::getFPS()));
  if (currentCape_ < targetCape_)
    currentCape_ = std::min(currentCape_+delta, targetCape_);
  else if (currentCape_ > targetCape_)
    currentCape_ = std::max(currentCape_-delta, targetCape_);
  
  // Correct current cape to stay in [0;360[ range.
  if (currentCape_ >= 360.0f)
    currentCape_ -= 360.0f;
  else if (currentCape_ < 0.0f)
    currentCape_ += 360.0f;
  
}

