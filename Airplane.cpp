/* 
 * File:   Airplane.cpp
 * Author: michael
 * 
 * Created on 25. mars 2013, 21:39
 */

#include <iostream>

#include <cmath>
#include <string>

#include "Airplane.h"
#include "Cloud.h"
#include "Constants.h"
#include "ForbiddenZone.h"
#include "Surface.h"



Airplane::Airplane(const int identification, const int altitude, const float cape,
                   const int velocity, const Point initialPosition)
:
Entity(cape, velocity, initialPosition), // Parent constructor.
identification_(identification), // Flight number.
altitude_(altitude)
{
}



void Airplane::compute() {
    
  // This entity can move, we have to compute it.
  computeMovement();
  
}



void Airplane::checkForCollisionDispatch(const Entity& entity) const {
  entity.checkForCollision(this);
}



void Airplane::checkForCollision(const Airplane* airplane) const {
  
  Point airplanePos = airplane->getPosition();
  
  // Collision if the distance between 2 airplanes is smaller than DMINCOL.
  if (std::sqrt(std::pow(airplanePos.x - refPos_.x, 2) +
                std::pow(airplanePos.y - refPos_.y, 2)) < DMINCOL)
    std::cout << "Collision with an airplane." << std::endl;
}



void Airplane::checkForCollision(const ForbiddenZone* forbiddenZone) const {
  // Terminate the simulation if the airplane is inside a forbidden zone.
  if (forbiddenZone->isInside(refPos_))
    std::cout << "Collision with a forbidden zone." << std::endl;
}



void Airplane::checkForCollision(const Cloud* cloud) const {
  // Remove points if the airplane is inside a cloud.
  if (cloud->isInside(refPos_))
    std::cout << "Collision with a cloud." << std::endl;
  
}



struct Point Airplane::getPosition() const {
  return refPos_;
}



void Airplane::render(Surface& displaySurf) const {
    
  const std::string labelLine1 = "ID " + std::to_string(identification_);
  const std::string labelLine2 = std::to_string(altitude_) + "   " + std::to_string(int(cape_));
  const std::string labelLine3 = std::to_string(velocity_);
  // SDL_ttf is a text rendering engine, not a text layout engine.
  // So it doesn't print "\n".
  
  Surface textSurf1(labelLine1, 255, 0, 0,
                   "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf", 14);
  Surface textSurf2(labelLine2, 0, 0, 0,
                   "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 14);
  Surface textSurf3(labelLine3, 0, 0, 0,
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
  displaySurf.blit(airplaneSurf, int16_t(refPos_.x-10), int16_t(refPos_.y-10));
  displaySurf.blit(textSurf1, int16_t(refPos_.x-20), int16_t(refPos_.y+15));
  displaySurf.blit(textSurf2, int16_t(refPos_.x-20), int16_t(refPos_.y+30));
  displaySurf.blit(textSurf3, int16_t(refPos_.x-20), int16_t(refPos_.y+45));
  
}

