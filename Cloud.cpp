/* 
 * File:   Cloud.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 16:44
 */

#include <algorithm>  // For max_element().

#include "Cloud.h"



Cloud::Cloud(const std::vector<int16_t>& xCorners,
             const std::vector<int16_t>& yCorners,
             float cape, int velocity)
:
Polygon(xCorners, yCorners, 0, 0, 255, 128, cape, velocity) // Parent constructor.
{
}



void Cloud::compute(enum PosType posType) {
  
  // This entity can move, we have to compute it.
  this->computeMovement(posType);
  
}



void Cloud::checkForCollisionDispatch(Entity& entity, enum PosType posType) const {
  entity.checkForCollision(this, posType);
}

