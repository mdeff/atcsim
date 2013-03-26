/* 
 * File:   Polygons.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 07:08
 */

#include "Polygon.h"
#include "Surface.h"




Polygon::Polygon(const vector<Sint16>& xCorners, const vector<Sint16>& yCorners,
                 const Uint8 red, const Uint8 green,
                 const Uint8 blue, const Uint8 alpha)
:
IEntity(), // Parent constructor.
xCorners_(xCorners),
yCorners_(yCorners),
red_(red),
green_(green),
blue_(blue),
alpha_(alpha)
{ }


Polygon::~Polygon() {
  // Default: call base class'es destructor and destructors of all members.
}



void Polygon::render(SDL_Surface* displaySurf) {
  
  SDL_Surface* polygonSurf;  
  int nPoints(min(xCorners_.size(), yCorners_.size()));
          
  // Data(): returns pointer to the underlying array (C++11) (OK even if empty).
  
  filledPolygonRGBA(polygonSurf, xCorners_.data(), yCorners_.data(),
                    nPoints, red_, green_, blue_, alpha_);
  
  Surface::draw(displaySurf, polygonSurf, 0, 0);
  SDL_FreeSurface(polygonSurf);
}
