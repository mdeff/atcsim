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



namespace ATCsim {  // Project ATCsim namespace.



// Program main function, where execution start.
int main();

// This function handles all the loading of data, whether it be textures, maps,
// NPCs, or whatever.
void initialize();

// This function simply cleans up any resources loaded, and insures a peaceful
// quitting of the game. 
// The cleanup callback will be called at application exit to cleanup SDL stuff.
void cleanup();

// Function which instanciates an instance of the game.
Game::GameStates play();



// int main(int argc, char** argv) {
int main() {

  int ret(0);

  try {

    std::cout << "Simulation start." << std::endl;

    // Initialize SDL.
    initialize();

    // Play until user decide to quit.
    while (play() != Game::exit);

  // Catch exceptions inherited from the standard exception class.
  // All exceptions from standard library, and also for this project.
  } catch (std::exception& e) {
    std::cerr << "Simulation error: " << e.what() << std::endl;
    ret = 1;

  // Catch all other exceptions (should not occur).
  } catch (...) {
    std::cerr << "Simulation error." << std::endl;
    ret = 1;
  }

  return ret;

}



Game::GameStates play() {

  Game game;
  SDL_Event event;
  Game::GameStates state(Game::run);

  while (state == Game::run) {

    while (SDL_PollEvent(&event) == 1)
      game.handleEvent(event);

    game.compute();
    game.render();

    state = game.getState();
  }

  return state;

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

  

}  // End of project ATCsim namespace.



// Should have a global main symbol.
int main() {
  return ATCsim::main();
}

