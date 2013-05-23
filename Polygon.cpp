/* 
 * File:   Polygons.cpp
 * Author: michael
 * 
 * Created on 26. mars 2013, 07:08
 */

#include <algorithm>  // For max_element().

#include "Airplane.h"
#include "Polygon.h"
#include "Surface.h"



Polygon::Polygon(const std::vector<int16_t>& xCorners,
                 const std::vector<int16_t>& yCorners,
                 const uint8_t red, const uint8_t green,
                 const uint8_t blue, const uint8_t alpha,
                 const float cape, const int velocity)
:
Entity(cape, velocity,Point(
        *min_element(xCorners.begin(), xCorners.end()),
        *min_element(yCorners.begin(), yCorners.end()))), // Parent constructor.
xCorners_(xCorners),
yCorners_(yCorners),
xMax_(*max_element(xCorners_.begin(), xCorners_.end())),
yMax_(*max_element(yCorners_.begin(), yCorners_.end())),
red_(red),
green_(green),
blue_(blue),
alpha_(alpha) {
  
  for (int16_t& xCorner : xCorners_) {
    xCorner = int16_t(xCorner - realPosition_.x);
  }
  for (int16_t& yCorner : yCorners_) {
    yCorner = int16_t(yCorner - realPosition_.y);
  }
  
}



void Polygon::render(Surface& displaySurf) const {
  
  // Create a new suface with the size of the real screen window.  
//  Surface polygonSurf(displaySurf.getWidth(), displaySurf.getHeight());
  Surface polygonSurf(xMax_-int16_t(realPosition_.x)+1, yMax_-int16_t(realPosition_.y)+1);
  
  // Draw a semi-transparent filled polygon for the inside.
  polygonSurf.drawFilledPolygon(xCorners_, yCorners_, red_, green_, blue_, alpha_);
  
  // Draw an anti-aliased solid polygon for the contour.
  polygonSurf.drawPolygon(xCorners_, yCorners_, red_, green_, blue_, 255);

//  displaySurf.blit(polygonSurf, 0, 0);
  displaySurf.blit(polygonSurf, int16_t(realPosition_.x), int16_t(realPosition_.y));
}













// Copyright 2000 softSurfer, 2012 Dan Sunday
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.
 

// a Point is defined by its coordinates {int x, y;}
//===================================================================
 

// isLeft(): tests if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2  on the line
//            <0 for P2  right of the line
//    See: Algorithm 1 "Area of Triangles and Polygons"

int Polygon::isLeft(const Point& point, size_t p0, size_t p1) const {
  return (xCorners_[p1] - xCorners_[p0]) * (int(point.y)  - yCorners_[p0])
       - (int(point.x)  - xCorners_[p0]) * (yCorners_[p1] - yCorners_[p0]);
}



// wn_PnPoly(): winding number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]!=V[0]
//      Return:  wn = the winding number (=0 only when P is outside)

bool Polygon::isInside(Point point, enum PosType posType, bool mouse) const {
  
  // We cannot click on a polygon, so the mouse is never inside it.
  if (mouse)
    return false;
  
  int wn = 0;                    // the  winding number counter
  unsigned int n = xCorners_.size() - 1;
  
  // Select the position from which to rebase.
  const Point* position;
  switch (posType) {
    case realPosition:
      position = &realPosition_;
      break;
    case simPosition:
      position = &simPosition_;
  }
  
  // Rebase the entity (airplane) position to the polygon base coordinates.
  point.x -= position->x;
  point.y -= position->y;
  
  // loop through all edges of the polygon, edge from V[0] to V[i+1]
  for (size_t i = 0; i <= n; ++i) {
    if (yCorners_[i] <= point.y) {            // start y <= P.y
      if (yCorners_[i<n?i+1:0] > point.y)     // an upward crossing
        if (isLeft(point, i, i<n?i+1:0) > 0)  // P left of edge
          ++wn;                               // have a valid up intersect
    } else {                                  // start y > P.y (no test needed)
      if (yCorners_[i<n?i+1:0] <= point.y)    // a downward crossing
        if (isLeft(point, i, i<n?i+1:0) < 0)  // P right of edge
          --wn;                               // have a valid down intersect
    }
  }
  
  // If the winding number is greater than 0, the point is inside the polygon.
  return wn > 0 ? true : false;
}

