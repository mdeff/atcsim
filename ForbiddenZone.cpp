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
Polygon(xCorners, yCorners, 0, 0, 0, 128, 0, 0) // Parent constructor.
{
}



void ForbiddenZone::compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) {
}



void ForbiddenZone::checkForCollisionDispatch(Entity& entity, enum PosType posType) const {
  entity.checkForCollision(this, posType);
}

