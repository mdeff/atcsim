//==============================================================================
// FPS namespace
//==============================================================================

#ifndef FPS_H
#define FPS_H

#include <SDL/SDL.h>



namespace FPS {
    
	void compute();
	unsigned int getFPS();
	float getSpeedFactor();
    
}



#endif	/* FPS_H */

