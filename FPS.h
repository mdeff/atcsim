//==============================================================================
// FPS Class
//==============================================================================

#ifndef FPS_H
#define FPS_H

#include <SDL/SDL.h>

//==============================================================================
class FPS {
  
	public:
    
//		static FPS FPSControl;
    
	static void compute();
	static unsigned int getFPS();
	static float getSpeedFactor();

	private:
    
  // Do not allow object creation by deleting all special function members.
  // Mark methods that won’t be implemented with '= delete' (C++11).
	FPS() = delete;
  FPS(const FPS& orig) = delete;
  FPS& operator=(const FPS& orig) = delete;
  FPS(FPS&& orig) = delete;
  FPS& operator=(FPS&& orig) = delete;
  ~FPS() = delete;
  
	static unsigned int oldTime_;
	static unsigned int lastTime_;

	static float speedFactor_;

  static unsigned int frames_;
	static unsigned int nFrames_;
    
};

//==============================================================================

#endif	/* FPS_H */
