/* 
 * File:   Game.cpp
 * Author: michael
 * 
 * Created on 23. mars 2013, 17:54
 */

#include "Airplane.h"
#include "Airway.h"
#include "Cloud.h"
#include "Constants.h"
#include "Entity.h"
#include "ForbiddenZone.h"
#include "Framerate.h"
#include "Game.h"
#include "Surface.h"
#include "Types.h"



Game::Game()
: Events(), // Parent constructor.
window_(1000, 551, 32),
background_("background.bmp"), // Load the background image.
sidePanel_(200, 551),
running_(true),
score_(1000),
gameFieldWidth_(background_.getWidth()),
gameFieldHeight_(background_.getHeight()),
entities_() {

  // Add airplanes, airways, forbidden zones and clouds to the heterogeneous collection.
  entities_.push_back(std::unique_ptr<Entity > (
          new Airway({0, 250, 300,   0},
                     {0,   0, 200, 300})));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airway({  0, 160, 260, 310, 290,   0},
                     {500, 350, 350, 450, 551, 551})));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airway({450, 800, 800, 650, 630, 480},
                     {  0,   0, 350, 330, 190, 150})));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airway({470, 670, 440},
                     {551, 551, 330})));
  
  entities_.push_back(std::unique_ptr<Entity > (
          new ForbiddenZone({260, 360, 360, 260},
                            {150, 150, 250, 250})));
  entities_.push_back(std::unique_ptr<Entity > (
          new ForbiddenZone({480, 670, 690, 780, 670, 650},
                            {150, 130,  20, 120, 130, 330})));
  
  entities_.push_back(std::unique_ptr<Entity > (
          new Cloud({540, 620, 770, 790, 700, 580},
                    {400, 350, 400, 500, 540, 500}, 124.2f, 200)));
  
  entities_.push_back(std::unique_ptr<Entity > (
          new Airplane(1, "AA293", 8000, 260.4f, 800, CardinalPoint(N), CardinalPoint(S))));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airplane(2, "LX8829", 9811, 90.3f, 600, CardinalPoint(S), CardinalPoint(W))));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airplane(3, "DLH22", 7510, 166.8f, 700, CardinalPoint(E), CardinalPoint(S))));
  entities_.push_back(std::unique_ptr<Entity > (
          new Airplane(4, "BER120", 7440, 20.3f, 400, CardinalPoint(W), CardinalPoint(E))));
  
  // Draw the side panel background (white with black outline).
  sidePanel_.drawFilledRectangle(0, 0, 199, 550, 255, 255, 255, 255);
  sidePanel_.drawRectangle(0, 0, 199, 550, 0, 0, 0, 255);
  sidePanel_.drawRectangle(1, 1, 198, 549, 0, 0, 0, 255);
  sidePanel_.drawRectangle(2, 2, 197, 548, 0, 0, 0, 255);
  sidePanel_.drawLine(0, 480, 199, 480, 0, 0, 0, 255);
  sidePanel_.drawLine(0, 481, 199, 481, 0, 0, 0, 255);
  sidePanel_.drawLine(0, 482, 199, 482, 0, 0, 0, 255);
  
}



Game::~Game() noexcept(true) {
  // Default: call base class'es destructor and destructors of all members.
}



bool Game::getState() const {
  return running_;
}



void Game::compute() {

  // Compute the framerate.
  Framerate::compute();
  
  // Reset entities status and simulated data.
  for (auto& entity : entities_) {
    entity->resetStatus();
    entity->resetSimulation();
  }

  // Do necessary computations for each entity, mostly movement calculation.
  for (auto& entity : entities_) {
    entity->compute(realPosition, gameFieldWidth_, gameFieldHeight_);
  }

  // Check for collisions between entities.
  for (auto& entity1 : entities_) {
    for (auto& entity2 : entities_) {
      if (entity1 != entity2) {
        entity1->checkForCollisionDispatch(*entity2, realPosition);
      }
    }
  }

  // Check for future collisions (future is NTICKSCOL long).  
  for (unsigned int i(NTICKSCOL); i > 0; --i) {
    
    // Simulate entities movements.
    for (auto& entity : entities_) {
      entity->compute(simPosition, gameFieldWidth_, gameFieldHeight_);
    }
  
    // Simulate collision checking.
    for (auto& entity1 : entities_) {
      for (auto& entity2 : entities_) {
        if (entity1 != entity2) {
          entity1->checkForCollisionDispatch(*entity2, simPosition);
        }
      }
    }
  }
  
  // Check airplane status to add / remove points or terminate the game.
  const struct AirplaneStatus* status;
  for (auto& entity : entities_) {
    status = entity->getStatus();
    if (status->outRight) {
      score_ += 100.0f;
    } if (status->outWrong) {
      score_ -= 100.0f;
    } if (status->airplaneRealCollision) {
//      running_ = false;
//      score_ -= 100.0f;
    } if (status->forbiddenZoneRealCollision) {
//      running_ = false;
//      score_ -= 100.0f;
    } if (status->airwayRealCollision) {
      score_ -= 1.0f;
    } if (status->cloudRealCollision) {
      score_ -= 0.1f;
    }
  }
  
  // No negative score.
  if (score_ <= 0.0f)
    score_ = 0.0f;
  
}



void Game::render() {

  // Set the window title.
  const std::string windowTitle = "Air Traffic Control simulator, CS-118 project, EPFL"
                                  "\t" + std::to_string(Framerate::getFPS()) + " FPS";
  SDL_WM_SetCaption(windowTitle.c_str(), nullptr);
  
  // Blit the background image on the window.
  window_.blit(background_, 0, 0);
  
  // Blit the side panel surface on the window.
  window_.blit(sidePanel_, 800, 0);
  
  // Render the score on the window.
  const std::string labelL1("Score: " + std::to_string(int(score_)));
  Surface textSurf1(labelL1, 0, 0, 0, BOLDFONT, 14);
  window_.blit(textSurf1, 810, 500);
  
  // Render the airplanes, forbidden zones and clouds on the window.
  for (auto& entity : entities_) {
    entity->render(window_);
  }
  
  // Flip the video buffers.
  window_.flip();

}



void Game::onExit() {
  running_ = false;
}



void Game::onLButtonDown(int mX, int mY) {
  
  Entity* selectedEntity(nullptr);
  Entity* clickedEntity(nullptr);
  
  for (auto& entity : entities_) {
    
    // Get the selected entity.
    if (entity->getSelected()) {
      // Convert from std::unique_ptr<Entity> to Entity*.
      selectedEntity = &(*entity);
    }
    
    // Check if the click was on an entity.
    if (entity->isInside(Point(mX, mY), realPosition, true)) {
      clickedEntity = &(*entity);
    }
  }
  
  // An entity was selected and we click somwhere : deselect it and change cape.
  if (selectedEntity != nullptr) {
    selectedEntity->setSelected(false);
    selectedEntity->setTargetCape(Point(mX, mY));
    
  // Else if another entity was clicked : select it.
  } else if (clickedEntity != nullptr) {
      clickedEntity->setSelected(true);
  }
  
}



void Game::handleEvent(SDL_Event& event) {
  Events::handleEvent(event);
}

