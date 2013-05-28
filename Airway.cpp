/* 
 * File:   Airways.cpp
 * Author: michael
 * 
 * Created on 23. mai 2013, 00:32
 */

#include "Airway.h"


Airway::Airway(const std::vector<int16_t>& xCorners,
                 const std::vector<int16_t>& yCorners)
:
Polygon(xCorners, yCorners, 0, 140, 0, 160, 0, 0) // Parent constructor.
{
}



void Airway::compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) {
  // Void casting to avoid compiler warning about unused parameter.
  // We make it explicit that this is our intent.
  (void)posType;
}



void Airway::checkForCollisionDispatch(Entity& entity, enum PosType posType) const {
  // Double dispatching (visitor pattern).
  entity.checkForCollision(this, posType);
}

