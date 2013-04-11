/* 
 * File:   MainApp.cpp
 * Author: michael
 * 
 * Created on 23. mars 2013, 17:54
 */

#include "Game.h"
#include "IEntity.h"
#include "Surface.h"
#include "Airplane.h"
#include "ForbiddenZone.h"
#include "Cloud.h"
#include "FPS.h"

using namespace std;



Game::Game()
: Events(),                     // Parent constructor.
window_(800, 551, 32),          // Image resolution of 800*551.
background_("background.bmp"),  // Load the background image.
running_(true),
entities_() {
   
  // Add airplanes, forbidden zones and clouds to the heterogeneous collection.
  entities_.push_back( unique_ptr<IEntity> (
                      new Airplane(1111, 8000, 10, 700, 40, 400) ) );
  entities_.push_back( unique_ptr<IEntity> (
                      new Airplane(222222222, 9811, 20, 700, 200, 400) ) );
  entities_.push_back( unique_ptr<IEntity> (
                      new Airplane(33, 7510, -12, 700, 350, 250) ) );
  entities_.push_back( unique_ptr<IEntity> (
                      new Airplane(44444, 7240, 44, 700, 750, 300) ) );
  
  entities_.push_back( unique_ptr<IEntity> (
                      new ForbiddenZone({0,250,400,0}, {0,0,200,200}) ) );
  entities_.push_back( unique_ptr<IEntity> (
                      new ForbiddenZone({0,200,400,450,450,0}, {500,350,350,450,551,551}) ) );
  entities_.push_back( unique_ptr<IEntity> (
                      new ForbiddenZone({500,800,800,600}, {0,0,250,200}) ) );
  
  entities_.push_back( unique_ptr<IEntity> (
                      new Cloud({540,620,770,770,700,580}, {400,350,400,500,540,500}) ) );
                      
}



Game::~Game() {
  // Default: call base class'es destructor and destructors of all members.
}



bool Game::getState() {
  
  return running_;
  
}

void Game::compute() {
  
  FPS::compute();
  
}



void Game::render() {

  // Set the window title.
  const string windowTitle = "Air Traffic Control simulator, CS-118 project, EPFL"
                             "\t" + to_string(FPS::getFPS()) + " FPS";
  SDL_WM_SetCaption(windowTitle.c_str(), nullptr);
  
  window_.blit(background_, 0, 0);

  // Draw the airplanes, forbidden zones and clouds.
  for (unique_ptr<IEntity>& entity : entities_) {
    entity->render(window_);
  }
  
  window_.flip();
  
}



void Game::onExit() {
  running_ = false;
}



void Game::onEvent(SDL_Event& event) {
  Events::onEvent(event);
}


