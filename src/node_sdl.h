#ifndef NODE_SDL_H_
#define NODE_SDL_H_

// Various defines to modify how the bindings operate somewhat when compiled. This can include
// things such as disabling runtime argument checks, including various logging, etc.
//
// NOTE: None of these flags are actually used yet. I am only putting them in here as a note to
// myself as to what features I will want to be optionally disabled in the future. Otherwise I
// will forget :)

// NOTE: All of these defines are actually put into binding.gyp
// WARNING: The only time you should disable arg checking is after thoroughly testing your application
// and you don't see any exceptions being thrown. You WILL get segfaults if you aren't careful about
// what types you pass to some functions without having them checked. (such as passing an SDL_Color
// when something want an SDL_Texture, or vise versa) And there will be no stacktrace or anything
// pointing to a location where the problem happened.
// #define ENABLE_ARG_CHECKING
// If this is not defined, the entire SDL_image wrapper will not be included in the build.
// #define ENABLE_IMAGE
// If this is not defined, the entire SDL_ttf wrapper will not be included in the build.
// #define ENABLE_TTF

#include <nan.h>
#include <node.h>
#include <v8.h>
#include <map>
#include <string>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "helpers.h"
#include "render.h"

namespace sdl {
  // Initialization and Shutdown.
  NAN_METHOD(Init);
  NAN_METHOD(InitSubSystem);
  NAN_METHOD(WasInit);
  NAN_METHOD(Quit);
  NAN_METHOD(QuitSubSystem);

  // Display and Window Management.
  NAN_METHOD(DisableScreenSaver);
  NAN_METHOD(EnableScreenSaver);
  NAN_METHOD(IsScreenSaverEnabled);

  NAN_METHOD(GetClosestDisplayMode);
  NAN_METHOD(GetCurrentDisplayMode);
  NAN_METHOD(GetCurrentVideoDriver);
  NAN_METHOD(GetDesktopDisplayMode);
  NAN_METHOD(GetDisplayBounds);
  NAN_METHOD(GetDisplayMode);
  NAN_METHOD(GetDisplayName);
  NAN_METHOD(GetNumDisplayModes);
  NAN_METHOD(GetNumVideoDisplays);
  NAN_METHOD(GetNumVideoDrivers);
  NAN_METHOD(GetVideoDriver);
  // TODO: Put this functionality into Window?
  // NAN_METHOD(GetWindowFromID);

  // TODO: Implement showing a normal message box.
  // NAN_METHOD(ShowMessageBox);
  NAN_METHOD(ShowSimpleMessageBox);

  NAN_METHOD(VideoInit);
  NAN_METHOD(VideoQuit);

  // Error handling?
  NAN_METHOD(ClearError);
  NAN_METHOD(GetError);
  NAN_METHOD(SetError);

  NAN_METHOD(MapRGB);
  NAN_METHOD(MapRGBA);
  NAN_METHOD(GetRGB);
  NAN_METHOD(GetRGBA);

  NAN_METHOD(AddHintCallback);
  // NAN_METHOD(ClearHints);
  NAN_METHOD(GetHint);
  NAN_METHOD(SetHint);
  NAN_METHOD(SetHintWithPriority);

  NAN_METHOD(CompiledVersion);
  NAN_METHOD(CompiledRevision);
  NAN_METHOD(GetRevision);
  NAN_METHOD(GetRevisionNumber);
  NAN_METHOD(GetVersion);

  NAN_METHOD(GetClipboardText);
  NAN_METHOD(HasClipboardText);
  NAN_METHOD(SetClipboardText);

  namespace IMG {
    NAN_METHOD(Load);
  }

  namespace WM {
  }
}

#endif
