/* 
 * File:   Points.cpp
 * Author: michael
 * 
 * Created on 23. mai 2013, 13:13
 */

#include <string>

#include "Constants.h"
#include "Score.h"
#include "Surface.h"


namespace Score {
  
  float points_(1000);
  
  
  void addPoints(float points) {
    points_ += points;
    if (points_ <= 0)
      points_ = 0;
  }
  
  
  float getPoints() {
    return points_;
  }
  
  
  void render(Surface& displaySurf) {
    const std::string labelL1("Score: " + std::to_string(int(points_)));
    Surface textSurf1(labelL1, 0, 0, 0, BOLDFONT, 14);
    displaySurf.blit(textSurf1, 810, 500);
  }
  
}

