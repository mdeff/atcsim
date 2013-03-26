/* 
 * File:   MainApp.h
 * Author: michael
 *
 * Created on 23. mars 2013, 17:54
 */

#ifndef MAINAPP_H
#define	MAINAPP_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "CEvent.h"
#include "Surface.h"

class MainApp : public CEvent {
  
public:
  
  MainApp();
  
  // Do not define : use the compiler generated copy constructor.
  MainApp(const MainApp& orig);
  
  virtual ~MainApp();
  
  int execute();

  bool init();

  void onExit();

  bool loop();

  bool render();

  void cleanup();

  void onEvent(SDL_Event* event);

private:
  
  bool running_;
  SDL_Surface* screenSurf_;
  SDL_Surface* backgroundSurf_;

};

#endif	/* MAINAPP_H */
