/* 
 * File:   Cloud.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 16:44
 */

#include "Cloud.h"

Cloud::Cloud(const std::vector<int16_t>& xCorners, const std::vector<int16_t>& yCorners)
:
Polygon(xCorners, yCorners, 0, 0, 255, 128) // Parent constructor.
{
}



Cloud::~Cloud() {
  // Default: call base class'es destructor and destructors of all members.
}
