/* 
 * File:   ForbiddenZone.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 15:21
 */

#include "ForbiddenZone.h"

ForbiddenZone::ForbiddenZone(const vector<Sint16>& xCorners,
                             const vector<Sint16>& yCorners)
:
Polygon(xCorners, yCorners, 255, 255, 255, 128) // Parent constructor.
{ }



ForbiddenZone::~ForbiddenZone() {
  // Default: call base class'es destructor and destructors of all members.
}

