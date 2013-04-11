
//==============================================================================
#include "Events.h"

//==============================================================================

Events::Events() {
  // Do nothing.
}

//------------------------------------------------------------------------------

Events::~Events() {
  // Default: call base class'es destructor and destructors of all members.
}

//==============================================================================

void Events::onEvent(SDL_Event& event) {
  switch (event.type) {
    case SDL_ACTIVEEVENT:
    {
      switch (event.active.state) {
        case SDL_APPMOUSEFOCUS:
        {
          if (event.active.gain) onMouseFocus();
          else onMouseBlur();

          break;
        }
        case SDL_APPINPUTFOCUS:
        {
          if (event.active.gain) onInputFocus();
          else onInputBlur();

          break;
        }
        case SDL_APPACTIVE:
        {
          if (event.active.gain) onRestore();
          else onMinimize();

          break;
        }
        default:
          break;
      }
      break;
    }

    case SDL_KEYDOWN:
    {
      onKeyDown(event.key.keysym.sym, event.key.keysym.mod, event.key.keysym.unicode);
      break;
    }

    case SDL_KEYUP:
    {
      onKeyUp(event.key.keysym.sym, event.key.keysym.mod, event.key.keysym.unicode);
      break;
    }

    case SDL_MOUSEMOTION:
    {
      onMouseMove(event.motion.x, event.motion.y,
                  event.motion.xrel, event.motion.yrel,
                  (event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
                  (event.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
                  (event.motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
      break;
    }

    case SDL_MOUSEBUTTONDOWN:
    {
      switch (event.button.button) {
        case SDL_BUTTON_LEFT:
        {
          onLButtonDown(event.button.x, event.button.y);
          break;
        }
        case SDL_BUTTON_RIGHT:
        {
          onRButtonDown(event.button.x, event.button.y);
          break;
        }
        case SDL_BUTTON_MIDDLE:
        {
          onMButtonDown(event.button.x, event.button.y);
          break;
        }
        default:
          break;
      }
      break;
    }

    case SDL_MOUSEBUTTONUP:
    {
      switch (event.button.button) {
        case SDL_BUTTON_LEFT:
        {
          onLButtonUp(event.button.x, event.button.y);
          break;
        }
        case SDL_BUTTON_RIGHT:
        {
          onRButtonUp(event.button.x, event.button.y);
          break;
        }
        case SDL_BUTTON_MIDDLE:
        {
          onMButtonUp(event.button.x, event.button.y);
          break;
        }
        default:
          break;
      }
      break;
    }

    case SDL_JOYAXISMOTION:
    {
      onJoyAxis(event.jaxis.which, event.jaxis.axis, event.jaxis.value);
      break;
    }

    case SDL_JOYBALLMOTION:
    {
      onJoyBall(event.jball.which, event.jball.ball, event.jball.xrel,
                event.jball.yrel);
      break;
    }

    case SDL_JOYHATMOTION:
    {
      onJoyHat(event.jhat.which, event.jhat.hat, event.jhat.value);
      break;
    }
    case SDL_JOYBUTTONDOWN:
    {
      onJoyButtonDown(event.jbutton.which, event.jbutton.button);
      break;
    }

    case SDL_JOYBUTTONUP:
    {
      onJoyButtonUp(event.jbutton.which, event.jbutton.button);
      break;
    }

    case SDL_QUIT:
    {
      onExit();
      break;
    }

    case SDL_SYSWMEVENT:
    {
      //Ignore
      break;
    }

    case SDL_VIDEORESIZE:
    {
      onResize(event.resize.w, event.resize.h);
      break;
    }

    case SDL_VIDEOEXPOSE:
    {
      onExpose();
      break;
    }

    default:
    {
      onUser(event.user.type, event.user.code, event.user.data1,
             event.user.data2);
      break;
    }
  }
}

//------------------------------------------------------------------------------

void Events::onInputFocus() {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onInputBlur() {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onMouseFocus() {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onMouseBlur() {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onMouseMove(int mX, int mY, int relX, int relY, bool Left,
                         bool Right, bool Middle) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onMouseWheel(bool Up, bool Down) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onLButtonDown(int mX, int mY) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onLButtonUp(int mX, int mY) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onRButtonDown(int mX, int mY) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onRButtonUp(int mX, int mY) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onMButtonDown(int mX, int mY) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onMButtonUp(int mX, int mY) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onJoyButtonDown(Uint8 which, Uint8 button) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onJoyButtonUp(Uint8 which, Uint8 button) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onJoyHat(Uint8 which, Uint8 hat, Uint8 value) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onMinimize() {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onRestore() {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onResize(int w, int h) {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onExpose() {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onExit() {
  //Pure virtual, do nothing
}

//------------------------------------------------------------------------------

void Events::onUser(Uint8 type, int code, void* data1, void* data2) {
  //Pure virtual, do nothing
}

//==============================================================================
