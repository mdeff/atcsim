//==============================================================================
// FPS Class
//==============================================================================
#ifndef _CFPS_H_
#define _CFPS_H_

#include <SDL/SDL.h>

//==============================================================================
class FPS {
  
	public:
    
//		static FPS FPSControl;
    
	static void compute();
	static unsigned int getFPS();
	static float getSpeedFactor();

	private:
    
  // Do not allow object creation by making default constructor private.
  // Mark methods that won’t be implemented with '= delete' (C++11).
	FPS() = delete;
  
	static unsigned int oldTime_;
	static unsigned int lastTime_;

	static float speedFactor_;

  static unsigned int frames_;
	static unsigned int numFrames_;
    
};

//==============================================================================
#endif
