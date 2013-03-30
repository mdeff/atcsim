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
identification_(identification), // Flight number.
altitude_(altitude),
cape_(cape),
velocity_(velocity),
x_(x), y_(y) // Position.
{
}



Airplane::~Airplane() {
  // Default: call base class'es destructor and destructors of all members.
}



void Airplane::loop() {
}



void Airplane::render(Surface& displaySurf) {
    
  const string labelLine1 = "ID " + to_string(identification_);
  const string labelLine2 = to_string(altitude_) + "   " + to_string(cape_);
  // SDL_ttf is a text rendering engine, not a text layout engine.
  // So it doesn't print "\n".
  
  Surface textSurf1(labelLine1, 255, 0, 0,
                   "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf", 14);
  Surface textSurf2(labelLine2, 0, 0, 0,
                   "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 14);
          
  // Create a new suface with the size of the airplane image.
  Surface airplaneSurf(21, 21);
   
  // Airplane is actually a grey 21x21 pixels rectangle with diagonals.
  const int grey(100);
  airplaneSurf.drawRectangle(0, 0, 20, 20, grey, grey, grey, 255);
  airplaneSurf.drawRectangle(1, 1, 19, 19, grey, grey, grey, 255);
  airplaneSurf.drawLine(0, 0, 20, 20, grey, grey, grey, 255);
  airplaneSurf.drawLine(0, 20, 20, 0, grey, grey, grey, 255);
          
  // Draw the airplane and his related text informations at it's actual position.
  displaySurf.blit(airplaneSurf, x_-10, y_-10);
  displaySurf.blit(textSurf1, x_-20, y_+15);
  displaySurf.blit(textSurf2, x_-20, y_+30);
  
}



void Airplane::cleanup() {
  
}

