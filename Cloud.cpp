/* 
 * File:   Cloud.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 16:44
 */

#include <algorithm>  // For max_element().

#include "Cloud.h"



namespace ATCsim {  // Project ATCsim namespace.



Cloud::Cloud(const std::vector<int16_t>& xCorners,
             const std::vector<int16_t>& yCorners,
             float cape, unsigned int velocity)
:
Polygon(xCorners, yCorners, 0, 0, 255, 128, cape, velocity) // Parent constructor.
{
}



void Cloud::compute(PosTypes posType, int gameFieldWidth, int gameFieldHeight) {
  // This entity can move, we have to compute it.
  computeMovement(posType);
}



void Cloud::checkForCollisionDispatch(Entity& entity, PosTypes posType) const {
  // Double dispatching (visitor pattern).
  entity.checkForCollision(this, posType);
}
  

}  // End of project ATCsim namespace.

