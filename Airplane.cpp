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



Airplane::Airplane(unsigned int number, unsigned int identification, unsigned int
                   altitude, float cape, int velocity, Point initialPosition)
:
Entity(cape, velocity, initialPosition), // Parent constructor.
number_(number),
identification_(identification), // Flight number.
altitude_(altitude),
predictedCollision_()
{
}



void Airplane::compute(enum PosType posType, int gameFieldWidth, int gameFieldHeight) {
    
  // This entity can move, we have to compute it.
  this->computeMovement(posType, gameFieldWidth, gameFieldHeight);
  
}



void Airplane::checkForCollisionDispatch(Entity& entity, enum PosType posType) const {
  entity.checkForCollision(this, posType);
}



void Airplane::checkForCollision(const Airplane* airplane, enum PosType posType) {
    
  const Point* airplane1Pos = this->getPosition(posType);
  const Point* airplane2Pos = airplane->getPosition(posType);
  
  // Collision if the distance between 2 airplanes is smaller than DMINCOL.
  if (std::sqrt(std::pow(airplane1Pos->x - airplane2Pos->x, 2) +
          std::pow(airplane1Pos->y - airplane2Pos->y, 2)) < DMINCOL &&
          static_cast<unsigned int>(std::abs(int(altitude_) -
          int(airplane->getAltitude()))) < DMINVERTCOL) {
    switch (posType) {
      case realPosition:
        std::cout << "Collision with an airplane." << std::endl;
        break;
      case simPosition:
        predictedCollision_.airplane = true;
    }
  }
    
}



void Airplane::checkForCollision(const ForbiddenZone* forbiddenZone, enum PosType posType) {

  // Terminate the simulation if the airplane is inside a forbidden zone.
    
  if (forbiddenZone->isInside(*this->getPosition(posType), posType)) {
    switch (posType) {
      case realPosition:
        std::cout << "Collision with a forbidden zone." << std::endl;
        break;
      case simPosition:
        predictedCollision_.forbiddenZone = true;
    }
  }
}



void Airplane::checkForCollision(const Cloud* cloud, enum PosType posType) {

  // Remove points if the airplane is inside a cloud.
  
  if (cloud->isInside(*this->getPosition(posType), posType)) {
    switch (posType) {
      case realPosition:
        std::cout << "Collision with a cloud." << std::endl;
        break;
      case simPosition:
        predictedCollision_.cloud = true;
    }
  }  
}



const struct Point* Airplane::getPosition(enum PosType posType) const {
  const struct Point* position;
  switch (posType) {
    case realPosition:
      position = &realPosition_;
      break;
    case simPosition:
      position = &simPosition_;
  }
  return position;
}



unsigned int Airplane::getAltitude() const {
  return altitude_;
}



void Airplane::resetSimulation() {
  Entity::resetSimulation();
  this->predictedCollision_.airplane      = false;
  this->predictedCollision_.cloud         = false;
  this->predictedCollision_.forbiddenZone = false;
}



void Airplane::render(Surface& displaySurf) const {
    
  const std::string labelLine1 = "ID " + std::to_string(identification_);
  const std::string labelLine2 = std::to_string(altitude_) + "   " + std::to_string(int(cape_));
  const std::string labelLine3 = std::to_string(velocity_);
  // SDL_ttf is a text rendering engine, not a text layout engine.
  // So it doesn't print "\n".
  
  // Default text color is black, become red if warning.
  uint8_t redColorLine1 = 0;
  if (predictedCollision_.cloud || predictedCollision_.forbiddenZone || predictedCollision_.airplane)
    redColorLine1 = 255;
  
  Surface textSurf1(labelLine1, redColorLine1, 0, 0, BOLDFONT, 14);
  Surface textSurf2(labelLine2, 0, 0, 0, STDFONT, 14);
  Surface textSurf3(labelLine3, 0, 0, 0, STDFONT, 14);
  
  // Create a new suface with the size of the airplane image.
  Surface airplaneSurf(21, 21);
  
  // Airplane is actually a grey 21x21 pixels rectangle with diagonals.
  const int grey(100);
  airplaneSurf.drawRectangle(0, 0, 20, 20, grey, grey, grey, 255);
  airplaneSurf.drawRectangle(1, 1, 19, 19, grey, grey, grey, 255);
  airplaneSurf.drawLine(0, 0, 20, 20, grey, grey, grey, 255);
  airplaneSurf.drawLine(0, 20, 20, 0, grey, grey, grey, 255);
  
  // Draw the airplane and his related text informations at it's actual position.
  displaySurf.blit(airplaneSurf, int16_t(realPosition_.x-10), int16_t(realPosition_.y-10));
  displaySurf.blit(textSurf1, int16_t(realPosition_.x-20), int16_t(realPosition_.y+15));
  displaySurf.blit(textSurf2, int16_t(realPosition_.x-20), int16_t(realPosition_.y+30));
  displaySurf.blit(textSurf3, int16_t(realPosition_.x-20), int16_t(realPosition_.y+45));
  
  // Print airplane informations on the side panel.
  this->printSidePanelInfo(displaySurf);
}



void Airplane::printSidePanelInfo(Surface& displaySurf) const {
  
  const std::string labelLine1 = "Airplane ID " + std::to_string(identification_);
  std::string labelLine2 = "OK";
  
  // Default text color is black, become red if warning.
  uint8_t redColorLine2 = 0;
  uint8_t greenColorLine2 = 128;
  
  if (predictedCollision_.cloud) {
    labelLine2 = "Warning: turbulence zone !";
    redColorLine2 = 255;
    greenColorLine2 = 128;
  }
  if (predictedCollision_.forbiddenZone) {
    labelLine2 = "Danger: forbidden zone !";
    redColorLine2 = 255;
    greenColorLine2 = 0;
  }
  if (predictedCollision_.airplane) {
    labelLine2 = "Danger: airplane collision !";
    redColorLine2 = 255;
    greenColorLine2 = 0;
  }
  
  Surface textSurf1(labelLine1, 0, 0, 0, BOLDFONT, 14);
  Surface textSurf2(labelLine2, redColorLine2, greenColorLine2, 0, STDFONT, 14);
  
  displaySurf.blit(textSurf1, 810, int16_t((number_-1) * 70 + 20));
  displaySurf.blit(textSurf2, 820, int16_t((number_-1) * 70 + 40));
  
}

