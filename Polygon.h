/* 
 * File:   Polygons.h
 * Author: michael
 *
 * Created on 26. mars 2013, 07:08
 */

#ifndef POLYGONS_H
#define	POLYGONS_H

#include <vector>
#include <stdint.h>   // Definitions of uint8_t and int16_t.
#include "IEntity.h"

// Forward declarations (no header including) (namespace pollution, build time).
class Surface;

class Polygon : public virtual IEntity {
  
public:
  
  Polygon(const std::vector<int16_t>& xPoints,
          const std::vector<int16_t>& yPoints,
          uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
  
  // Do not define : use the compiler generated copy constructor.
  Polygon(const Polygon& orig);
  
  virtual ~Polygon();
  
  // Redefinition of virtual methods inherited from IEntity class.
  void loop();
  void render(Surface& displaySurf);
  void cleanup();
  
protected:
  
private:
  
  std::vector<int16_t> xCorners_, yCorners_;    // Polygon corner.
  uint8_t red_, green_, blue_, alpha_;          // Polygon color.

};

#endif	/* POLYGONS_H */
