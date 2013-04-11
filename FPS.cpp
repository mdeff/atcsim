//=============================================================================
#include "FPS.h"

//=============================================================================
//FPS FPS::FPSControl;


unsigned int FPS::oldTime_(0);
unsigned int FPS::lastTime_(0);

float FPS::speedFactor_(0);

unsigned int FPS::frames_(0);
unsigned int FPS::numFrames_(0);

//=============================================================================

//FPS::FPS()
////:
////oldTime(0),
////lastTime(0),
////speedFactor(0),
////frames(0),
////numFrames(0)
//{
//}

//=============================================================================
void FPS::compute() {
  
  // Compute framerate (aka FPS).
  frames_++;
  if (oldTime_ + 1000 < SDL_GetTicks()) {
    oldTime_ = SDL_GetTicks();
    numFrames_ = frames_;
    frames_ = 0;
  }

  // Compute speed factor.
  speedFactor_ = ( float(SDL_GetTicks() - lastTime_) / 1000.0f ) * 32.0f;
  lastTime_ = SDL_GetTicks();
  
}

//=============================================================================
unsigned int FPS::getFPS() {
    return numFrames_;
}

//------------------------------------------------------------------------------
float FPS::getSpeedFactor() {
    return speedFactor_;
}

//==============================================================================

