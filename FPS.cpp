//=============================================================================
#include "FPS.h"


//=============================================================================

namespace FPS {
  
  // These variables are only visible from inside this namespace.
  // They cannot be accessed from outside with FPS::oldTime for example.
  // They are initialized at startup and keep their values between function calls.
  
  unsigned int oldTime(0);
	unsigned int lastTime(0);

	float speedFactor(0);

  unsigned int frames(0);
	unsigned int nFrames(50);
  // Not initialized to zero or we'll get infinite speed.
    
  
  
  void compute() {

    // Compute framerate (aka FPS).
    frames++;
    if (oldTime + 1000 < SDL_GetTicks()) {
      oldTime = SDL_GetTicks();
      nFrames = frames;
      frames = 0;
    }

    // Compute speed factor.
    speedFactor = ( float(SDL_GetTicks() - lastTime) / 1000.0f ); // * 32.0f;
    lastTime = SDL_GetTicks();

  }

  //----------------------------------------------------------------------------
  unsigned int getFPS() {
      return nFrames;
  }

  //----------------------------------------------------------------------------
  float getSpeedFactor() {
      return speedFactor;
  }
  
}

