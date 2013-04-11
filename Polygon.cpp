/* 
 * File:   Polygons.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 07:08
 */

#include <algorithm>  // For max_element().

#include "Polygon.h"
#include "Surface.h"

using namespace std;



Polygon::Polygon(const std::vector<int16_t>& xCorners,
                 const std::vector<int16_t>& yCorners,
                 const uint8_t red, const uint8_t green,
                 const uint8_t blue, const uint8_t alpha)
:
IEntity(), // Parent constructor.
xCorners_(xCorners),
yCorners_(yCorners),
xMin_(*min_element(xCorners_.begin(), xCorners_.end())),
xMax_(*max_element(xCorners_.begin(), xCorners_.end())),
yMin_(*min_element(yCorners_.begin(), yCorners_.end())),
yMax_(*max_element(yCorners_.begin(), yCorners_.end())),
red_(red),
green_(green),
blue_(blue),
alpha_(alpha) {
  
  for (int16_t& xCorner : xCorners_) {
    xCorner = int16_t(xCorner - xMin_);
  }
  for (int16_t& yCorner : yCorners_) {
    yCorner = int16_t(yCorner- yMin_);
  }
  
}



Polygon::~Polygon() {
  // Default: call base class'es destructor and destructors of all members.
}



void Polygon::render(Surface& displaySurf) {  
  
  // Create a new suface with the size of the real screen window.  
//  Surface polygonSurf(displaySurf.getWidth(), displaySurf.getHeight());
  Surface polygonSurf(xMax_-xMin_, yMax_-yMin_);
  
  // Draw a semi-transparent filled polygon for the inside.
  polygonSurf.drawFilledPolygon(xCorners_, yCorners_, red_, green_, blue_, alpha_);
  
  // Draw an anti-aliased solid polygon for the contour.
  polygonSurf.drawAaPolygon(xCorners_, yCorners_, red_, green_, blue_, 255);

//  displaySurf.blit(polygonSurf, 0, 0);
  displaySurf.blit(polygonSurf, xMin_, yMin_);
}



void Polygon::compute() {
}


