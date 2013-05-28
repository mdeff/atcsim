/* 
 * File:   ForbiddenZone.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 15:21
 */

#include "ForbiddenZone.h"


ForbiddenZone::ForbiddenZone(const std::vector<int16_t>& xCorners,
                             const std::vector<int16_t>& yCorners)
:
Polygon(xCorners, yCorners, 0, 0, 0, 200, 0, 0) // Parent constructor.
{
}



void ForbiddenZone::compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) {
  // Void casting to avoid compiler warning about unused parameter.
  // We make it explicit that this is our intent.
  (void)posType;
}



void ForbiddenZone::checkForCollisionDispatch(Entity& entity, enum PosType posType) const {
  // Double dispatching (visitor pattern).
  entity.checkForCollision(this, posType);
}

