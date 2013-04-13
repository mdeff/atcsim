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

#include "Game.h"

using namespace std;


// Function declarations.


// This function handles all the loading of data, whether it be textures, maps,
// NPCs, or whatever.
void initialize();


// This function simply cleans up any resources loaded, and insures a peaceful
// quitting of the game. 
// The cleanup() callback will be called at application exit to cleanup SDL stuff.
void cleanup();



//#include "IEntity.h"
//IEntity::~IEntity() {}



// int main(int argc, char** argv) {
int main() {
  
initialize();
  
  try {
    cout << "Simulation start." << endl;
  
    Game ATCsim;
    SDL_Event event;

    while (ATCsim.getState()) {

      while (SDL_PollEvent(&event) == 1)
        ATCsim.handleEvent(event);

      ATCsim.compute();
      ATCsim.render();
    }
    
  } catch (...) {
    cerr << "Simulation error." << endl;
  }
  
}



void initialize() {
  
  // Be sure to quit the SDL and TTF libraries before exiting.
  // This is exception safe.
  atexit(cleanup);
  
  // Load and initialize SDL and TTF libraries.
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
    throw;
  }

  if (TTF_Init() != 0) {
    cerr << "Unable to initialize TTF: " << TTF_GetError() << endl;
    throw;
  }
}



void cleanup() {
  TTF_Quit();
  SDL_Quit();
  cout << "Simulation end." << endl;
}

