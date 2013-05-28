/* 
 * File:   Airways.h
 * Author: michael
 *
 * Created on 23. mai 2013, 00:32
 */

#ifndef AIRWAYS_H
#define	AIRWAYS_H


#include "Polygon.h"


class Airway : public Polygon {
  
public:
  
  // There is no default constructor.
  Airway() = delete;
  Airway(const std::vector<int16_t>& xPoints,
         const std::vector<int16_t>& yPoints);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Airway(const Airway& orig) = default;
  Airway& operator=(const Airway& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Airway(Airway&& orig) = default;
  Airway& operator=(Airway&& orig) = default;
  
  // Default : call base class'es destructor and destructors of all members.
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Airway() noexcept(true) = default;
  
  // Redeclaration of virtual methods inherited from Entity class.
  virtual void compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) final;
  
  // Redirection method used to implement double dispatching (visitor pattern).
  virtual void checkForCollisionDispatch(Entity& entity, enum PosType posType) const final;
  
protected:
  
private:

};


#endif	/* AIRWAYS_H */

