/* 
 * File:   Entity.h
 * Author: michael
 *
 * Created on 25. mars 2013, 16:40
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>

class Entity {
  
public:

  Entity();
  Entity(const Entity& orig);
  virtual ~Entity();

  virtual void loop() = 0;
  virtual void render(SDL_Surface* surf_Display) = 0;
  virtual void cleanup() = 0;

private:

};

#endif	/* ENTITY_H */
