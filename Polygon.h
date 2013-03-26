/* 
 * File:   Polygons.h
 * Author: michael
 *
 * Created on 26. mars 2013, 07:08
 */

#ifndef POLYGONS_H
#define	POLYGONS_H

#include <vector>
#include <SDL/SDL.h>
#include "IEntity.h"

using namespace std;

class Polygon : public virtual IEntity {
  
public:
  
  Polygon(const vector<Sint16>& xPoints, const vector<Sint16>& yPoints,
          const Uint8 red, const Uint8 green,
          const Uint8 blue, const Uint8 alpha);
  
  // Do not define : use the compiler generated copy constructor.
  Polygon(const Polygon& orig);
  
  virtual ~Polygon();
  
  void render(SDL_Surface* displaySurf);
  
private:
  
  vector<Sint16> xCorners_, yCorners_;   // polygon corner
  Uint8 red_, green_, blue_, alpha_;     // polygon color

};

#endif	/* POLYGONS_H */
