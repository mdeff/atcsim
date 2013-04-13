/* 
 * File:   Airplane.h
 * Author: michael
 *
 * Created on 25. mars 2013, 21:39
 */

#ifndef AIRPLANE_H
#define	AIRPLANE_H

#include "Entity.h"

// Forward declarations (no header including) (namespace pollution, build time).
class Surface;

class Airplane : public Entity {
  
public:
  
  // There is no default constructor.
  Airplane() = delete;
  Airplane(int identification, int altitude, float cape,
           int velocity, int xInitial, int yInitial);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Airplane(const Airplane& orig) = default;
  Airplane& operator=(const Airplane& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Airplane(Airplane&& orig) = default;
  Airplane& operator=(Airplane&& orig) = default;
  
  // Default : call base class'es destructor and destructors of all members.
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Airplane() throw() = default;
  
  // Redefinition of virtual methods inherited from IEntity class.
  void compute();
  void render(Surface& displaySurf);
    
protected:
  
private:
  
  int identification_;          // Flight number.
  int altitude_;
  
};

#endif	/* AIRPLANE_H */
