/* 
 * File:   Game.cpp
 * Author: michael
 * 
 * Created on 23. mars 2013, 17:54
 */

#include "Airplane.h"
#include "Cloud.h"
#include "Constants.h"
#include "Entity.h"
#include "ForbiddenZone.h"
#include "FPS.h"
#include "Game.h"
#include "Surface.h"

using namespace std;



Game::Game()
: Events(),                     // Parent constructor.
window_(WINDOWXSIZE, WINDOWYSIZE, 32),
background_("background.bmp"),  // Load the background image.
running_(true),
entities_() {
   
  // Add airplanes, forbidden zones and clouds to the heterogeneous collection.
  entities_.push_back( unique_ptr<Entity> (
                      new Airplane(1111, 8000, 10.0f, 800, 40, 400) ) );
  entities_.push_back( unique_ptr<Entity> (
                      new Airplane(222222222, 9811, 90.3f, 600, 200, 400) ) );
  entities_.push_back( unique_ptr<Entity> (
                      new Airplane(33, 7510, -12.2f, 700, 350, 250) ) );
  entities_.push_back( unique_ptr<Entity> (
                      new Airplane(44444, 7240, 180.0f, 400, 750, 300) ) );
  
  entities_.push_back( unique_ptr<Entity> (
                      new ForbiddenZone({0,250,400,0}, {0,0,200,200}) ) );
  entities_.push_back( unique_ptr<Entity> (
                      new ForbiddenZone({0,200,400,450,450,0}, {500,350,350,450,551,551}) ) );
  entities_.push_back( unique_ptr<Entity> (
                      new ForbiddenZone({500,800,800,600}, {0,0,250,200}) ) );
  
  entities_.push_back( unique_ptr<Entity> (
                      new Cloud({540,620,770,790,700,580}, {400,350,400,500,540,500}, 124.2f, 200) ) );
                      
}



Game::~Game() throw() {
  // Default: call base class'es destructor and destructors of all members.
}



bool Game::getState() {
  
  return running_;
  
}

void Game::compute() {
  
  // Compute the framerate.
  FPS::compute();
  
  // Do the necessary computations for the airplanes, forbidden zones and clouds.
  for (auto& entity : entities_) {
    entity->compute();
  }
  
}



void Game::render() {

  // Set the window title.
  const string windowTitle = "Air Traffic Control simulator, CS-118 project, EPFL"
                             "\t" + to_string(FPS::getFPS()) + " FPS";
  SDL_WM_SetCaption(windowTitle.c_str(), nullptr);
  
  window_.blit(background_, 0, 0);

  // Render the airplanes, forbidden zones and clouds.
  for (auto& entity : entities_) {
    entity->render(window_);
  }
  
  window_.flip();
  
}



void Game::onExit() {
  running_ = false;
}



void Game::handleEvent(SDL_Event& event) {
  Events::handleEvent(event);
}

