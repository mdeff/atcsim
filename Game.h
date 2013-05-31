/* 
 * File:   Game.h
 * Author: michael
 *
 * Created on 23. mars 2013, 17:54
 */

#ifndef GAME_H
#define	GAME_H


#include <memory>           // For C++11 unique_ptr.
#include <vector>

#include "Events.h"
#include "Surface.h"


namespace ATCsim {  // Project ATCsim namespace.


// Forward declarations (no header includes) (namespace pollution, build time).
class Entity;


class Game : public Events {
  
public:
  
  // Constructor takes the configuration file name.
  Game(std::string configFileName);
  
  // Although it does nothing more than default, it should be defined for unique_ptr.
  // Default : call base class'es destructor and destructors of all members.
  // Does not throw any exception (which is what we want for a dtor).
  virtual ~Game() noexcept(true);
  
  // Return the game state.
  enum GameStates {run, restart, exit};
  GameStates getState() const;
  
  // This method handles all the data updates, such as a NPCs moving across
  // the screen, decreasing your health bar, or whatever.
  void compute();

  // This method handles all the rendering of anything that shows up on the
  // screen. It does NOT handle data manipulation, as this is what the compute()
  // method is supposed to handle.
  void render();

  // This method handles all input events from the mouse, keyboard, joysticks,
  // or other devices.
//  void handleEvent(SDL_Event& event);
  virtual void onExit() final;
  virtual void onLButtonDown(int mX, int mY) final;
  virtual void onLButtonUp(int mX, int mY) final;
  
protected:
  
private:
  
  Surface window_;         // Main window SDL surface.
  Surface background_;     // Background bitmap SDL surface.
  Surface sidePanel_;      // Side panel SDL surface.
//  Surface userDialogBox_;  // User dialog box SDL surface.
  
  // Indiquate game state : run, restart or exit.
  GameStates state_;
  
  // User score (points).
  float score_;
  
  // Number of active airplanes inside the simulation.
  unsigned int nActiveAirplanes_;
  
  // Indiquate to show a dialog who ask the user if he wish to restart or quit
  // the simulation.
  bool dialogBox_;
  
  // Indique if the player loosed the game.
  bool gameOver_;
  
  // Game field size (used to check movement bounds).
  const int gameFieldWidth_;
  const int gameFieldHeight_;
  
  // Store the entities (moving objects).
  std::vector< std::unique_ptr<Entity> > entities_;
  
  // Ask the user if he wish to restart or quit the simulation.
  void renderUserDialogBox();
  
  // Do not allow object copy or move by making copy / move constructor and
  // copy / move assignment operator private members.
  // It will fail to compile if somebody want to copy or move a Game object.
  // Also prohibit default constructor usage.
  // Mark methods that won’t be implemented with '= delete' (C++11).
  Game() = delete;
  Game(const Game& orig) = delete;
  Game& operator=(const Game& orig) = delete;
  Game(Game&& orig) = delete;
  Game& operator=(Game&& orig) = delete;
  
};
  

}  // End of project ATCsim namespace.


#endif	/* GAME_H */

