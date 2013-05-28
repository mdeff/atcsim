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
  Airplane(unsigned int number, std::string identification, unsigned int
           altitude, float cape, unsigned int velocity,
           struct CardinalPoint in, struct CardinalPoint out);
  
  // Use the default (member to member) copy ctor and copy assignment operator.
  Airplane(const Airplane& orig) = default;
  Airplane& operator=(const Airplane& orig) = default;
  // Use the default (member to member) move ctor and move assignment operator.
  Airplane(Airplane&& orig) = default;
  Airplane& operator=(Airplane&& orig) = default;
  
  // Default : call base class'es destructor and destructors of all members.
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Airplane() noexcept(true) = default;
  
  // Redefinition of virtual methods inherited from Entity class.
  virtual void compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) final;
  virtual void render(Surface& displaySurf) const final;
  
  // Redirection method used to implement double dispatching (visitor pattern).
  virtual void checkForCollisionDispatch(Entity& entity, enum PosType posType) const final;
  
  // Return the airplane altitude.
  unsigned int getAltitude() const;
  
  // Check if a point is inside an entity.
  virtual bool isInside(Point point, enum PosType posType = realPosition,
                        bool mouse = false) const final;
  
protected:
  
private:
  
  // Airplane number, used to place side panel informations.
  unsigned int number_;
  
  // Airplane specific attributes : flight number and altitude.
  std::string identification_;
  unsigned int altitude_;
  
  // Airplane in and out cardinal points.
  struct CardinalPoint in_;
  struct CardinalPoint out_;
  
  // Indicate if the airplane is visible or not.
  bool hidden_;
  
//  std::queue<Point> pastPositions_;
  
  // Collision handling functions : take different actions based on entity type.
  virtual void checkForCollision(const Airplane* airplane,
                                 enum PosType posType) final;
  virtual void checkForCollision(const Cloud* cloud,
                                 enum PosType posType) final;
  virtual void checkForCollision(const Airway* airway,
                                 enum PosType posType) final;
  virtual void checkForCollision(const ForbiddenZone* forbiddenZone,
                                 enum PosType posType) final;
  
  // Print informations about the airplane on the side panel.
  void renderSidePanelInfo(Surface& displaySurf) const;
  
  // Trace a line from the airplane center to an end point.
  void traceLineFromAirplane(Surface& displaySurf, Point endPoint, uint8_t red, uint8_t green, uint8_t blue) const;
  
};

#endif	/* AIRPLANE_H */

