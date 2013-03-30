/* 
 * File:   Polygons.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 07:08
 */

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
red_(red),
green_(green),
blue_(blue),
alpha_(alpha) {
}



Polygon::~Polygon() {
  // Default: call base class'es destructor and destructors of all members.
}



void Polygon::render(Surface& displaySurf) {
            
  // Create a new suface with the size of the real screen window.
  Surface polygonSurf(displaySurf.getWidth(), displaySurf.getHeight());
  
  // Draw a semi-transparent filled polygon for the inside.
  polygonSurf.drawFilledPolygon(xCorners_, yCorners_, red_, green_, blue_, alpha_);
  
  // Draw an anti-aliased solid polygon for the contour.
  polygonSurf.drawAaPolygon(xCorners_, yCorners_, red_, green_, blue_, 255);
              
  displaySurf.blit(polygonSurf, 0, 0);
}



void Polygon::loop() {
}



void Polygon::cleanup() {
}

