/* 
 * File:   Game.cpp
 * Author: michael
 * 
 * Created on 23. mars 2013, 17:54
 */

#include <iostream>


#include "Airplane.h"
#include "Cloud.h"
#include "Constants.h"
#include "Entity.h"
#include "ForbiddenZone.h"
#include "FPS.h"
#include "Game.h"
#include "Surface.h"



Game::Game()
: Events(), // Parent constructor.
window_(1000, 551, 32),
background_("background.bmp"), // Load the background image.
sidePanel_(200, 551),
running_(true),
gameFieldWidth_(background_.getWidth()),
gameFieldHeight_(background_.getHeight()),
entities_() {

  // Add airplanes, forbidden zones and clouds to the heterogeneous collection.
  entities_.push_back(std::unique_ptr<Entity > (
          new Airplane(1, 1111, 8000, 10.0f, 800, Point(40, 400))));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airplane(2, 222222222, 9811, 90.3f, 600, Point(200, 400))));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airplane(3, 33, 7510, -12.2f, 700, Point(350, 250))));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airplane(4, 44444, 7440, 180.0f, 400, Point(750, 300))));

  entities_.push_back(std::unique_ptr<Entity > (
          new ForbiddenZone({0, 250, 400,   0},
                            {0,   0, 200, 200})));
  entities_.push_back(std::unique_ptr<Entity > (
          new ForbiddenZone({0,   200, 400, 450, 450,   0},
                            {500, 350, 350, 450, 551, 551})));
  entities_.push_back(std::unique_ptr<Entity > (
          new ForbiddenZone({500, 800, 800, 600},
                            {  0,   0, 250, 200})));

  entities_.push_back(std::unique_ptr<Entity > (
          new Cloud({540, 620, 770, 790, 700, 580},
                    {400, 350, 400, 500, 540, 500}, 124.2f, 200)));

  // Draw the side panel background (white with black outline).
  sidePanel_.drawFilledRectangle(0, 0, 199, 550, 255, 255, 255, 255);
  sidePanel_.drawRectangle(0, 0, 199, 550, 0, 0, 0, 255);
  sidePanel_.drawRectangle(1, 1, 198, 549, 0, 0, 0, 255);
  sidePanel_.drawRectangle(2, 2, 197, 548, 0, 0, 0, 255);
  
}



Game::~Game() throw () {
  // Default: call base class'es destructor and destructors of all members.
}



bool Game::getState() const {
  return running_;
}



void Game::compute() {

  // Compute the framerate.
  FPS::compute();

  // Do necessary computations for the airplanes, forbidden zones and clouds.
  // Mostly movement calculation.
  for (auto& entity : entities_) {
    entity->compute(realPosition, gameFieldWidth_, gameFieldHeight_);
  }

  std::cout << "Check collisions." << std::endl;
  // Check for collisions between entities.
  for (auto& entity1 : entities_) {
    for (auto& entity2 : entities_) {
      if (entity1 != entity2) {
        entity1->checkForCollisionDispatch(*entity2, realPosition);
      }
    }
  }

  // Check for future collisions.
  
  // Reset entities simulated positions.
  for (auto& entity : entities_) {
    entity->resetSimulation();
  }
  
  for (unsigned int i(NTICKSCOL); i > 0; --i) {
    
    // Simulate entities movements.
    for (auto& entity : entities_) {
      entity->compute(simPosition, gameFieldWidth_, gameFieldHeight_);
    }
  
    // Simulate collision cWINDOWXSIZEhecking.
    for (auto& entity1 : entities_) {
      for (auto& entity2 : entities_) {
        if (entity1 != entity2) {
          entity1->checkForCollisionDispatch(*entity2, simPosition);
        }
      }
    }
  }
}



void Game::render() {

  // Set the window title.
  const std::string windowTitle = "Air Traffic Control simulator, CS-118 project, EPFL"
                                  "\t" + std::to_string(FPS::getFPS()) + " FPS";
  SDL_WM_SetCaption(windowTitle.c_str(), nullptr);
  
  // Blit the background image on the window.
  window_.blit(background_, 0, 0);
  
  // Blit the side panel surface on the window.
  window_.blit(sidePanel_, 800, 0);
  
  // Render the airplanes, forbidden zones and clouds on the window.
  for (auto& entity : entities_) {
    entity->render(window_);
  }
  
  // Flip the window video buffers.
  window_.flip();

}



void Game::onExit() {
  running_ = false;
}



void Game::onLButtonDown(int mX, int mY) {
  // Check if the click was on an airplane
  for (auto& entity1 : entities_) {
    if (entity1->checkMouseClick(mX, mY)) {
      entity1->select(!entity1->isSelected());
      for (auto& entity2 : entities_) {
        if (entity1 != entity2) {
          entity2->select(false);
        }
      }
      break;
    }
  }
}



void Game::handleEvent(SDL_Event& event) {
  Events::handleEvent(event);
}

