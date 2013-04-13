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
  
  // There is no default constructor.
  ForbiddenZone() = delete;
  ForbiddenZone(const std::vector<int16_t>& xPoints,
                const std::vector<int16_t>& yPoints);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  ForbiddenZone(const ForbiddenZone& orig) = default;
  ForbiddenZone& operator=(const ForbiddenZone& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  ForbiddenZone(ForbiddenZone&& orig) = default;
  ForbiddenZone& operator=(ForbiddenZone&& orig) = default;
  
  // Default : call base class'es destructor and destructors of all members.
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~ForbiddenZone() throw() = default;
  
protected:
  
private:

};

#endif	/* FORBIDDENZONE_H */

