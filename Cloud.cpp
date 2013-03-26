/* 
 * File:   Cloud.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 16:44
 */

#include "Cloud.h"

Cloud::Cloud(const vector<Sint16>& xCorners,
             const vector<Sint16>& yCorners)
:
Polygon(xCorners, yCorners, 0, 0, 255, 128) // Parent constructor.
{ }



Cloud::~Cloud() {
  // Default: call base class'es destructor and destructors of all members.
}