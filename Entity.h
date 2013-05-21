/* 
 * File:   Entity.h
 * Author: michael
 *
 * Created on 25. mars 2013, 16:40
 */

#ifndef ENTITY_H
#define	ENTITY_H


#include "Types.h"


// Forward declarations (no header includes) (namespace pollution, build time).
class Airplane;
class Cloud;
class ForbiddenZone;
class Surface;



class Entity {
  
  // Theses classes need access to checkForCollision() private methods.
  friend class Airplane;
  friend class Cloud;
  friend class ForbiddenZone;
  
public:

  // There is no default constructor.
  Entity() = delete;
  Entity(float cape, int velocity, Point initialPosition);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Entity(const Entity& orig) = default;
  Entity& operator=(const Entity& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Entity(Entity&& orig) = default;
  Entity& operator=(Entity&& orig) = default;
  
  // Virtual destructor to avoid undefined behaviours if someone tries to
  // delete an object of type IEntity.
  // For exemple : IEntity * obj = new Airplane(...); delete obj;
  // Default : call base class'es destructor and destructors of all members.
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Entity() throw() = default;

  // Abstract methods that will have to be defined by subclasses.
  virtual void compute(enum PosType posType) = 0;
  virtual void render(Surface& displaySurf) const = 0;
  
  // Redirection method used to implement double dispatching (visitor pattern).
  virtual void checkForCollisionDispatch(const Entity& entity, enum PosType posType) const = 0;
  
  // Reset the simulated position to the real one.
  void resetSimPosition();
  
protected:
    
  // Compute the movement of an entity.
  void computeMovement(enum PosType posType);
  
  float cape_;
  int velocity_;
  Point realPosition_;   // Real entity position on XY plane.
  Point simPosition_;    // Simulated entity position on XY plane.
  
private:
  
  // Collision handling functions : take different actions based on entity type.
  virtual void checkForCollision(const Airplane* airplane, enum PosType posType) const;
  virtual void checkForCollision(const ForbiddenZone* forbiddenZone, enum PosType posType) const;
  virtual void checkForCollision(const Cloud* cloud, enum PosType posType) const;
  
};

#endif	/* ENTITY_H */

