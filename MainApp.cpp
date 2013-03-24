/* 
 * File:   MainApp.cpp
 * Author: michael
 * 
 * Created on 23. mars 2013, 17:54
 */

#include "MainApp.h"

MainApp::MainApp() {
  running = true;
  surfDisplay = NULL;
}

//MainApp::MainApp(const MainApp& orig) {}
//MainApp::~MainApp() {}

int MainApp::execute() {
  
  SDL_Event event;
  
  if (!init()) {
    cleanup();
    return -1;
  }
  
  while (running) {
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

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  // 800*551 is the image resolution
  if ((surfDisplay = SDL_SetVideoMode(800, 551, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return false;
  }
  
  surfBG = Surface::load("background.bmp");
  if (surfBG == NULL)
    return false;
  
  return true;  
}

 bool MainApp::loop(){
   return true;
 }
 
 bool MainApp::render() {
   
   if (!Surface::draw(surfDisplay, surfBG, 0, 0))
     return false;
   
   if (SDL_Flip(surfDisplay) != 0) {
     printf("Unable to flip display buffers: %s\n", SDL_GetError());
     return false;
   }
   
   return true;
 }
 
 void MainApp::onExit() {
   running = false;
 }
 
 void MainApp::onEvent(SDL_Event* event) {
   CEvent::onEvent(event);
 }
 
void MainApp::cleanup() {

  SDL_FreeSurface(surfBG);
  SDL_FreeSurface(surfDisplay);
  SDL_Quit();

}