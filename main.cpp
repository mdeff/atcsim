/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on 23. mars 2013, 17:54
 */

#include <cstdlib>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "MainApp.h"

using namespace std;


void exit() {
  TTF_Quit();
  SDL_Quit();
  cout << "Simulation stop." << endl;
}


int main(int argc, char** argv) {
  
  // Be sure to quit the SDL and TTF libraries before exiting.
  atexit(exit);
  
  // Load and initialize SDL and TTF libraries.
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  if (TTF_Init() != 0) {
    printf("Unable to initialize TTF: %s\n", TTF_GetError());
    return false;
  }

  // Set the window title.
  SDL_WM_SetCaption("Air Traffic Control simulator, CS-118 project, EPFL", NULL);
  
  try {
    
    cout << "Simulation start." << endl;
  MainApp simulation;
  return simulation.execute();
  
  } catch (...) {
    cout << "Simulation error." << endl;
  }
  
}
