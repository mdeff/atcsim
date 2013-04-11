/* 
 * File:   Airplane.h
 * Author: michael
 *
 * Created on 25. mars 2013, 21:39
 */

#ifndef AIRPLANE_H
#define	AIRPLANE_H

//#include <cstdint>
#include "IEntity.h"

// Forward declarations (no header including) (namespace pollution, build time).
class Surface;

class Airplane : public virtual IEntity {
  
public:
  
  Airplane(const int identification, const int altitude, const int cape,
           const int velocity, const int16_t x, const int16_t y);
  
  // Do not define : use the compiler generated copy constructor.
  Airplane(const Airplane& orig);
  
  virtual ~Airplane();
  
  // Redefinition of virtual methods inherited from IEntity class.
  void compute();
  void render(Surface& displaySurf);
    
protected:
  
private:
  
  int identification_;          // Flight number.
  int altitude_;
  int cape_;
  int velocity_;
  int16_t x_, y_;                   // Position.

  // Move the airplane.
  void move(float moveX, float moveY);

};

#endif	/* AIRPLANE_H */
