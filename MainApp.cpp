/* 
 * File:   MainApp.cpp
 * Author: michael
 * 
 * Created on 23. mars 2013, 17:54
 */

#include "MainApp.h"
#include "IEntity.h"
#include "Surface.h"
#include "Airplane.h"
#include "ForbiddenZone.h"
#include "Cloud.h"

using namespace std;



MainApp::MainApp()
: CEvent(),                     // Parent constructor.
screen_(800, 551, 32),          // Image resolution of 800*551.
background_("background.bmp"),  // Load the background image.
running_(true),
entities() {
   
  // Add airplanes, forbidden zones and clouds to the heterogeneous collection.
  entities.push_back( unique_ptr<IEntity> (
                      new Airplane(1111, 8000, 10, 700, 40, 400) ) );
  entities.push_back( unique_ptr<IEntity> (
                      new Airplane(222222222, 9811, 20, 700, 200, 400) ) );
  entities.push_back( unique_ptr<IEntity> (
                      new Airplane(33, 7510, -12, 700, 350, 250) ) );
  entities.push_back( unique_ptr<IEntity> (
                      new Airplane(44444, 7240, 44, 700, 750, 300) ) );
  entities.push_back( unique_ptr<IEntity> (
                      new ForbiddenZone({0,250,400,0}, {0,0,200,200}) ) );
  entities.push_back( unique_ptr<IEntity> (
                      new ForbiddenZone({0,200,400,450,450,0}, {500,350,350,450,551,551}) ) );
  entities.push_back( unique_ptr<IEntity> (
                      new ForbiddenZone({500,800,800,600}, {0,0,250,200}) ) );
  entities.push_back( unique_ptr<IEntity> (
                      new Cloud({540,620,770,770,700,580}, {400,350,400,500,540,500}) ) );
                      
}



MainApp::~MainApp() {
  // Default: call base class'es destructor and destructors of all members.
}



int MainApp::execute() {

  SDL_Event event;

//  if (!init()) {
//    cleanup();
//    return -1;
//  }

  while (running_) {
    while (SDL_PollEvent(&event) == 1)
      onEvent(&event);
    if (!loop()) {
      cleanup();
      return -1;
    }
    if (!render()) {
      cleanup();
      return -1;
    }
  }

  return 0;
}



//bool MainApp::init() {
//  return true;
//}



bool MainApp::loop() {
  return true;
}



bool MainApp::render() {

  screen_.blit(background_, 0, 0);

  // Draw the airplanes, forbidden zones and clouds.
  for (unique_ptr<IEntity>& entity : entities) {
    entity->render(screen_);
  }
  
  screen_.flip();
  
  return true;
}



void MainApp::onExit() {
  running_ = false;
}



void MainApp::onEvent(SDL_Event* event) {
  CEvent::onEvent(event);
}



void MainApp::cleanup() {
}

