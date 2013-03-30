/*
 * File:   Surface.cpp
 * Author: malecoul
 *
 * Created on February 22, 2013, 2:22 PM
 */

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>

#include "Surface.h"

using namespace std;



//Surface::Surface(SDL_Surface* surface)
//:
//surface_(surface) {
//
//  if (surface_ == NULL)
//    throw -1;
//}



Surface::Surface(const int w, const int h) {

//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//    rmask = 0xff000000;
//    gmask = 0x00ff0000;
//    bmask = 0x0000ff00;
//    amask = 0x000000ff;
//#else
    int rmask = 0x000000ff;
    int gmask = 0x0000ff00;
    int bmask = 0x00ff0000;
    int amask = 0xff000000;
//#endif

  // Create a new software surface (better software because we'll change it often).
  surface_ = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, rmask, gmask, bmask, amask);

  if (surface_ == NULL)
  {
    printf("Fail to create RGB surface: %s\n", SDL_GetError());
    throw -1;  // TODO
  }

}



Surface::Surface(int weight, int height, int colorDepth) {
    surface_ = SDL_SetVideoMode(weight, height, colorDepth,
                                SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (surface_ == NULL) {
      printf("Unable to set video mode: %s\n", SDL_GetError());
      throw -1;
    }
}



Surface::Surface(const char* file) {

  string errorString;

  SDL_Surface* tempSurf = SDL_LoadBMP(file);
  
  if (tempSurf == NULL) {
    printf("Unable to load bitmap: %s\n", errorString.c_str());
    throw -1;
  }
  
  surface_ = SDL_DisplayFormat(tempSurf);

	if (surface_ == NULL)
  {
    printf("Unable to format surface: %s\n", SDL_GetError());
    throw -1;
	}
}



Surface::Surface(const string text, const int red, const int green, const int blue,
                 const string font, const int size) {

  SDL_Color textColor = {red, green, blue};
//  textColor.r = red;
//  textColor.g = green;
//  textColor.b = blue;

  TTF_Font* textFont = TTF_OpenFont(font.c_str(), size);

  if (textFont == NULL)
    throw -1;

  surface_ = TTF_RenderText_Solid(textFont, text.c_str(), textColor);

  if (surface_ == NULL)
    throw -1;

  TTF_CloseFont(textFont);
}



Surface::~Surface() {
  SDL_FreeSurface(surface_);
  // Default: call base class'es destructor and destructors of all members.
}



int Surface::getWidth() {
  return surface_->w;
}



int Surface::getHeight() {
  return surface_->h;
}



//SDL_Surface* Surface::getPointer() const {
//  if (surface_ == NULL)
//    throw -1;
//  return surface_;
//}



void Surface::blit(const Surface& source, const int x, const int y) {

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;
	destR.w = source.surface_->w;
	destR.h = source.surface_->h;

	if (SDL_BlitSurface(source.surface_, NULL, surface_, &destR) != 0)
  {
    printf("Unable to blit surface: %s\n", SDL_GetError());
    throw -1;
  }
}



void Surface::blit(const Surface& source, const int x, const int y,
                   const int x2, const int y2, const int w, const int h) {

	SDL_Rect destR, srcR;

	destR.x = x;
	destR.y = y;
	destR.w = source.surface_->w;
	destR.h = source.surface_->h;

	srcR.x = x2;
	srcR.y = y2;
	srcR.w = w;
	srcR.h = h;

	if (SDL_BlitSurface(source.surface_, &srcR, surface_, &destR) != 0)
  {
    printf("Unable to blit surface: %s\n", SDL_GetError());
    throw -1;
  }
}



void Surface::makeTransparent(const int red, const int green, const int blue) {

  Uint32 key = SDL_MapRGB(surface_->format, red, green, blue);

	if (SDL_SetColorKey(surface_, SDL_SRCCOLORKEY | SDL_RLEACCEL, key) != 0)
  {
    printf("Unable to set color key: %s\n", SDL_GetError());
    throw -1;
  }
}



void Surface::flip() {
  if (SDL_Flip(surface_) != 0) {
    printf("Unable to flip display buffers: %s\n", SDL_GetError());
    throw -1;
  }
}



void Surface::drawRectangle(int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

  if (rectangleRGBA(surface_, x1, y1, x2, y2, r, g, b, a) != 0)
    throw -1;
}



void Surface::drawLine(int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

  if (aalineRGBA(surface_, x1, y1, x2, y2, r, g, b, a) != 0)
    throw -1;
}



void Surface::drawAaPolygon(const std::vector<int16_t>& x, const std::vector<int16_t>& y,
                      uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

  const int n(min(x.size(), y.size()));
  // Data(): returns pointer to the underlying array (C++11) (OK even if empty).
  if (aapolygonRGBA(surface_, x.data(), y.data(), n, r, g, b, a) != 0)
    throw -1;
}



void Surface::drawFilledPolygon(const std::vector<int16_t>& x, std::vector<int16_t>& y,
                            uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

  const int n(min(x.size(), y.size()));
  // Data(): returns pointer to the underlying array (C++11) (OK even if empty).
  if (filledPolygonRGBA(surface_, x.data(), y.data(), n, r, g, b, a) != 0)
    throw -1;
}

