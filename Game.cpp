/* 
 * File:   Game.cpp
 * Author: michael
 * 
 * Created on 23. mars 2013, 17:54
 */

#include "Airway.h"
#include "Constants.h"
#include "Entity.h"
#include "Framerate.h"
#include "Game.h"
#include "Parser.h"
#include "Surface.h"



namespace ATCsim {  // Project ATCsim namespace.



Game::Game(std::string configFileName)
: Events(), // Parent constructor.
window_(1000, 551, 32),
background_("background.bmp"), // Load the background image.
sidePanel_(200, 551),
state_(run),
score_(1000),
nActiveAirplanes_(4),
dialogBox_(false),
gameOver_(false),
gameFieldWidth_(background_.getWidth()),
gameFieldHeight_(background_.getHeight()),
entities_() {
  
  // Add airways to the entities heterogeneous collection.
  // Airways are not defined in the configuration file because other things
  // depend on it, like airplane input / output cardinal points.
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
  
  // Extract entities (forbidden zones, clouds and airplanes) configurations
  // from a configuration file.
  Parser parser(configFileName);
  parser.extract(entities_);
  
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



Game::GameStates Game::getState() const {
  return state_;
}



void Game::compute() {

  // Compute the framerate.
  Framerate::compute();
  
  // No more to compute if we are curently showing a dialog box.
  // We don't want entities to move in the background.
  if (dialogBox_)
    return;
  
  // Reset entities status and simulated data.
  for (auto& entity : entities_) {
    entity->resetStatus();
    entity->resetSimulation();
  }

  // Do necessary computations for each entity, mostly movement calculation.
  for (auto& entity : entities_) {
    entity->compute(Entity::realPosition, gameFieldWidth_, gameFieldHeight_);
  }
  
  // Check for collisions between entities.
  for (auto& entity1 : entities_) {
    for (auto& entity2 : entities_) {
      if (entity1 != entity2) {
        entity1->checkForCollisionDispatch(*entity2, Entity::realPosition);
      }
    }
  }
  
  // Check for future collisions (future is NTICKSCOL long).  
  for (unsigned int i(NTICKSCOL); i > 0; --i) {
    
    // Simulate entities movements.
    for (auto& entity : entities_) {
      entity->compute(Entity::simPosition, gameFieldWidth_, gameFieldHeight_);
    }
  
    // Simulate collision checking.
    for (auto& entity1 : entities_) {
      for (auto& entity2 : entities_) {
        if (entity1 != entity2) {
          entity1->checkForCollisionDispatch(*entity2, Entity::simPosition);
        }
      }
    }
  }
  
  // Check airplane status to add / remove points or terminate the game.
  const Entity::AirplaneStatus* status;
  for (auto& entity : entities_) {
    status = entity->getStatus();
    if (status->outRight) {
      score_ += 500.0f;
      --nActiveAirplanes_;
      if (nActiveAirplanes_ == 0)
        dialogBox_ = true;
    } if (status->outWrong) {
      score_ -= 100.0f;
      --nActiveAirplanes_;
      if (nActiveAirplanes_ == 0)
        dialogBox_ = true;
    } if (status->airplaneRealCollision) {
      dialogBox_ = true;
      gameOver_ = true;
    } if (status->forbiddenZoneRealCollision) {
      dialogBox_ = true;
      gameOver_ = true;
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
    
  // Ask the user if we have to, but don't block here to allow normal exit.
  if (dialogBox_)
    renderUserDialogBox();
  
  // Flip the video buffers.
  window_.flip();

}



void Game::renderUserDialogBox() {
  
  Surface userDialogBox(300, 200);
  
  // White background.
  userDialogBox.drawFilledRectangle(0, 0, 299, 199, 255, 255, 255, 255);
  
  // Black title bar.
  userDialogBox.drawFilledRectangle(6, 6, 292, 60, 0, 0, 0, 255);
  
  // Contour : transparent black gradient.
  userDialogBox.drawRectangle(0, 0, 299, 199, 0, 0, 0,  70);
  userDialogBox.drawRectangle(1, 1, 298, 198, 0, 0, 0, 100);
  userDialogBox.drawRectangle(2, 2, 297, 197, 0, 0, 0, 130);
  userDialogBox.drawRectangle(3, 3, 296, 196, 0, 0, 0, 160);
  userDialogBox.drawRectangle(4, 4, 295, 195, 0, 0, 0, 190);
  userDialogBox.drawRectangle(5, 5, 294, 194, 0, 0, 0, 220);
  userDialogBox.drawRectangle(6, 6, 293, 193, 0, 0, 0, 255);
  
  uint8_t restartGrey(100), exitGrey(100);
  int mX, mY;
  
  // Test if mouse left button is pressed.
  if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON_LMASK) {
    
    // Restart button pressed.
    if (mX >= 250+20  && mX <= 250+140 && mY >= 175+140 && mY <= 175+180)
      restartGrey = 50;

    // Exit button pressed.
    if (mX >= 250+160 && mX <= 250+280 && mY >= 175+140 && mY <= 175+180)
      exitGrey = 50;
    
  }
  
  // Buttons background.
  userDialogBox.drawFilledRectangle( 20, 140, 140, 180,
          restartGrey, restartGrey, restartGrey, 255);
  userDialogBox.drawFilledRectangle(160, 140, 280, 180,
          exitGrey, exitGrey, exitGrey, 255);
  
  // Buttons contour : grey gradient.
  userDialogBox.drawRectangle(19, 139, 141, 181, 140, 140, 140,  255);
  userDialogBox.drawRectangle(18, 138, 142, 182, 180, 180, 180,  255);
  userDialogBox.drawRectangle(17, 137, 143, 183, 220, 220, 220,  255);
  userDialogBox.drawRectangle(159, 139, 281, 181, 140, 140, 140,  255);
  userDialogBox.drawRectangle(158, 138, 282, 182, 180, 180, 180,  255);
  userDialogBox.drawRectangle(157, 137, 283, 183, 220, 220, 220,  255);
  
  // Texts.
  
  int16_t pos(110);
  uint8_t red(0), green(180);
  std::string title("Bravo !");
  if (gameOver_) {
    title = "Game over.";
    pos = 90;
    red = 255;
    green = 0;
  }
  Surface titleSurf(title, red, green, 0, BOLDFONT, 20);
  userDialogBox.blit(titleSurf, pos, 22);
  
  const std::string score("Final score : " + std::to_string(int(score_)));
  Surface scoreSurf(score, 0, 0, 0, BOLDFONT, 18);
  userDialogBox.blit(scoreSurf, 20, 90);
  
  const std::string button1("RESTART");
  Surface button1Surf(button1, 0, 0, 0, BOLDFONT, 16);
  userDialogBox.blit(button1Surf, 40, 152);
  
  const std::string button2("QUIT");
  Surface button2Surf(button2, 0, 0, 0, BOLDFONT, 16);
  userDialogBox.blit(button2Surf, 200, 152);
  
  // Blit everything to the window.
  window_.blit(userDialogBox, 250, 175);
  
}



void Game::onExit() {
  state_ = exit;
}



void Game::onLButtonUp(int mX, int mY) {
  
  // If we are showing the dialog box, the user can click on a button.
  if (dialogBox_) {
    
    // Restart button pressed.
    if (mX >= 250+20  && mX <= 250+140 && mY >= 175+140 && mY <= 175+180)
      state_ = restart;
    
    // Exit button pressed.
    if (mX >= 250+160 && mX <= 250+280 && mY >= 175+140 && mY <= 175+180)
      state_ = exit;
    
  } 
}



void Game::onLButtonDown(int mX, int mY) {
  
  // If we are showing the dialog box, user cannot change airplane trajectories.
  if (dialogBox_)
    return;
  
  Entity* selectedEntity(nullptr);
  Entity* clickedEntity(nullptr);

  for (auto& entity : entities_) {

    // Get the selected entity.
    if (entity->getSelected()) {
      // Convert from std::unique_ptr<Entity> to Entity*.
      selectedEntity = &(*entity);
    }

    // Check if the click was on an entity.
    if (entity->isInside(Entity::Point(mX, mY), Entity::realPosition, true)) {
      clickedEntity = &(*entity);
    }
  }

  // An entity was selected and we click somwhere : deselect it and change cape.
  if (selectedEntity != nullptr) {
    selectedEntity->setSelected(false);
    selectedEntity->setTargetCape(Entity::Point(mX, mY));

  // Else if another entity was clicked : select it.
  } else if (clickedEntity != nullptr) {
      clickedEntity->setSelected(true);
  }
  
}



//void Game::handleEvent(SDL_Event& event) {
//  Events::handleEvent(event);
//}
  

}  // End of project ATCsim namespace.

