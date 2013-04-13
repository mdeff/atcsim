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
                 const uint8_t blue, const uint8_t alpha,
                 const float cape, const int velocity)
:
Entity(cape, velocity, *min_element(xCorners.begin(), xCorners.end()), *min_element(yCorners.begin(), yCorners.end())), // Parent constructor.
xCorners_(xCorners),
yCorners_(yCorners),
xMax_(*max_element(xCorners_.begin(), xCorners_.end())),
yMax_(*max_element(yCorners_.begin(), yCorners_.end())),
red_(red),
green_(green),
blue_(blue),
alpha_(alpha) {
  
  for (int16_t& xCorner : xCorners_) {
    xCorner = int16_t(xCorner - xRef_);
  }
  for (int16_t& yCorner : yCorners_) {
    yCorner = int16_t(yCorner - yRef_);
  }
  
}



void Polygon::render(Surface& displaySurf) {  
  
  // Create a new suface with the size of the real screen window.  
//  Surface polygonSurf(displaySurf.getWidth(), displaySurf.getHeight());
  Surface polygonSurf(xMax_-int16_t(xRef_)+1, yMax_-int16_t(yRef_)+1);
  
  // Draw a semi-transparent filled polygon for the inside.
  polygonSurf.drawFilledPolygon(xCorners_, yCorners_, red_, green_, blue_, alpha_);
  
  // Draw an anti-aliased solid polygon for the contour.
  polygonSurf.drawPolygon(xCorners_, yCorners_, red_, green_, blue_, 255);

//  displaySurf.blit(polygonSurf, 0, 0);
  displaySurf.blit(polygonSurf, int16_t(xRef_), int16_t(yRef_));
}



void Polygon::compute() {
}


