/* 
 * File:   MainApp.h
 * Author: michael
 *
 * Created on 23. mars 2013, 17:54
 */

#ifndef MAINAPP_H
#define	MAINAPP_H

#include <vector>
#include <memory>           // for C++11 unique_ptr

#include "CEvent.h"
#include "Surface.h"

// Forward declarations (no header including) (namespace pollution, build time).
class IEntity;


class MainApp : public CEvent {
  
public:
  
  MainApp();
  
  // Do not define : use the compiler generated copy constructor.
  MainApp(const MainApp& orig);
  
  virtual ~MainApp();
  
  int execute();

//  bool init();

  void onExit();

  bool loop();

  bool render();

  void cleanup();

  void onEvent(SDL_Event* event);

protected:
  
private:
  
  Surface screen_;
  Surface background_;
  bool running_;
  
  std::vector< std::unique_ptr<IEntity> > entities;

};

#endif	/* MAINAPP_H */
