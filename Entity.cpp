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



Entity::Entity(float cape, unsigned int velocity, Point initialPosition)
:
currentCape_(cape),
targetCape_(cape),
velocity_(velocity),
realPosition_(initialPosition), // Entity initial position.
simPosition_(initialPosition),
selected_(false),
status_(),
pi_(std::atan(1.0f) * 4.0f)
{
}



// Void casting to avoid compiler warning about unused parameter.
// We make it explicit that this is our intent.
void Entity::checkForCollision(const Airplane* airplane, enum PosType posType) {(void)airplane; (void)posType;}
void Entity::checkForCollision(const ForbiddenZone* forbiddenZone, enum PosType posType) {(void)forbiddenZone; (void)posType;}
void Entity::checkForCollision(const Airway* airway, enum PosType posType) {(void)airway; (void)posType;}
void Entity::checkForCollision(const Cloud* cloud, enum PosType posType) {(void)cloud; (void)posType;}



// Const and non-const getPosition implementation.
// Templated to avoid code duplication.
template <typename TSrc, typename TRet>
TRet getPositionT(TSrc entity, enum PosType posType) {
  
  TRet position;
  
  switch (posType) {
    case simPosition:
      position = &(entity->simPosition_);
      break;
    case realPosition:
    default:
      position = &(entity->realPosition_);
  }
  
  return position;
}



// Constant method used in the general case.
const struct Point* Entity::getPosition(enum PosType posType) const {
  return getPositionT<const Entity*, const struct Point*>(this, posType);
}



// Non-constant method used by Entity::computeMovement.
struct Point* Entity::getPosition(enum PosType posType) {
  return getPositionT<Entity*, struct Point*>(this, posType);
}



void Entity::resetSimulation() {
  simPosition_ = realPosition_;
}



bool Entity::getSelected() const {
  return selected_;
}



void Entity::setSelected(bool selected) {
  selected_ = selected;
}



const struct AirplaneStatus* Entity::getStatus() const {
  return &status_;
}



void Entity::resetStatus() {
  status_.outRight = false;
  status_.outWrong = false;
  status_.airplaneSimCollision = false;
  status_.forbiddenZoneSimCollision = false;
  status_.airwaySimCollision = false;
  status_.cloudSimCollision = false;
  status_.airplaneRealCollision = false;
  status_.forbiddenZoneRealCollision = false;
  status_.airwayRealCollision = false;
  status_.cloudRealCollision = false;
}



void Entity::setTargetCape(Point point) {
  float dx = point.x - realPosition_.x;
  float dy = realPosition_.y - point.y;
  targetCape_ = 180/pi_ * std::atan(dy / dx);
  // Arctan return angle of +-90°, we want 0° to 360°.
  if (dx < 0)
    targetCape_ = targetCape_ + 180;
  else if (dy < 0)
    targetCape_ = targetCape_ + 360;
}



void Entity::computeMovement(enum PosType posType) {
  
  // Select the position to modify (remove the pointer constness).
  Point* position(getPosition(posType));
  
  // Compute new position based on current velocity, cape and game framerate.
  position->x += float(velocity_) * std::cos(currentCape_*pi_/180.0f)
                 / SPEEDCONVERT / float(Framerate::getFPS());
  position->y -= float(velocity_) * std::sin(currentCape_*pi_/180.0f)
                 / SPEEDCONVERT / float(Framerate::getFPS());
}



void Entity::updateCape() {
  
  // Determine if a zero-crossing is shorter.
  if (std::abs(currentCape_+360.0f-targetCape_) < std::abs(currentCape_-targetCape_))
    currentCape_ += 360.0f;
  else if (std::abs(currentCape_-360.0f-targetCape_) < std::abs(currentCape_-targetCape_))
    currentCape_ -= 360.0f;
  
  // Increment or decrement the current cape, with a bound to target cape.
  // Consider framerate for computation.
  const float delta(DELTAANGLE / float(Framerate::getFPS()));
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

