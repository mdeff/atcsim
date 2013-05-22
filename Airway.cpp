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
}



void Airway::checkForCollisionDispatch(Entity& entity, enum PosType posType) const {
  entity.checkForCollision(this, posType);
}

