/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on 23. mars 2013, 17:54
 */


#include <stdexcept>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Game.h"



// Function declarations.



// This function handles all the loading of data, whether it be textures, maps,
// NPCs, or whatever.
void initialize();



// This function simply cleans up any resources loaded, and insures a peaceful
// quitting of the game. 
// The cleanup callback will be called at application exit to cleanup SDL stuff.
void cleanup();



// int main(int argc, char** argv) {
int main() {
    
  try {
    
    std::cout << "Simulation start." << std::endl;
    
    initialize();
    
    Game ATCsim;
    SDL_Event event;

    while (ATCsim.getState()) {

      while (SDL_PollEvent(&event) == 1)
        ATCsim.handleEvent(event);

      ATCsim.compute();
      ATCsim.render();
    }
    
  // Catch exceptions inherited from the standard exception class.
  // All exceptions from standard library, and also for this project.
  } catch (std::exception& e) {
    std::cerr << "Simulation error: " << e.what() << std::endl;
    
  // Catch all other exceptions (should not occur).
  } catch (...) {
    std::cerr << "Simulation error." << std::endl;
  }
  
}



void initialize() {
  
  // Be sure to quit the SDL and TTF libraries before exiting.
  // This is exception safe.
  atexit(cleanup);
  
  // Load and initialize SDL and TTF libraries.
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    throw std::runtime_error("Unable to initialize SDL: " + std::string(SDL_GetError()));

  if (TTF_Init() != 0)
    throw std::runtime_error("Unable to initialize TTF: " + std::string(TTF_GetError()));
  
}



void cleanup() {
  TTF_Quit();
  SDL_Quit();
  std::cout << "Simulation end." << std::endl;
}

