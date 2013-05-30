/* 
 * File:   Airplane.cpp
 * Author: michael
 * 
 * Created on 25. mars 2013, 21:39
 */

#include <cmath>
#include <string>

#include "SDL/SDL_mouse.h"

#include "Airplane.h"
#include "Airway.h"
#include "Cloud.h"
#include "Constants.h"
#include "ForbiddenZone.h"
#include "Surface.h"



namespace ATCsim {  // Project ATCsim namespace.



Airplane::Airplane(unsigned int number, std::string identification, unsigned int
                   altitude, float cape, unsigned int velocity,
                   CardinalPoint in, CardinalPoint out)
:
Entity(cape, velocity, in.getPosition()), // Parent constructor.
number_(number),
identification_(identification), // Flight number.
altitude_(altitude),
in_(in),
out_(out),
hidden_(false)
{
}



void Airplane::compute(PosTypes posType, int gameFieldWidth, int gameFieldHeight) {
    
  // Nothing to compute if hidden.
  if (hidden_)
    return;
  
  // The cape of this entity can change (user input) : compute it.
  if (posType == realPosition)
    updateCape();
  
  // Select the position from which to test.
  const Point* pos(getPosition(posType));
  
  // Check if we are not out-of-field (not if already hidden).
  // Before the edge for real position (otherwise airplane would be half out).
  if (posType == realPosition && (
          pos->x > gameFieldWidth -14 || pos->x < 14 ||
          pos->y > gameFieldHeight-14 || pos->y < 14)) {
        
    hidden_ = true;
    status_.outWrong = true;
    
    if (pos->x > 250 && pos->x < 450 && pos->y < 14) {
      if (out_.cardinalPoint == N) {
        status_.outRight = true;
        status_.outWrong = false;
      }
    } else if (pos->x > 290 && pos->x < 470 && pos->y > gameFieldHeight-14) {
      if (out_.cardinalPoint == S) {
        status_.outRight = true;
        status_.outWrong = false;
      }
    } else if (pos->x > 670 && pos->x < 800 && pos->y > gameFieldHeight-14) {
      if (out_.cardinalPoint == E) {
        status_.outRight = true;
        status_.outWrong = false;
      }
    } else if (pos->y > 350 && pos->y < 551 && pos->x > gameFieldWidth-14) {
      if (out_.cardinalPoint == E) {
        status_.outRight = true;
        status_.outWrong = false;
      }
    } else if (pos->y > 300 && pos->y < 500 && pos->x < 14) {
      if (out_.cardinalPoint == W) {
        status_.outRight = true;
        status_.outWrong = false;
      }
    }
    
  // On edge for simulated position (trajectory line until edges).
  } else if (posType == simPosition && (
          pos->x > gameFieldWidth -0 || pos->x < 0 ||
          pos->y > gameFieldHeight-0 || pos->y < 0)) {
    
  } else {
    // This entity can move : compute it.
    computeMovement(posType);
  }
}



void Airplane::checkForCollisionDispatch(Entity& entity, PosTypes posType) const {
  // Double dispatching (visitor pattern).
  entity.checkForCollision(this, posType);
}


  
void Airplane::checkForCollision(const Airplane* airplane, PosTypes posType) {
    
  // No collisions if hidden.
  if (hidden_)
    return;
  
  const Point* airplane1Pos = getPosition(posType);
  const Point* airplane2Pos = airplane->getPosition(posType);
  
  // Collision if the distance between 2 airplanes is smaller than DMINCOL.
  if (std::sqrt(std::pow(airplane1Pos->x - airplane2Pos->x, 2) +
          std::pow(airplane1Pos->y - airplane2Pos->y, 2)) < DMINCOL &&
          static_cast<unsigned int>(std::abs(int(altitude_) -
          int(airplane->getAltitude()))) < DMINVERTCOL) {
    switch (posType) {
      case simPosition:
        status_.airplaneSimCollision = true;
        break;
      case realPosition:
      default:
        status_.airplaneRealCollision = true;
    }
  }
}



void Airplane::checkForCollision(const ForbiddenZone* forbiddenZone, PosTypes posType) {

  // No collisions if hidden.
  if (hidden_)
    return;
  
  if (forbiddenZone->isInside(*getPosition(posType), posType, false)) {
    switch (posType) {
      case simPosition:
        status_.forbiddenZoneSimCollision = true;
        break;
      case realPosition:
      default:
        status_.forbiddenZoneRealCollision = true;
    }
  }
}



void Airplane::checkForCollision(const Airway* airway, PosTypes posType) {

  // No collisions if hidden.
  if (hidden_)
    return;
  
  if (airway->isInside(*getPosition(posType), posType, false)) {
    switch (posType) {
      case simPosition:
        status_.airwaySimCollision = true;
        break;
      case realPosition:
      default:
        status_.airwayRealCollision = true;
    }
  }
}



void Airplane::checkForCollision(const Cloud* cloud, PosTypes posType) {

  // No collisions if hidden.
  if (hidden_)
    return;
  
  if (cloud->isInside(*getPosition(posType), posType, false)) {
    switch (posType) {
      case simPosition:
        status_.cloudSimCollision = true;
        break;
      case realPosition:
      default:
        status_.cloudRealCollision = true;
    }
  }  
}



unsigned int Airplane::getAltitude() const {
  return altitude_;
}



bool Airplane::isInside(Point point, PosTypes posType, bool mouse) const {
  
  // Cannot be inside if hidden.
  if (hidden_)
    return false;
  
  // Select the position from which to test.
  const Point* position(getPosition(posType));
  
  if (point.x >= position->x-10 && point.x <= position->x+10 &&
      point.y >= position->y-10 && point.y <= position->y+10)
    return true;
  else
    return false;
  
}



void Airplane::render(Surface& displaySurf) const {
  
  // Print airplane informations on the side panel.
  renderSidePanelInfo(displaySurf);
  
  // Don't render airplane if hidden.
  if (hidden_)
    return;
  
  // Airplane labels.
  const std::string labelL1(identification_);
  const std::string labelL2(std::to_string(altitude_) + "m   " +
                            std::to_string(int(std::round(currentCape_))) + "°");
  const std::string labelL3(std::to_string(velocity_) + "km/h");
  // SDL_ttf is a text rendering engine, not a text layout engine.
  // So it doesn't print "\n".
  
  // Default text color is black, become orange if warning, red if danger.
  uint8_t red(0), green(0), blue(0);
  if (status_.airplaneSimCollision || status_.forbiddenZoneSimCollision) {
    red = 255;
  } else if (status_.airwaySimCollision || status_.cloudSimCollision) {
    red = 255;
    green = 128;
  }
  
  // Create surfaces out of text strings.
  Surface textSurf1(labelL1, red, green, blue, BOLDFONT, 14);
  Surface textSurf2(labelL2, 0, 0, 0, STDFONT, 14);
  Surface textSurf3(labelL3, 0, 0, 0, STDFONT, 14);
  
  // Change airplane color if selected by user.
  red = green = blue = 100;
  if (selected_) {
    red = 150;
    green = 0;
    blue = 150;
  }
  
  // Airplane is actually a 21x21 pixels rectangle with diagonals.
  Surface airplaneSurf(21, 21);
  airplaneSurf.drawRectangle(0, 0, 20, 20, red, green, blue, 255);
  airplaneSurf.drawRectangle(1, 1, 19, 19, red, green, blue, 255);
  airplaneSurf.drawLine(0, 0, 20, 20, red, green, blue, 255);
  airplaneSurf.drawLine(0, 20, 20, 0, red, green, blue, 255);
  
  // Draw the airplane and his related text informations at it's actual position.
  displaySurf.blit(airplaneSurf, int16_t(realPosition_.x-10), int16_t(realPosition_.y-10));
  displaySurf.blit(textSurf1,    int16_t(realPosition_.x-20), int16_t(realPosition_.y+15));
  displaySurf.blit(textSurf2,    int16_t(realPosition_.x-20), int16_t(realPosition_.y+30));
  displaySurf.blit(textSurf3,    int16_t(realPosition_.x-20), int16_t(realPosition_.y+45));
  
  // Draw a line which indicates the predicted airplane trajectory.
  traceLineFromAirplane(displaySurf, simPosition_, red, green, blue);
  
  // Draw a line which indicates the new cape a user would choose.
  if (selected_) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    traceLineFromAirplane(displaySurf, Point(x,y), red, green, blue);
  }
    
}



