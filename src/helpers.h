#ifndef HELPERS_H_
#define HELPERS_H_

#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <sstream>
#include <iostream>

#define STRING_NEW(x) Nan::New(x).ToLocalChecked()

namespace sdl {

  // Error reporting helpers
  void ThrowSDLException(const char* name);

  v8::Local<v8::Object> SDLDisplayModeToJavascriptObject(const SDL_DisplayMode& mode);

} // sdl

#endif  // HELPERS_H_
