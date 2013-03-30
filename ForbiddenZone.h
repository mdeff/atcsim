/* 
 * File:   ForbiddenZone.h
 * Author: michael
 *
 * Created on 26. mars 2013, 15:21
 */

#ifndef FORBIDDENZONE_H
#define	FORBIDDENZONE_H

#include "Polygon.h"

class ForbiddenZone : public Polygon {
  
public:
  
  ForbiddenZone(const std::vector<int16_t>& xPoints,
                const std::vector<int16_t>& yPoints);
  
  // Do not define : use the compiler generated copy constructor.
  ForbiddenZone(const ForbiddenZone& orig);
  
  virtual ~ForbiddenZone();
  
protected:
  
private:

};

#endif	/* FORBIDDENZONE_H */

