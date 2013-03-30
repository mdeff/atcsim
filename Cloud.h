/* 
 * File:   Cloud.h
 * Author: michael
 *
 * Created on 26. mars 2013, 16:44
 */

#ifndef CLOUD_H
#define	CLOUD_H

#include "Polygon.h"

using namespace std;

class Cloud : public Polygon {
  
public:
  
  Cloud(const vector<int16_t>& xPoints, const vector<int16_t>& yPoints);
  
  // Do not define : use the compiler generated copy constructor.
  Cloud(const Cloud& orig);
  
  virtual ~Cloud();
  
protected:
  
private:

};

#endif	/* CLOUD_H */

