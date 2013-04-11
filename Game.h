/* 
 * File:   MainApp.h
 * Author: michael
 *
 * Created on 23. mars 2013, 17:54
 */

#ifndef MAINAPP_H
#define	MAINAPP_H

#include <vector>
#include <memory>           // For C++11 unique_ptr.

#include "Events.h"
#include "Surface.h"

// Forward declarations (no header including) (namespace pollution, build time).
class IEntity;


class Game : public Events {
  
public:
  
  Game();
  
  // Do not define : use the compiler generated copy constructor.
  Game(const Game& orig);
  
  virtual ~Game();
  
  bool getState();
  
  // This function handles all the data updates, such as a NPCs moving across the screen, decreasing your health bar, or whatever
  void compute();

  // This function handles all the rendering of anything that shows up on the screen. It does NOT handle data manipulation, as this is what the Loop function is supposed to handle.
  void render();

  // This function handles all input events from the mouse, keyboard, joysticks, or other devices.
  void onEvent(SDL_Event& event);
  void onExit();

protected:
  
private:
  
  Surface window_;
  Surface background_;
  bool running_;
  
  // Store the entities (moving simulation objects).
  std::vector< std::unique_ptr<IEntity> > entities_;

};

#endif	/* MAINAPP_H */
