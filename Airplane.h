/* 
 * File:   Airplane.h
 * Author: michael
 *
 * Created on 25. mars 2013, 21:39
 */

#ifndef AIRPLANE_H
#define	AIRPLANE_H

#include "IEntity.h"

class Airplane : public virtual IEntity {
  
public:
  
  Airplane(const int identification, const int altitude, const int cape,
           const int velocity, const int x, const int y);
  Airplane(const Airplane& orig);
  virtual ~Airplane();
  
  // Redefinition of virtual methods inherited from Entity class.
  void loop();
  void render(SDL_Surface* displaySurf);
  void cleanup();
  
private:
  
  int identification_;          // Flight number.
  int altitude_;
  int cape_;
  int velocity_;
  int x_, y_;                   // Position.
  SDL_Surface* textSurf_;
  TTF_Font* textFont_;
  SDL_Color textColor_;

};

#endif	/* AIRPLANE_H */
