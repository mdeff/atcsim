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


// Forward declarations (no header includes) (namespace pollution, build time).
class Entity;


class Game : public Events {
  
public:
  
  // Use a custom default constructor.
  Game();
  
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Game() throw();
  
  // Return the game stat, which is true if running.
  bool getState() const;
  
  // This method handles all the data updates, such as a NPCs moving across
  // the screen, decreasing your health bar, or whatever.
  void compute();

  // This method handles all the rendering of anything that shows up on the
  // screen. It does NOT handle data manipulation, as this is what the compute()
  // method is supposed to handle.
  void render();

  // This method handles all input events from the mouse, keyboard, joysticks,
  // or other devices.
  void handleEvent(SDL_Event& event);
  void onExit();
  
protected:
  
private:
  
  Surface window_;      // Main window SDL surface.
  Surface background_;  // Background bitmap SDL surface.
  Surface sidePanel_;   // Side panel SDL surface
  bool running_;
  
  // Game field size (used to check movement bounds).
  const int gameFieldWidth_;
  const int gameFieldHeight_;
  
  // Store the entities (moving objects).
  std::vector< std::unique_ptr<Entity> > entities_;
  
  // Do not allow object copy or move by making copy / move constructor and
  // copy / move assignment operator private members.
  // It will fail to compile if somebody want to copy or move a Surface object.
  // Mark methods that won’t be implemented with '= delete' (C++11).
  Game(const Game& orig) = delete;
  Game& operator=(const Game& orig) = delete;
  Game(Game&& orig) = delete;
  Game& operator=(Game&& orig) = delete;
  
};

#endif	/* GAME_H */