void Airplane::renderSidePanelInfo(Surface& displaySurf) const {
  
  const std::string labelL1("Airplane " + identification_);
  const std::string labelL2("in: " + in_.toString() + "    out: " + out_.toString());
  std::string labelL3("Status: OK");
  
  // Default text color is black, become red if warning.
  uint8_t redL2(0), greenL2(160);
  
  if (hidden_) {
    labelL3 = "Airplane out of area.";
  } else if (status_.airplaneSimCollision) {
    labelL3 = "Danger: airplane collision !";
    redL2 = 255;
    greenL2 = 0;
  } else if (status_.forbiddenZoneSimCollision) {
    labelL3 = "Danger: forbidden zone !";
    redL2 = 255;
    greenL2 = 0;
  } else if (status_.airwaySimCollision) {
    labelL3 = "Warning: out of airway !";
    redL2 = 255;
    greenL2 = 128;
  } else if (status_.cloudSimCollision) {
    labelL3 = "Warning: turbulence zone !";
    redL2 = 255;
    greenL2 = 128;
  } else if (int(currentCape_) != int(targetCape_)) {
    labelL3 = "Airplane turning !";
  }
  
  Surface textSurf1(labelL1, 0, 0, 0, BOLDFONT, 14);
  Surface textSurf2(labelL2, 0, 0, 0, STDFONT, 14);
  Surface textSurf3(labelL3, redL2, greenL2, 0, STDFONT, 14);
  
  displaySurf.blit(textSurf1, 810, int16_t((number_-1) * 70 + 20));
  displaySurf.blit(textSurf2, 820, int16_t((number_-1) * 70 + 40));
  displaySurf.blit(textSurf3, 820, int16_t((number_-1) * 70 + 60));
}



void Airplane::traceLineFromAirplane(Surface& displaySurf, Point endPoint,
        uint8_t red, uint8_t green, uint8_t blue) const {

  const float xPred(endPoint.x - realPosition_.x);
  const float yPred(endPoint.y - realPosition_.y);
  
  Surface predTrajectorySurf(
          int16_t(std::abs(xPred))+1,
          int16_t(std::abs(yPred))+1);
  
  predTrajectorySurf.drawLine(
          int16_t(xPred>0?0:-xPred),
          int16_t(yPred>0?0:-yPred),
          int16_t(xPred>0?xPred:0),
          int16_t(yPred>0?yPred:0),
          red, green, blue, 255);
  
  displaySurf.blit(predTrajectorySurf,
          int16_t(xPred>0?realPosition_.x:realPosition_.x+xPred),
          int16_t(yPred>0?realPosition_.y:realPosition_.y+yPred));
}



}  // End of project ATCsim namespace.

