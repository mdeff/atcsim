/* 
 * File:   MainApp.cpp
 * Author: michael
 * 
 * Created on 23. mars 2013, 17:54
 */

#include "MainApp.h"

MainApp::MainApp() {
  running_ = true;
  screenSurf_ = NULL;
}

//MainApp::MainApp(const MainApp& orig) {}
//MainApp::~MainApp() {}

int MainApp::execute() {
  
  SDL_Event event;
  
  if (!init()) {
    cleanup();
    return -1;
  }
  
  while (running_) {
    while(SDL_PollEvent(&event) == 1)
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

bool MainApp::init() {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return false;
  }
  
  if (TTF_Init() != 0) {
    printf("Unable to initialize TTF: %s\n", TTF_GetError());
    return false;
  }

  // 800*551 is the image resolution
  if ((screenSurf_ = SDL_SetVideoMode(800, 551, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return false;
  }
  
  backgroundSurf_ = Surface::load("background.bmp");
  if (backgroundSurf_ == NULL)
    return false;
  
  return true;  
}

 bool MainApp::loop(){
   return true;
 }
 
 bool MainApp::render() {
   
   if (!Surface::draw(screenSurf_, backgroundSurf_, 0, 0))
     return false;
   
   if (SDL_Flip(screenSurf_) != 0) {
     printf("Unable to flip display buffers: %s\n", SDL_GetError());
     return false;
   }
   
   return true;
 }
 
 void MainApp::onExit() {
   running_ = false;
 }
 
 void MainApp::onEvent(SDL_Event* event) {
   CEvent::onEvent(event);
 }
 
void MainApp::cleanup() {

  SDL_FreeSurface(backgroundSurf_);
  SDL_FreeSurface(screenSurf_);
  TTF_Quit();
  SDL_Quit();

}