/* 
 * File:   Cloud.h
 * Author: michael
 *
 * Created on 26. mars 2013, 16:44
 */

#ifndef CLOUD_H
#define	CLOUD_H

#include "Polygon.h"

class Cloud : public Polygon {
  
public:
  
  Cloud(const vector<Sint16>& xPoints, const vector<Sint16>& yPoints);
  
  // Do not define : use the compiler generated copy constructor.
  Cloud(const Cloud& orig);
  
  virtual ~Cloud();
  
private:

};

#endif	/* CLOUD_H */

