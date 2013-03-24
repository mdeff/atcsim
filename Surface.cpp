/* 
 * File:   Surface.cpp
 * Author: malecoul
 * 
 * Created on February 22, 2013, 2:22 PM
 */

#include "Surface.h"

Surface::Surface() {
}

SDL_Surface* Surface::load(const char* file) {
  
	SDL_Surface* image = NULL;
	SDL_Surface* temp = SDL_LoadBMP(file);
  
	if(temp == NULL) {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
		return NULL;
	}

	image = SDL_DisplayFormat(temp);
	if (image == NULL) {
    printf("Unable to format surface: %s\n", SDL_GetError());
		return NULL;
	}
  
	SDL_FreeSurface(temp);

	return image;
}

//==============================================================================
bool Surface::draw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y) {

  if(surfDest == NULL || surfSrc == NULL) {
		return false;
	}

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;
	destR.w = surfSrc->w;
	destR.h = surfSrc->h;

	if (SDL_BlitSurface(surfSrc, NULL, surfDest, &destR) != 0) {
    printf("Unable to blit surface: %s\n", SDL_GetError());
    return false;    
  }

	return true;
}

//------------------------------------------------------------------------------
bool Surface::draw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y, int x2, int y2, int w, int h) {

  if(surfDest == NULL || surfSrc == NULL) {
		return false;
	}

	SDL_Rect destR, srcR;

	destR.x = x;
	destR.y = y;
	destR.w = surfSrc->w;
	destR.h = surfSrc->h;

	srcR.x = x2;
	srcR.y = y2;
	srcR.w = w;
	srcR.h = h;

	if (SDL_BlitSurface(surfSrc, &srcR, surfDest, &destR) != 0) {
    printf("Unable to blit surface: %s\n", SDL_GetError());
    return false;    
  }

	return true;
}

//------------------------------------------------------------------------------
bool Surface::transparent(SDL_Surface* surfDest, int r, int g, int b) {

  if(surfDest == NULL) {
		return false;
	}

  Uint32 key = SDL_MapRGB(surfDest->format, r, g, b);
  
	if (SDL_SetColorKey(surfDest, SDL_SRCCOLORKEY | SDL_RLEACCEL, key) != 0) {
    printf("Unable to set color key: %s\n", SDL_GetError());
    return false;    
  }

	return true;
}
