#ifdef __APPLE__
#include <objc/objc.h>
#include <objc/objc-runtime.h>
#endif

#include "SDL.h"
#include "SDL_revision.h"
#include "node_sdl.h"
#include "struct_wrappers.h"
#include "window.h"
#include "texture.h"
#include "surface.h"
#include "container.h"
#include "sdl_gl.h"
#include "event.h"
#include "key.h"
#include "mouse.h"
#include "font.h"
#include "joystick.h"
#include "controller.h"
#include "helpers.h"
#include <v8.h>
#include <string>
#include <iostream>
#include <ctime>
#include <sys/time.h>

using namespace v8;

static std::map<uint32_t, std::string> event_type_to_string_;
static std::map<SDL_WindowEventID, std::string> window_event_to_string_;

extern "C" void
init(Handle<Object> target)
{
// #ifdef __APPLE__
//   // on the mac it is necessary to create to call [NSApplication sharedApplication]
//   // before we can create a rendering window
//   objc_msgSend(objc_getClass("NSApplication"), sel_getUid("sharedApplication"));
// #endif
  // std::cout << "Starting init." << std::endl;

  // Initialize the SDL event type to string mappings.
  // std::cout << "Initializing SDL event type to string mappings." << std::endl;
  event_type_to_string_[SDL_DOLLARGESTURE] = "dollarGesture";
  event_type_to_string_[SDL_DROPFILE] = "dropFile";
  event_type_to_string_[SDL_FINGERMOTION] = "fingerMotion";
  event_type_to_string_[SDL_FINGERDOWN] = "fingerDown";
  event_type_to_string_[SDL_FINGERUP] = "fingerUp";
  event_type_to_string_[SDL_KEYDOWN] = "keyDown";
  event_type_to_string_[SDL_KEYUP] = "keyUp";
  event_type_to_string_[SDL_JOYAXISMOTION] = "joyAxisMotion";
  event_type_to_string_[SDL_JOYBALLMOTION] = "joyBallMotion";
  event_type_to_string_[SDL_JOYHATMOTION] = "joyHatMotion";
  event_type_to_string_[SDL_JOYBUTTONDOWN] = "joyButtonDown";
  event_type_to_string_[SDL_JOYBUTTONUP] = "joyButtonUp";
  event_type_to_string_[SDL_MOUSEMOTION] = "mouseMotion";
  event_type_to_string_[SDL_MOUSEBUTTONDOWN] = "mouseButtonDown";
  event_type_to_string_[SDL_MOUSEBUTTONUP] = "mouseButtonUp";
  event_type_to_string_[SDL_MOUSEWHEEL] = "mouseWheel";
  event_type_to_string_[SDL_MULTIGESTURE] = "multiGesture";
  event_type_to_string_[SDL_QUIT] = "quit";
  event_type_to_string_[SDL_SYSWMEVENT] = "sysWMEvent";
  event_type_to_string_[SDL_TEXTEDITING] = "textEditing";
  event_type_to_string_[SDL_TEXTINPUT] = "textInput";
  event_type_to_string_[SDL_USEREVENT] = "userEvent";
  event_type_to_string_[SDL_WINDOWEVENT] = "windowEvent";
  // std::cout << "Finished initializing event mappings." << std::endl;

  // Initialize the SDL WindowEvent type to string mappings.
  // std::cout << "Initializing SDL window event type to string mappings." << std::endl;
  window_event_to_string_[SDL_WINDOWEVENT_SHOWN] = "shown";
  window_event_to_string_[SDL_WINDOWEVENT_HIDDEN] = "hidden";
  window_event_to_string_[SDL_WINDOWEVENT_EXPOSED] = "exposed";
  window_event_to_string_[SDL_WINDOWEVENT_MOVED] = "moved";
  window_event_to_string_[SDL_WINDOWEVENT_RESIZED] = "resized";
  window_event_to_string_[SDL_WINDOWEVENT_SIZE_CHANGED] = "sizeChanged";
  window_event_to_string_[SDL_WINDOWEVENT_MINIMIZED] = "minimized";
  window_event_to_string_[SDL_WINDOWEVENT_MAXIMIZED] = "maximized";
  window_event_to_string_[SDL_WINDOWEVENT_RESTORED] = "restored";
  window_event_to_string_[SDL_WINDOWEVENT_ENTER] = "enter";
  window_event_to_string_[SDL_WINDOWEVENT_LEAVE] = "leave";
  window_event_to_string_[SDL_WINDOWEVENT_FOCUS_GAINED] = "focusGained";
  window_event_to_string_[SDL_WINDOWEVENT_FOCUS_LOST] = "focusLost";
  window_event_to_string_[SDL_WINDOWEVENT_CLOSE] = "close";
  // std::cout << "Finished initializing window event mappings." << std::endl;

  sdl::InitWrappers(target);
  sdl::WindowWrapper::Init(target);
  sdl::RendererWrapper::Init(target);
  sdl::TextureWrapper::Init(target);
  sdl::SurfaceWrapper::Init(target);
  sdl::ColorWrapper::Init(target);
  sdl::RectWrapper::Init(target);
  sdl::gl::Init(target);
  sdl::event::Init(target);
  sdl::key::Init(target);
  sdl::mouse::Init(target);
  sdl::TTF::Initialize(target);
  sdl::joystick::Init(target);
  sdl::controller::Init(target);

  // Initialization and Shutdown.
  Nan::SetPrototypeMethod(target, "init", sdl::Init);
  Nan::SetPrototypeMethod(target, "initSubSystem", sdl::InitSubSystem);
  Nan::SetPrototypeMethod(target, "wasInit", sdl::WasInit);
  Nan::SetPrototypeMethod(target, "quit", sdl::Quit);
  Nan::SetPrototypeMethod(target, "quitSubSystem", sdl::QuitSubSystem);

  // Display and Window Management.

  Nan::SetPrototypeMethod(target, "clearError", sdl::ClearError);
  Nan::SetPrototypeMethod(target, "getError", sdl::GetError);
  Nan::SetPrototypeMethod(target, "setError", sdl::SetError);

  Nan::SetPrototypeMethod(target, "mapRGB", sdl::MapRGB);
  Nan::SetPrototypeMethod(target, "mapRGBA", sdl::MapRGBA);
  Nan::SetPrototypeMethod(target, "getRGB", sdl::GetRGB);
  Nan::SetPrototypeMethod(target, "getRGBA", sdl::GetRGBA);

  Nan::SetPrototypeMethod(target, "AddHintCallback", sdl::AddHintCallback);
  Nan::SetPrototypeMethod(target, "getHint", sdl::GetHint);
  Nan::SetPrototypeMethod(target, "setHint", sdl::SetHint);
  Nan::SetPrototypeMethod(target, "setHintWithPriority", sdl::SetHintWithPriority);

  Nan::SetPrototypeMethod(target, "compiledVersion", sdl::CompiledVersion);
  Nan::SetPrototypeMethod(target, "compiledRevision", sdl::CompiledRevision);
  Nan::SetPrototypeMethod(target, "getRevision", sdl::GetRevision);
  Nan::SetPrototypeMethod(target, "getRevisionNumber", sdl::GetRevisionNumber);
  Nan::SetPrototypeMethod(target, "getVersion", sdl::GetVersion);

  Nan::SetPrototypeMethod(target, "getClipboardText", sdl::GetClipboardText);
  Nan::SetPrototypeMethod(target, "hasClipboardText", sdl::HasClipboardText);
  Nan::SetPrototypeMethod(target, "setClipboardText", sdl::SetClipboardText);

  Local<Object> INIT = Object::New();
  target->Set(String::New("INIT"), INIT);
  INIT->Set(String::New("TIMER"), Number::New(SDL_INIT_TIMER));
  INIT->Set(String::New("AUDIO"), Number::New(SDL_INIT_AUDIO));
  INIT->Set(String::New("VIDEO"), Number::New(SDL_INIT_VIDEO));
  INIT->Set(String::New("JOYSTICK"), Number::New(SDL_INIT_JOYSTICK));
  INIT->Set(String::New("HAPTIC"), Number::New(SDL_INIT_HAPTIC));
  INIT->Set(String::New("GAMECONTROLLER"), Number::New(SDL_INIT_GAMECONTROLLER));
  INIT->Set(String::New("EVENTS"), Number::New(SDL_INIT_EVENTS));
  INIT->Set(String::New("EVERYTHING"), Number::New(SDL_INIT_EVERYTHING));
  INIT->Set(String::New("NOPARACHUTE"), Number::New(SDL_INIT_NOPARACHUTE));

  Local<Object> EVENT = Object::New();
  target->Set(String::New("EVENT"), EVENT);
  EVENT->Set(String::New("DOLLARGESTURE"), Number::New(SDL_DOLLARGESTURE));
  EVENT->Set(String::New("DROPFILE"), Number::New(SDL_DROPFILE));
  EVENT->Set(String::New("FINGERMOTION"), Number::New(SDL_FINGERMOTION));
  EVENT->Set(String::New("FINGERUP"), Number::New(SDL_FINGERUP));
  EVENT->Set(String::New("KEYDOWN"), Number::New(SDL_KEYDOWN));
  EVENT->Set(String::New("KEYUP"), Number::New(SDL_KEYUP));
  EVENT->Set(String::New("JOYAXISMOTION"), Number::New(SDL_JOYAXISMOTION));
  EVENT->Set(String::New("JOYBALLMOTION"), Number::New(SDL_JOYBALLMOTION));
  EVENT->Set(String::New("JOYHATMOTION"), Number::New(SDL_JOYHATMOTION));
  EVENT->Set(String::New("JOYBUTTONDOWN"), Number::New(SDL_JOYBUTTONDOWN));
  EVENT->Set(String::New("JOYBUTTONUP"), Number::New(SDL_JOYBUTTONUP));
  EVENT->Set(String::New("MOUSEMOTION"), Number::New(SDL_MOUSEMOTION));
  EVENT->Set(String::New("MOUSEBUTTONDOWN"), Number::New(SDL_MOUSEBUTTONDOWN));
  EVENT->Set(String::New("MOUSEBUTTONUP"), Number::New(SDL_MOUSEBUTTONUP));
  EVENT->Set(String::New("MOUSEWHEEL"), Number::New(SDL_MOUSEWHEEL));
  EVENT->Set(String::New("MULTIGESTURE"), Number::New(SDL_MULTIGESTURE));
  EVENT->Set(String::New("QUIT"), Number::New(SDL_QUIT));
  EVENT->Set(String::New("SYSWMEVENT"), Number::New(SDL_SYSWMEVENT));
  EVENT->Set(String::New("TEXTEDITING"), Number::New(SDL_TEXTEDITING));
  EVENT->Set(String::New("TEXTINPUT"), Number::New(SDL_TEXTINPUT));
  EVENT->Set(String::New("USEREVENT"), Number::New(SDL_USEREVENT));
  EVENT->Set(String::New("WINDOWEVENT"), Number::New(SDL_WINDOWEVENT));

  // SDL Enumerations start:

  Local<Object> AUDIOFORMAT = Object::New();
  target->Set(String::New("AUDIOFORMAT"), AUDIOFORMAT);
  AUDIOFORMAT->Set(String::New("MASK_BITSIZE"), Number::New(SDL_AUDIO_MASK_BITSIZE));
  AUDIOFORMAT->Set(String::New("MASK_DATATYPE"), Number::New(SDL_AUDIO_MASK_DATATYPE));
  AUDIOFORMAT->Set(String::New("MASK_ENDIAN"), Number::New(SDL_AUDIO_MASK_ENDIAN));
  AUDIOFORMAT->Set(String::New("MASK_SIGNED"), Number::New(SDL_AUDIO_MASK_SIGNED));

  Local<Object> TEXTUREACCESS = Object::New();
  target->Set(String::New("TEXTUREACCESS"), TEXTUREACCESS);
  TEXTUREACCESS->Set(String::New("STATIC"), Number::New(SDL_TEXTUREACCESS_STATIC));
  TEXTUREACCESS->Set(String::New("STREAMING"), Number::New(SDL_TEXTUREACCESS_STREAMING));

  Local<Object> IMG = Object::New();
  target->Set(String::New("IMG"), IMG);

  Nan::SetPrototypeMethod(IMG, "load", sdl::IMG::Load);

  Local<Object> WM = Object::New();
  target->Set(String::New("WM"), WM);

  Local<Object> HINT = Object::New();
  target->Set(String::New("HINT"), HINT);
  HINT->Set(String::New("FRAMEBUFFER_ACCELERATION"), String::New(SDL_HINT_FRAMEBUFFER_ACCELERATION));
  HINT->Set(String::New("IDLE_TIMER_DISABLED"), String::New(SDL_HINT_IDLE_TIMER_DISABLED));
  HINT->Set(String::New("ORIENTATIONS"), String::New(SDL_HINT_ORIENTATIONS));
  HINT->Set(String::New("RENDER_DRIVER"), String::New(SDL_HINT_RENDER_DRIVER));
  HINT->Set(String::New("RENDER_OPENGL_SHADERS"), String::New(SDL_HINT_RENDER_OPENGL_SHADERS));
  HINT->Set(String::New("SCALE_QUALITY"), String::New(SDL_HINT_RENDER_SCALE_QUALITY));
  HINT->Set(String::New("RENDER_VSYNC"), String::New(SDL_HINT_RENDER_VSYNC));
  HINT->Set(String::New("DEFAULT"), Number::New(SDL_HINT_DEFAULT));
  HINT->Set(String::New("NORMAL"), Number::New(SDL_HINT_NORMAL));
  HINT->Set(String::New("OVERRIDE"), Number::New(SDL_HINT_OVERRIDE));

  Local<Object> RENDERER = Object::New();
  target->Set(String::New("RENDERER"), RENDERER);
  RENDERER->Set(String::New("SOFTWARE"), Number::New(SDL_RENDERER_SOFTWARE));
  RENDERER->Set(String::New("ACCELERATED"), Number::New(SDL_RENDERER_ACCELERATED));
  RENDERER->Set(String::New("PRESENTVSYNC"), Number::New(SDL_RENDERER_PRESENTVSYNC));
  RENDERER->Set(String::New("TARGETTEXTURE"), Number::New(SDL_RENDERER_TARGETTEXTURE));

  Local<Object> BLENDMODE = Object::New();
  target->Set(String::New("BLENDMODE"), BLENDMODE);
  BLENDMODE->Set(String::New("NONE"), Number::New(SDL_BLENDMODE_NONE));
  BLENDMODE->Set(String::New("BLEND"), Number::New(SDL_BLENDMODE_BLEND));
  BLENDMODE->Set(String::New("ADD"), Number::New(SDL_BLENDMODE_ADD));
  BLENDMODE->Set(String::New("MOD"), Number::New(SDL_BLENDMODE_MOD));

  Local<Object> FLIP = Object::New();
  target->Set(String::New("FLIP"), FLIP);
  FLIP->Set(String::New("NONE"), Number::New(SDL_FLIP_NONE));
  FLIP->Set(String::New("HORIZONTAL"), Number::New(SDL_FLIP_HORIZONTAL));
  FLIP->Set(String::New("VERTICAL"), Number::New(SDL_FLIP_VERTICAL));

  Local<Object> WINDOWPOS = Object::New();
  target->Set(String::New("WINDOWPOS"), WINDOWPOS);
  WINDOWPOS->Set(String::NewSymbol("CENTERED"), Number::New(SDL_WINDOWPOS_CENTERED));
  WINDOWPOS->Set(String::NewSymbol("UNDEFINED"), Number::New(SDL_WINDOWPOS_UNDEFINED));

  Local<Object> WINDOW = Object::New();
  target->Set(String::New("WINDOW"), WINDOW);
  WINDOW->Set(String::New("FULLSCREEN"), Number::New(SDL_WINDOW_FULLSCREEN));
  WINDOW->Set(String::New("FULLSCREEN_DESKTOP"), Number::New(SDL_WINDOW_FULLSCREEN_DESKTOP));
  WINDOW->Set(String::New("OPENGL"), Number::New(SDL_WINDOW_OPENGL));
  WINDOW->Set(String::New("HIDDEN"), Number::New(SDL_WINDOW_HIDDEN));
  WINDOW->Set(String::New("BORDERLESS"), Number::New(SDL_WINDOW_BORDERLESS));
  WINDOW->Set(String::New("RESIZABLE"), Number::New(SDL_WINDOW_RESIZABLE));
  WINDOW->Set(String::New("MINIMIZED"), Number::New(SDL_WINDOW_MINIMIZED));
  WINDOW->Set(String::New("MAXIMIZED"), Number::New(SDL_WINDOW_MAXIMIZED));
  WINDOW->Set(String::New("INPUT_GRABBED"), Number::New(SDL_WINDOW_INPUT_GRABBED));
  WINDOW->Set(String::New("ALLOW_HIGHDPI"), Number::New(SDL_WINDOW_ALLOW_HIGHDPI));
}


