//==============================================================================

#ifndef EVENTS_H
#define EVENTS_H

#include <SDL/SDL.h>


namespace ATCsim {  // Project ATCsim namespace.


//==============================================================================

class Events {
  
public:
  
  // Use the default (member to member) default constructor.
  Events() = default;

  // Default : call base class'es destructor and destructors of all members.
  // Does not throw any exception (which is what we want for a dtor).
  virtual ~Events() noexcept(true) = default;

  virtual void handleEvent(SDL_Event& event);

  virtual void onInputFocus();

  virtual void onInputBlur();

  virtual void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

  virtual void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

  virtual void onMouseFocus();

  virtual void onMouseBlur();

  virtual void onMouseMove(int mX, int mY, int relX, int relY, bool Left,
          bool Right, bool Middle);

  virtual void onMouseWheel(bool Up, bool Down); //Not implemented

  virtual void onLButtonDown(int mX, int mY);

  virtual void onLButtonUp(int mX, int mY);

  virtual void onRButtonDown(int mX, int mY);

  virtual void onRButtonUp(int mX, int mY);

  virtual void onMButtonDown(int mX, int mY);

  virtual void onMButtonUp(int mX, int mY);

  virtual void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value);

  virtual void onJoyButtonDown(Uint8 which, Uint8 button);

  virtual void onJoyButtonUp(Uint8 which, Uint8 button);

  virtual void onJoyHat(Uint8 which, Uint8 hat, Uint8 value);

  virtual void onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);

  virtual void onMinimize();

  virtual void onRestore();

  virtual void onResize(int w, int h);

  virtual void onExpose();

  virtual void onExit();

  virtual void onUser(Uint8 type, int code, void* data1, void* data2);
  
  
protected:
  
private:
  
  // Do not allow object copy or move by making copy / move constructor and
  // copy / move assignment operator private members.
  // It will fail to compile if somebody want to copy or move a Events object.
  // Mark methods that won’t be implemented with '= delete' (C++11).
  Events(const Events& orig) = delete;
  Events& operator=(const Events& orig) = delete;
  Events(Events&& orig) = delete;
  Events& operator=(Events&& orig) = delete;
  
};


}  // End of project ATCsim namespace.


#endif	/* EVENTS_H */
