/* 
 * File:   Entity.h
 * Author: michael
 *
 * Created on 25. mars 2013, 16:40
 */

#ifndef IENTITY_H
#define	IENTITY_H

// Forward declarations (no header including) (namespace pollution, build time).
class Surface;

// This is an interface (abstract) class like the ones in Java or C#.
// It contains only pure virtual (abstract) methods
// and a virtual destructor (important).

class IEntity {
  
public:

  // Virtual destructor to avoid undefined behaviours if someone tries to
  // delete an object of type IEntity.
  // For exemple : IEntity * obj = new Airplane(...); delete obj;
  virtual ~IEntity() {}

  // abstract methods that will have to be defined
  virtual void loop() = 0;
  virtual void render(Surface& displaySurf) = 0;
  virtual void cleanup() = 0;

protected:
  
private:
  
};

#endif	/* IENTITY_H */
