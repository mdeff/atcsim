/* 
 * File:   Surface.h
 * Author: michael
 *
 * Created on 24. mars 2013, 14:04
 */

#ifndef SURFACE_H
#define	SURFACE_H

#include <SDL/SDL.h>

class Surface {
public:
  Surface();
//  Surface(const Surface& orig);
//  virtual ~Surface();
  
  static SDL_Surface* load(const char* file);
  
  static bool draw(SDL_Surface* surf_Dest, SDL_Surface* surf_Src, int x, int y);
  static bool draw(SDL_Surface* surf_Dest, SDL_Surface* surf_Src, int x, int y, int x2, int y2, int w, int h);
  
  static bool transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
  
private:

};

#endif	/* SURFACE_H */
