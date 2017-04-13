#include <nan.h>
#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include "SDL.h"
#include "SDL_ttf.h"

#include "helpers.h"

using namespace v8;
using namespace node;

namespace sdl {

    // Helper for formatting error exceptions
  void ThrowSDLException(const char* name) {
    Nan::ThrowError(String::Concat(
      String::Concat(Nan::New(name).ToLocalChecked(), Nan::New(": ").ToLocalChecked()),
      STRING_NEW(SDL_GetError())
      ));
  }

  Local<Object> SDLEventToJavascriptObject(const SDL_Event& event) {
    Local<Object> evt = Nan::New<Object>();

    switch (event.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New(event.type == SDL_KEYDOWN ? "KEYDOWN" : "KEYUP").ToLocalChecked());
        evt->Set(Nan::New("scancode").ToLocalChecked(), Nan::New<Number>(event.key.keysym.scancode));
        evt->Set(Nan::New("sym").ToLocalChecked(), Nan::New<Number>(event.key.keysym.sym));
        evt->Set(Nan::New("mod").ToLocalChecked(), Nan::New<Number>(event.key.keysym.mod));
        evt->Set(Nan::New("repeat").ToLocalChecked(), Nan::New<Boolean>(event.key.repeat > 0 ? true : false));
      break;
      case SDL_MOUSEMOTION:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("MOUSEMOTION").ToLocalChecked());
        evt->Set(Nan::New("state").ToLocalChecked(), Nan::New<Number>(event.motion.state));
        evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.motion.which));
        evt->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(event.motion.x));
        evt->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(event.motion.y));
        evt->Set(Nan::New("xrel").ToLocalChecked(), Nan::New<Number>(event.motion.xrel));
        evt->Set(Nan::New("yrel").ToLocalChecked(), Nan::New<Number>(event.motion.yrel));
      break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New(event.type == SDL_MOUSEBUTTONDOWN ? "MOUSEBUTTONDOWN" : "MOUSEBUTTONUP").ToLocalChecked());
        evt->Set(Nan::New("button").ToLocalChecked(), Nan::New<Number>(event.button.button));
        evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.button.which));
        evt->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(event.button.x));
        evt->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(event.button.y));
      break;
      case SDL_JOYAXISMOTION:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("JOYAXISMOTION").ToLocalChecked());
        evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.jaxis.which));
        evt->Set(Nan::New("axis").ToLocalChecked(), Nan::New<Number>(event.jaxis.axis));
        evt->Set(Nan::New("value").ToLocalChecked(), Nan::New<Number>(event.jaxis.value));
      break;
      case SDL_JOYBALLMOTION:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("JOYBALLMOTION").ToLocalChecked());
        evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.jball.which));
        evt->Set(Nan::New("ball").ToLocalChecked(), Nan::New<Number>(event.jball.ball));
        evt->Set(Nan::New("xrel").ToLocalChecked(), Nan::New<Number>(event.jball.xrel));
        evt->Set(Nan::New("yrel").ToLocalChecked(), Nan::New<Number>(event.jball.yrel));
      break;
      case SDL_JOYHATMOTION:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("JOYHATMOTION").ToLocalChecked());
        evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.jhat.which));
        evt->Set(Nan::New("hat").ToLocalChecked(), Nan::New<Number>(event.jhat.hat));
        evt->Set(Nan::New("value").ToLocalChecked(), Nan::New<Number>(event.jhat.value));
      break;
      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New(event.type == SDL_JOYBUTTONDOWN ? "JOYBUTTONDOWN" : "JOYBUTTONUP").ToLocalChecked());
        evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.jbutton.which));
        evt->Set(Nan::New("button").ToLocalChecked(), Nan::New<Number>(event.jbutton.button));
      break;
      case SDL_QUIT:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("QUIT").ToLocalChecked());
      break;
      default:
        evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("UNKNOWN").ToLocalChecked());
        evt->Set(Nan::New("typeCode").ToLocalChecked(), Nan::New<Number>(event.type));
      break;
    }

    return evt;
  }

  Local<Object> SDLDisplayModeToJavascriptObject(const SDL_DisplayMode& mode) {
    Local<Object> jsMode = Nan::New<Object>();
    jsMode->Set(Nan::New("format").ToLocalChecked(), Nan::New<Number>(mode.format));
    jsMode->Set(Nan::New("w").ToLocalChecked(), Nan::New<Number>(mode.w));
    jsMode->Set(Nan::New("h").ToLocalChecked(), Nan::New<Number>(mode.h));
    jsMode->Set(Nan::New("refreshRate").ToLocalChecked(), Nan::New<Number>(mode.refresh_rate));
    return jsMode;
  }

} // node_sdl