////////////////////////////////////////////////////////////////////////////////
// Initialization and Shutdown.

NAN_METHOD(sdl::Init) {

  SDL_SetMainReady();
  int init = (info[0]->IsUndefined() || !info[0]->IsNumber()) ? SDL_INIT_EVERYTHING : info[0]->Int32Value();
  // std::cout << "sdl::Init got: " << init << std::endl;
  if (SDL_Init(init) < 0) {
    return ThrowSDLException(__func__);
  }
  return Undefined();
}

NAN_METHOD(sdl::InitSubSystem) {


  if (!(info.Length() == 1 && info[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected InitSubSystem(Number)")));
  }

  if (SDL_InitSubSystem(info[0]->Int32Value()) < 0) return ThrowSDLException(__func__);

  return Undefined();
}

NAN_METHOD(sdl::Quit) {


  if (!(info.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Quit()")));
  }

  SDL_Quit();

  return Undefined();
}

NAN_METHOD(sdl::QuitSubSystem) {


  if (!(info.Length() == 1 && info[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected QuitSubSystem(Number)")));
  }

  SDL_QuitSubSystem(info[0]->Int32Value());

  return Undefined();
}

NAN_METHOD(sdl::WasInit) {


  if (!(info.Length() == 1 && info[0]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected WasInit(Number)")));
  }

  return Number::New(SDL_WasInit(info[0]->Int32Value()));
}

////////////////////////////////////////////////////////////////////////////////
// Display and Window Management.


////////////////////////////////////////////////////////////////////////////////
// Global SDL functions.
NAN_METHOD(sdl::DisableScreenSaver) {
  SDL_DisableScreenSaver();
  return Undefined();
}
NAN_METHOD(sdl::EnableScreenSaver) {
  SDL_EnableScreenSaver();
  return Undefined();
}
NAN_METHOD(sdl::IsScreenSaverEnabled) {


  SDL_bool ret = SDL_IsScreenSaverEnabled();
  info.GetReturnValue().Set(Boolean::New(ret));
}

NAN_METHOD(sdl::GetClosestDisplayMode) {


  if(info.Length() < 2) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected getClosestDisplayMode(Number, DisplayMode)")));
  }

  int index = info[0]->Int32Value();
  SDL_DisplayMode* mode = UnwrapDisplayMode(Handle<Object>::Cast(info[1]));
  SDL_DisplayMode* closest = new SDL_DisplayMode;
  SDL_DisplayMode* err = SDL_GetClosestDisplayMode(index, mode, closest);
  if(NULL == err) {
    delete closest;
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(WrapDisplayMode(closest));
}
NAN_METHOD(sdl::GetCurrentDisplayMode) {


  if(info.Length() < 1) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected getCurrentDisplayMode(Number)")));
  }

  int index = info[0]->Int32Value();
  SDL_DisplayMode* current = new SDL_DisplayMode;
  int err = SDL_GetCurrentDisplayMode(index, current);
  if(err < 0) {
    delete current;
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(WrapDisplayMode(current));
}
NAN_METHOD(sdl::GetCurrentVideoDriver) {


  const char* ret = SDL_GetCurrentVideoDriver();
  if(NULL == ret) {
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(String::New(ret));
}
NAN_METHOD(sdl::GetDesktopDisplayMode) {


  if(info.Length() < 1) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected getCurrentDisplayMode(Number)")));
  }

  int index = info[0]->Int32Value();
  SDL_DisplayMode* current = new SDL_DisplayMode;
  int err = SDL_GetDesktopDisplayMode(index, current);
  if(err < 0) {
    delete current;
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(WrapDisplayMode(current));
}
NAN_METHOD(sdl::GetDisplayBounds) {


  if(info.Length() < 1) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected getDisplayBounds(Number)")));
  }

  int index = info[0]->Int32Value();
  SDL_Rect* bounds = new SDL_Rect;
  int err = SDL_GetDisplayBounds(index, bounds);
  if(err < 0) {
    delete bounds;
    return ThrowSDLException(__func__);
  }

  NEW_WRAPPED(bounds, RectWrapper, ret);
//   Handle<Value> argv[] = {External::New(bounds)};
//   Handle<Object> ret = RectWrapper::tpl->GetFunction()->NewInstance(1, argv);
//   Handle<Object> ret = Object::New();
//   RectWrapper* wrap = new RectWrapper(ret);
//   wrap->wrapped = bounds;

  info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::GetDisplayMode) {


  if(info.Length() < 2) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected getDisplayMode(Number, Number)")));
  }

  int displayIndex = info[0]->Int32Value();
  int modeIndex = info[1]->Int32Value();
  SDL_DisplayMode* mode = new SDL_DisplayMode;
  int err = SDL_GetDisplayMode(displayIndex, modeIndex, mode);
  if(err < 0) {
    delete mode;
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(WrapDisplayMode(mode));
}
NAN_METHOD(sdl::GetDisplayName) {


  if(info.Length() < 0) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: expected getDisplayName(Number)")));
  }

  int index = info[0]->Int32Value();
  const char* ret = SDL_GetDisplayName(index);
  if(NULL == ret) {
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(String::New(ret));
}
NAN_METHOD(sdl::GetNumDisplayModes) {


  if(info.Length() < 0) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: expected getNumDisplayModes(Number)")));
  }

  int index = info[0]->Int32Value();
  int ret = SDL_GetNumDisplayModes(index);
  if(ret < 0) {
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(Number::New(ret));
}
NAN_METHOD(sdl::GetNumVideoDisplays) {


  int num = SDL_GetNumVideoDisplays();
  if(num < 0) {
    return ThrowSDLException(__func__);
  }
  info.GetReturnValue().Set(Number::New(num));
}
NAN_METHOD(sdl::GetNumVideoDrivers) {


  int num = SDL_GetNumVideoDrivers();
  if(num < 0) {
    return ThrowSDLException(__func__);
  }
  info.GetReturnValue().Set(Number::New(num));
}
NAN_METHOD(sdl::GetVideoDriver) {


  if(info.Length() < 1) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: expected getVideoDriver(Number)")));
  }

  int index = info[0]->Int32Value();
  const char* driver = SDL_GetVideoDriver(index);
  if(NULL == driver) {
    return ThrowSDLException(__func__);
  }
  info.GetReturnValue().Set(String::New(driver));
}

// NAN_METHOD(sdl::ShowMessageBox) {

// }
NAN_METHOD(sdl::ShowSimpleMessageBox) {


  if(info.Length() < 3) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: expected showSimpleMessageBox(Number, String, String, [Window])")));
  }
  else if(info.Length() < 4) {
    int flags = info[0]->Int32Value();
    String::Utf8Value title(info[1]);
    String::Utf8Value message(info[2]);
    int err = SDL_ShowSimpleMessageBox(flags, *title, *message, NULL);
    if(err < 0) {
      return ThrowSDLException(__func__);
    }
  }
  else {
    int flags = info[0]->Int32Value();
    String::Utf8Value title(info[1]);
    String::Utf8Value message(info[2]);
    WindowWrapper* window = node::ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[3]));
    int err = SDL_ShowSimpleMessageBox(flags, *title, *message, window->window_);
    if(err < 0) {
      return ThrowSDLException(__func__);
    }
  }

  return Undefined();
}

NAN_METHOD(sdl::VideoInit) {


  const char* driver = info[0]->IsUndefined() ? NULL : *(String::Utf8Value(info[0]));
  int err = SDL_VideoInit(driver);
  if(err < 0) {
    return ThrowSDLException(__func__);
  }
  info.GetReturnValue().Set(String::New(driver));
}
NAN_METHOD(sdl::VideoQuit) {
  SDL_VideoQuit();
  return Undefined();
}

////////////////////////////////////////////////////////////////////////////////

NAN_METHOD(sdl::ClearError) {


  if (!(info.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected ClearError()")));
  }

  SDL_ClearError();

  return Undefined();
}

NAN_METHOD(sdl::GetError) {


  if (!(info.Length() == 0)) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetError()")));
  }

  return String::New(SDL_GetError());
}

NAN_METHOD(sdl::SetError) {


  if (!(info.Length() == 1 && info[0]->IsString())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetError(String)")));
  }

  String::Utf8Value message(info[1]);

  SDL_SetError(*message);

  return Undefined();
}

NAN_METHOD(sdl::MapRGB) {


  if (!(info.Length() == 4 && info[0]->IsObject() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected MapRGB(PixelFormat, Number, Number, Number)")));
  }

  SDL_PixelFormat* fmt = UnwrapPixelFormat(info[0]->ToObject());
  int r = info[1]->Int32Value();
  int g = info[2]->Int32Value();
  int b = info[3]->Int32Value();

  return Number::New(SDL_MapRGB(fmt, r, g, b));
}

NAN_METHOD(sdl::MapRGBA) {


  if (!(info.Length() == 5 && info[0]->IsObject() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() && info[4]->IsNumber())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected MapRGBA(PixelFormat, Number, Number, Number, Number)")));
  }

  SDL_PixelFormat* fmt = UnwrapPixelFormat(info[0]->ToObject());
  int r = info[1]->Int32Value();
  int g = info[2]->Int32Value();
  int b = info[3]->Int32Value();
  int a = info[4]->Int32Value();

  return Number::New(SDL_MapRGBA(fmt, r, g, b, a));
}

NAN_METHOD(sdl::GetRGB) {


  if (!(info.Length() == 2 && info[0]->IsNumber() && info[1]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetRGB(Number, PixelFormat)")));
  }

  int pixel = info[0]->Int32Value();
  SDL_PixelFormat* fmt = UnwrapPixelFormat(info[1]->ToObject());
  ::Uint8 r, g, b;

  SDL_GetRGB(pixel, fmt, &r, &g, &b);

  Local<Object> rgb = Object::New();
  rgb->Set(String::New("r"), Number::New(r));
  rgb->Set(String::New("g"), Number::New(g));
  rgb->Set(String::New("b"), Number::New(b));

  info.GetReturnValue().Set(rgb);
}

NAN_METHOD(sdl::GetRGBA) {


  if (!(info.Length() == 2 && info[0]->IsNumber() && info[1]->IsObject())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetRGBA(Number, PixelFormat)")));
  }

  int pixel = info[0]->Int32Value();
  SDL_PixelFormat* fmt = UnwrapPixelFormat(info[1]->ToObject());
  ::Uint8 r, g, b, a;

  SDL_GetRGBA(pixel, fmt, &r, &g, &b, &a);

  Local<Object> rgba = Object::New();
  rgba->Set(String::New("r"), Number::New(r));
  rgba->Set(String::New("g"), Number::New(g));
  rgba->Set(String::New("b"), Number::New(b));
  rgba->Set(String::New("a"), Number::New(a));

  info.GetReturnValue().Set(rgba);
}

////////////////////////////////////////////////////////////////////////////////
// SDL Hint Handling.
static void HintCallbackHandler(void *userData, const char *name, const char *oldValue, const char *newValue) {


  Persistent<Function> callback = *static_cast<Persistent<Function>*>(userData);

  Local<Value> nodeName = String::New(name);
  Local<Value> nodeOldValue = String::New(oldValue);
  Local<Value> nodeNewValue = String::New(newValue);

  Local<Value> argv[3] = {nodeName, nodeOldValue, nodeNewValue};
  Local<Value> retValue = callback->Call(Context::GetCurrent()->Global(), 3, argv);
  Local<Boolean> ret = retValue->ToBoolean();
  if(ret->BooleanValue()) {
    SDL_DelHintCallback(name, HintCallbackHandler, userData);
    callback.Dispose();
  }
}

NAN_METHOD(sdl::AddHintCallback) {


  if(info.Length() < 2) {
    return ThrowException(Exception::TypeError(
      String::New("Invalid arguments: Expected AddHintCallback(String, Function)")));
  }

  String::Utf8Value name(info[0]);
  Handle<Function> callback = Handle<Function>::Cast(info[1]);
  Persistent<Function> userData = Persistent<Function>::New(callback);
  SDL_AddHintCallback(*name, HintCallbackHandler, static_cast<void*>(&userData));

  return Undefined();
}
// TODO: Implement a way to call SDL_ClearHints safely. Currently, because we store a Persistent
//       in the userData slot, this would leak memory due to those functions never being cleaned
//       up. Need some global list of Persistents to dispose of when this is called.
// TODO: Also implement a wrapper around SDL_DelHintCallback. (need to return a token or something
//       when adding a callback, because it's likely most callbacks will be anonymous so we won't
//       have the exact same Persistent address)
// NAN_METHOD(ClearHints) {
//
//   return Undefined();
// }
NAN_METHOD(sdl::GetHint) {


  if(info.Length() < 1) {
    return ThrowException(Exception::TypeError(
      String::New("Invalid arguments: Expected GetHint(String)")));
  }

  String::Utf8Value name(info[0]);
  const char *value = SDL_GetHint(*name);
  if(NULL == value) {
    return Undefined();
  }

  info.GetReturnValue().Set(String::New(value));
}
NAN_METHOD(sdl::SetHint) {


  if(info.Length() < 2) {
    return ThrowException(Exception::TypeError(
      String::New("Invalid arguments: Expected SetHint(String, String)")));
  }

  String::Utf8Value name(info[0]);
  String::Utf8Value value(info[1]);
  int err = SDL_SetHint(*name, *value);
  if(err < 0) {
    return ThrowSDLException(__func__);
  }

  return Undefined();
}
NAN_METHOD(sdl::SetHintWithPriority) {


  if(info.Length() < 3) {
    return ThrowException(Exception::TypeError(
      String::New("Invalid arguments: Excpected SetHintWithPriority(String, String, Number)")));
  }

  String::Utf8Value name(info[0]);
  String::Utf8Value value(info[1]);
  SDL_HintPriority priority = static_cast<SDL_HintPriority>(info[2]->Int32Value());
  SDL_bool ret = SDL_SetHintWithPriority(*name, *value, priority);

  info.GetReturnValue().Set(Boolean::New(ret ? true : false));
}

NAN_METHOD(sdl::CompiledVersion) {


  SDL_version version;
  SDL_VERSION(&version);

  Handle<Object> ret = Object::New();
  ret->Set(String::New("major"), Number::New(version.major));
  ret->Set(String::New("minor"), Number::New(version.minor));
  ret->Set(String::New("patch"), Number::New(version.patch));

  info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::CompiledRevision) {


  Handle<String> ret = String::New(SDL_REVISION);

  info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::GetRevision) {


  const char *revision = SDL_GetRevision();
  Handle<String> ret = String::New(revision);

  info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::GetRevisionNumber) {


  int revision = SDL_GetRevisionNumber();
  Handle<Value> ret = Number::New(revision);

  info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::GetVersion) {


  SDL_version version;
  SDL_GetVersion(&version);

  Handle<Object> ret = Object::New();
  ret->Set(String::New("major"), Number::New(version.major));
  ret->Set(String::New("minor"), Number::New(version.minor));
  ret->Set(String::New("patch"), Number::New(version.patch));

  info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::GetClipboardText) {


  char *text = SDL_GetClipboardText();
  if(NULL == text) {
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(String::New(text));
}
NAN_METHOD(sdl::HasClipboardText) {


  SDL_bool has = SDL_HasClipboardText();

  info.GetReturnValue().Set(Boolean::New(has ? true : false));
}
NAN_METHOD(sdl::SetClipboardText) {


  if(info.Length() < 1) {
    return ThrowException(Exception::TypeError(
      String::New("Invalid arguments: Expected SetClipboardText(String)")));
  }

  String::Utf8Value text(info[0]);
  int err = SDL_SetClipboardText(*text);
  if(err < 0) {
    return ThrowSDLException(__func__);
  }

  return Undefined();
}


// TODO: make an async version so this can be used in loops or parallel load images
NAN_METHOD(sdl::IMG::Load) {


  if (!(info.Length() == 1 && info[0]->IsString())) {
    return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected IMG::Load(String)")));
  }

  String::Utf8Value file(info[0]);

  SDL_Surface *image;
  image=IMG_Load(*file);
  if(!image) {
    return ThrowException(Exception::Error(String::Concat(
      String::New("IMG::Load: "),
      String::New(IMG_GetError())
    )));
  }

  NEW_WRAPPED(image, SurfaceWrapper, ret)

  info.GetReturnValue().Set(ret);
}

NODE_MODULE(node_sdl, init)
