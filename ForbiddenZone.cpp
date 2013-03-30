/* 
 * File:   ForbiddenZone.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 15:21
 */

#include "ForbiddenZone.h"

using namespace std;



ForbiddenZone::ForbiddenZone(const vector<int16_t>& xCorners,
                             const vector<int16_t>& yCorners)
: Polygon(xCorners, yCorners, 0, 0, 0, 128) // Parent constructor.
{
}



ForbiddenZone::~ForbiddenZone() {
  // Default: call base class'es destructor and destructors of all members.
}

