/* 
 * File:   Entity.h
 * Author: michael
 *
 * Created on 25. mars 2013, 16:40
 */

#ifndef ENTITY_H
#define	ENTITY_H

// Forward declarations (no header including) (namespace pollution, build time).
class Surface;


class Entity {
  
public:

  // There is no default constructor.
  Entity() = delete;
  Entity(float cape, int velocity, int xInitial, int yInitial);
  
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

  // Abstract methods that will have to be defined.
  virtual void compute() = 0;
  virtual void render(Surface& displaySurf) = 0;

protected:
  
  // Compute the movement of an entity.
  void computeMovement();
  
  float cape_;
  int velocity_;
  float xRef_, yRef_;   // Entity position on XY plane.
  
private:
  
};

#endif	/* ENTITY_H */
