/* 
 * File:   Airplane.cpp
 * Author: michael
 * 
 * Created on 25. mars 2013, 21:39
 */

#include <string>
#include "Airplane.h"
#include "Surface.h"

using namespace std;

Airplane::Airplane(const int identification, const int altitude, const int cape,
                   const int velocity, const int x, const int y) 
  :
  IEntity(), // Parent constructor.
  identification_(identification),   // Flight number.
  altitude_(altitude),
  cape_(cape),
  velocity_(velocity),
  x_(x), y_(y)                       // Position.
{
  
  textFont_ = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 12);
  
  textColor_.r = 255;        // Black
  textColor_.g = 255;
  textColor_.b = 255;
}


Airplane::~Airplane() {
  TTF_CloseFont(textFont_);
  SDL_FreeSurface(textSurf_);
  // Default: call base class'es destructor and destructors of all members.
}


void Airplane::loop() {
}

void Airplane::render(SDL_Surface* displaySurf) {
  
  SDL_Surface* airplaneSurf;
  string label;
  
  label = to_string(identification_) + "\n";
  label += to_string(altitude_) + to_string(cape_);
  
  textSurf_ = TTF_RenderText_Solid(textFont_, label.c_str(), textColor_);
  
  if (textSurf_ == NULL)
    throw -1;  // TODO
  
  // Airplane is actually a grey rectangle.
  rectangleRGBA(airplaneSurf, 0, 0, 10, 10, 128, 128, 128, 0);
  
  if (airplaneSurf == NULL)
    throw -1;  // TODO
  
  Surface::draw(displaySurf, airplaneSurf, x_, y_);
  Surface::draw(displaySurf, textSurf_, x_, y_+20);
  
  SDL_FreeSurface(airplaneSurf);
}

void Airplane::cleanup() {
  
}