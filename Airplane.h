/* 
 * File:   Airplane.h
 * Author: michael
 *
 * Created on 25. mars 2013, 21:39
 */

#ifndef AIRPLANE_H
#define	AIRPLANE_H


#include "Entity.h"


// Forward declarations (no header includes) (namespace pollution, build time).
class Cloud;
class ForbiddenZone;
class Surface;


class Airplane : public Entity {
  
public:
  
  // There is no default constructor.
  Airplane() = delete;
  Airplane(unsigned int number, unsigned int identification, unsigned int
           altitude, float cape, int velocity, Point initialPosition);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Airplane(const Airplane& orig) = default;
  Airplane& operator=(const Airplane& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Airplane(Airplane&& orig) = default;
  Airplane& operator=(Airplane&& orig) = default;
  
  // Default : call base class'es destructor and destructors of all members.
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Airplane() throw() = default;
  
  // Redefinition of virtual methods inherited from Entity class.
  virtual void compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) final;
  virtual void render(Surface& displaySurf) const final;
    
  // Redirection method used to implement double dispatching (visitor pattern).
  virtual void checkForCollisionDispatch(Entity& entity, enum PosType posType) const final;
  
  // Return the airplane position.
  const struct Point* getPosition(enum PosType posType) const;
  
  // Return the airplane position.
  unsigned int getAltitude() const;
  
  // Reset the simulation attributes.
  virtual void resetSimulation() final;
  
  // Check if a mouse click is on the airplane, and select it accordingly.
  virtual bool checkMouseClick(int mX, int mY) const final;
  virtual bool isSelected() const final;
  virtual void select(bool status) final;
  
protected:
  
private:
  
  // Airplane number, used to place side panel informations.
  unsigned int number_;
  
  // Airplane specific attributes : flight number and altitude.
  unsigned int identification_;
  unsigned int altitude_;
  
  // Indicate if the airplane is selected by the user.
  bool selected_;
  
  // It indicates if future collisions with some entities are predicted.
  struct EntityTypes predictedCollision_;
  
  // Collision handling functions : take different actions based on entity type.
  virtual void checkForCollision(const Airplane* airplane,
                                 enum PosType posType) final;
  virtual void checkForCollision(const ForbiddenZone* forbiddenZone,
                                 enum PosType posType) final;
  virtual void checkForCollision(const Cloud* cloud,
                                 enum PosType posType) final;
  
  // Print informations about the airplane on the side panel.
  void printSidePanelInfo(Surface& displaySurf) const;
  
};

#endif	/* AIRPLANE_H */
