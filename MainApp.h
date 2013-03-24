/* 
 * File:   MainApp.h
 * Author: michael
 *
 * Created on 23. mars 2013, 17:54
 */

#ifndef MAINAPP_H
#define	MAINAPP_H

#include <SDL/SDL.h>
#include "Surface.h"
#include "CEvent.h"

class MainApp : CEvent {
  
public:
  MainApp();
  //    MainApp(const MainApp& orig);
  //    virtual ~MainApp();
  
  int execute();

  bool init();

  void onExit();

  bool loop();

  bool render();

  void cleanup();

  void onEvent(SDL_Event* event);

private:
  bool running;
  SDL_Surface* surfDisplay;
  SDL_Surface* surfBG;

};

#endif	/* MAINAPP_H */
