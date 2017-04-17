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

  // sdl::InitWrappers(target);
  sdl::WindowWrapper::Init(target);
  sdl::RendererWrapper::Init(target);
  sdl::TextureWrapper::Init(target);
  sdl::SurfaceWrapper::Init(target);
  // sdl::ColorWrapper::Init(target);
  // sdl::RectWrapper::Init(target);
  sdl::gl::Init(target);
  sdl::event::Init(target);
  sdl::key::Init(target);
  sdl::mouse::Init(target);
  sdl::TTF::Initialize(target);
  sdl::joystick::Init(target);
  sdl::controller::Init(target);

  // Initialization and Shutdown.
  Nan::Export(target, "init", sdl::Init);
  Nan::Export(target, "initSubSystem", sdl::InitSubSystem);
  Nan::Export(target, "wasInit", sdl::WasInit);
  Nan::Export(target, "quit", sdl::Quit);
  Nan::Export(target, "quitSubSystem", sdl::QuitSubSystem);

  // Display and Window Management.

  Nan::Export(target, "clearError", sdl::ClearError);
  Nan::Export(target, "getError", sdl::GetError);
  Nan::Export(target, "setError", sdl::SetError);

  Nan::Export(target, "mapRGB", sdl::MapRGB);
  Nan::Export(target, "mapRGBA", sdl::MapRGBA);
  Nan::Export(target, "getRGB", sdl::GetRGB);
  Nan::Export(target, "getRGBA", sdl::GetRGBA);

  Nan::Export(target, "AddHintCallback", sdl::AddHintCallback);
  Nan::Export(target, "getHint", sdl::GetHint);
  Nan::Export(target, "setHint", sdl::SetHint);
  Nan::Export(target, "setHintWithPriority", sdl::SetHintWithPriority);

  Nan::Export(target, "compiledVersion", sdl::CompiledVersion);
  Nan::Export(target, "compiledRevision", sdl::CompiledRevision);
  Nan::Export(target, "getRevision", sdl::GetRevision);
  Nan::Export(target, "getRevisionNumber", sdl::GetRevisionNumber);
  Nan::Export(target, "getVersion", sdl::GetVersion);

  Nan::Export(target, "getClipboardText", sdl::GetClipboardText);
  Nan::Export(target, "hasClipboardText", sdl::HasClipboardText);
  Nan::Export(target, "setClipboardText", sdl::SetClipboardText);

  Local<Object> INIT = Nan::New<Object>();
  target->Set(Nan::New("INIT").ToLocalChecked(), INIT);
  INIT->Set(Nan::New("TIMER").ToLocalChecked(), Nan::New<Number>(SDL_INIT_TIMER));
  INIT->Set(Nan::New("AUDIO").ToLocalChecked(), Nan::New<Number>(SDL_INIT_AUDIO));
  INIT->Set(Nan::New("VIDEO").ToLocalChecked(), Nan::New<Number>(SDL_INIT_VIDEO));
  INIT->Set(Nan::New("JOYSTICK").ToLocalChecked(), Nan::New<Number>(SDL_INIT_JOYSTICK));
  INIT->Set(Nan::New("HAPTIC").ToLocalChecked(), Nan::New<Number>(SDL_INIT_HAPTIC));
  INIT->Set(Nan::New("GAMECONTROLLER").ToLocalChecked(), Nan::New<Number>(SDL_INIT_GAMECONTROLLER));
  INIT->Set(Nan::New("EVENTS").ToLocalChecked(), Nan::New<Number>(SDL_INIT_EVENTS));
  INIT->Set(Nan::New("EVERYTHING").ToLocalChecked(), Nan::New<Number>(SDL_INIT_EVERYTHING));
  INIT->Set(Nan::New("NOPARACHUTE").ToLocalChecked(), Nan::New<Number>(SDL_INIT_NOPARACHUTE));

  Local<Object> EVENT = Nan::New<Object>();
  target->Set(Nan::New("EVENT").ToLocalChecked(), EVENT);
  EVENT->Set(Nan::New("DOLLARGESTURE").ToLocalChecked(), Nan::New<Number>(SDL_DOLLARGESTURE));
  EVENT->Set(Nan::New("DROPFILE").ToLocalChecked(), Nan::New<Number>(SDL_DROPFILE));
  EVENT->Set(Nan::New("FINGERMOTION").ToLocalChecked(), Nan::New<Number>(SDL_FINGERMOTION));
  EVENT->Set(Nan::New("FINGERUP").ToLocalChecked(), Nan::New<Number>(SDL_FINGERUP));
  EVENT->Set(Nan::New("KEYDOWN").ToLocalChecked(), Nan::New<Number>(SDL_KEYDOWN));
  EVENT->Set(Nan::New("KEYUP").ToLocalChecked(), Nan::New<Number>(SDL_KEYUP));
  EVENT->Set(Nan::New("JOYAXISMOTION").ToLocalChecked(), Nan::New<Number>(SDL_JOYAXISMOTION));
  EVENT->Set(Nan::New("JOYBALLMOTION").ToLocalChecked(), Nan::New<Number>(SDL_JOYBALLMOTION));
  EVENT->Set(Nan::New("JOYHATMOTION").ToLocalChecked(), Nan::New<Number>(SDL_JOYHATMOTION));
  EVENT->Set(Nan::New("JOYBUTTONDOWN").ToLocalChecked(), Nan::New<Number>(SDL_JOYBUTTONDOWN));
  EVENT->Set(Nan::New("JOYBUTTONUP").ToLocalChecked(), Nan::New<Number>(SDL_JOYBUTTONUP));
  EVENT->Set(Nan::New("MOUSEMOTION").ToLocalChecked(), Nan::New<Number>(SDL_MOUSEMOTION));
  EVENT->Set(Nan::New("MOUSEBUTTONDOWN").ToLocalChecked(), Nan::New<Number>(SDL_MOUSEBUTTONDOWN));
  EVENT->Set(Nan::New("MOUSEBUTTONUP").ToLocalChecked(), Nan::New<Number>(SDL_MOUSEBUTTONUP));
  EVENT->Set(Nan::New("MOUSEWHEEL").ToLocalChecked(), Nan::New<Number>(SDL_MOUSEWHEEL));
  EVENT->Set(Nan::New("MULTIGESTURE").ToLocalChecked(), Nan::New<Number>(SDL_MULTIGESTURE));
  EVENT->Set(Nan::New("QUIT").ToLocalChecked(), Nan::New<Number>(SDL_QUIT));
  EVENT->Set(Nan::New("SYSWMEVENT").ToLocalChecked(), Nan::New<Number>(SDL_SYSWMEVENT));
  EVENT->Set(Nan::New("TEXTEDITING").ToLocalChecked(), Nan::New<Number>(SDL_TEXTEDITING));
  EVENT->Set(Nan::New("TEXTINPUT").ToLocalChecked(), Nan::New<Number>(SDL_TEXTINPUT));
  EVENT->Set(Nan::New("USEREVENT").ToLocalChecked(), Nan::New<Number>(SDL_USEREVENT));
  EVENT->Set(Nan::New("WINDOWEVENT").ToLocalChecked(), Nan::New<Number>(SDL_WINDOWEVENT));

  // SDL Enumerations start:

  Local<Object> AUDIOFORMAT = Nan::New<Object>();
  target->Set(Nan::New("AUDIOFORMAT").ToLocalChecked(), AUDIOFORMAT);
  AUDIOFORMAT->Set(Nan::New("MASK_BITSIZE").ToLocalChecked(), Nan::New<Number>(SDL_AUDIO_MASK_BITSIZE));
  AUDIOFORMAT->Set(Nan::New("MASK_DATATYPE").ToLocalChecked(), Nan::New<Number>(SDL_AUDIO_MASK_DATATYPE));
  AUDIOFORMAT->Set(Nan::New("MASK_ENDIAN").ToLocalChecked(), Nan::New<Number>(SDL_AUDIO_MASK_ENDIAN));
  AUDIOFORMAT->Set(Nan::New("MASK_SIGNED").ToLocalChecked(), Nan::New<Number>(SDL_AUDIO_MASK_SIGNED));

  Local<Object> TEXTUREACCESS = Nan::New<Object>();
  target->Set(Nan::New("TEXTUREACCESS").ToLocalChecked(), TEXTUREACCESS);
  TEXTUREACCESS->Set(Nan::New("STATIC").ToLocalChecked(), Nan::New<Number>(SDL_TEXTUREACCESS_STATIC));
  TEXTUREACCESS->Set(Nan::New("STREAMING").ToLocalChecked(), Nan::New<Number>(SDL_TEXTUREACCESS_STREAMING));

  Local<Object> IMG = Nan::New<Object>();
  target->Set(Nan::New("IMG").ToLocalChecked(), IMG);

  Nan::Export(IMG, "load", sdl::IMG::Load);

  Local<Object> WM = Nan::New<Object>();
  target->Set(Nan::New("WM").ToLocalChecked(), WM);

  Local<Object> HINT = Nan::New<Object>();
  target->Set(Nan::New("HINT").ToLocalChecked(), HINT);
  HINT->Set(Nan::New("FRAMEBUFFER_ACCELERATION").ToLocalChecked(), Nan::New(SDL_HINT_FRAMEBUFFER_ACCELERATION).ToLocalChecked());
  HINT->Set(Nan::New("IDLE_TIMER_DISABLED").ToLocalChecked(), Nan::New(SDL_HINT_IDLE_TIMER_DISABLED).ToLocalChecked());
  HINT->Set(Nan::New("ORIENTATIONS").ToLocalChecked(), Nan::New(SDL_HINT_ORIENTATIONS).ToLocalChecked());
  HINT->Set(Nan::New("RENDER_DRIVER").ToLocalChecked(), Nan::New(SDL_HINT_RENDER_DRIVER).ToLocalChecked());
  HINT->Set(Nan::New("RENDER_OPENGL_SHADERS").ToLocalChecked(), Nan::New(SDL_HINT_RENDER_OPENGL_SHADERS).ToLocalChecked());
  HINT->Set(Nan::New("SCALE_QUALITY").ToLocalChecked(), Nan::New(SDL_HINT_RENDER_SCALE_QUALITY).ToLocalChecked());
  HINT->Set(Nan::New("RENDER_VSYNC").ToLocalChecked(), Nan::New(SDL_HINT_RENDER_VSYNC).ToLocalChecked());
  HINT->Set(Nan::New("DEFAULT").ToLocalChecked(), Nan::New<Number>(SDL_HINT_DEFAULT));
  HINT->Set(Nan::New("NORMAL").ToLocalChecked(), Nan::New<Number>(SDL_HINT_NORMAL));
  HINT->Set(Nan::New("OVERRIDE").ToLocalChecked(), Nan::New<Number>(SDL_HINT_OVERRIDE));

  Local<Object> RENDERER = Nan::New<Object>();
  target->Set(Nan::New("RENDERER").ToLocalChecked(), RENDERER);
  RENDERER->Set(Nan::New("SOFTWARE").ToLocalChecked(), Nan::New<Number>(SDL_RENDERER_SOFTWARE));
  RENDERER->Set(Nan::New("ACCELERATED").ToLocalChecked(), Nan::New<Number>(SDL_RENDERER_ACCELERATED));
  RENDERER->Set(Nan::New("PRESENTVSYNC").ToLocalChecked(), Nan::New<Number>(SDL_RENDERER_PRESENTVSYNC));
  RENDERER->Set(Nan::New("TARGETTEXTURE").ToLocalChecked(), Nan::New<Number>(SDL_RENDERER_TARGETTEXTURE));

  Local<Object> BLENDMODE = Nan::New<Object>();
  target->Set(Nan::New("BLENDMODE").ToLocalChecked(), BLENDMODE);
  BLENDMODE->Set(Nan::New("NONE").ToLocalChecked(), Nan::New<Number>(SDL_BLENDMODE_NONE));
  BLENDMODE->Set(Nan::New("BLEND").ToLocalChecked(), Nan::New<Number>(SDL_BLENDMODE_BLEND));
  BLENDMODE->Set(Nan::New("ADD").ToLocalChecked(), Nan::New<Number>(SDL_BLENDMODE_ADD));
  BLENDMODE->Set(Nan::New("MOD").ToLocalChecked(), Nan::New<Number>(SDL_BLENDMODE_MOD));

  Local<Object> FLIP = Nan::New<Object>();
  target->Set(Nan::New("FLIP").ToLocalChecked(), FLIP);
  FLIP->Set(Nan::New("NONE").ToLocalChecked(), Nan::New<Number>(SDL_FLIP_NONE));
  FLIP->Set(Nan::New("HORIZONTAL").ToLocalChecked(), Nan::New<Number>(SDL_FLIP_HORIZONTAL));
  FLIP->Set(Nan::New("VERTICAL").ToLocalChecked(), Nan::New<Number>(SDL_FLIP_VERTICAL));

  Local<Object> WINDOWPOS = Nan::New<Object>();
  target->Set(Nan::New("WINDOWPOS").ToLocalChecked(), WINDOWPOS);
  WINDOWPOS->Set(STRING_NEW("CENTERED"), Nan::New<Number>(SDL_WINDOWPOS_CENTERED));
  WINDOWPOS->Set(STRING_NEW("UNDEFINED"), Nan::New<Number>(SDL_WINDOWPOS_UNDEFINED));

  Local<Object> WINDOW = Nan::New<Object>();
  target->Set(Nan::New("WINDOW").ToLocalChecked(), WINDOW);
  WINDOW->Set(Nan::New("FULLSCREEN").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_FULLSCREEN));
  WINDOW->Set(Nan::New("FULLSCREEN_DESKTOP").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_FULLSCREEN_DESKTOP));
  WINDOW->Set(Nan::New("OPENGL").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_OPENGL));
  WINDOW->Set(Nan::New("HIDDEN").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_HIDDEN));
  WINDOW->Set(Nan::New("BORDERLESS").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_BORDERLESS));
  WINDOW->Set(Nan::New("RESIZABLE").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_RESIZABLE));
  WINDOW->Set(Nan::New("MINIMIZED").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_MINIMIZED));
  WINDOW->Set(Nan::New("MAXIMIZED").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_MAXIMIZED));
  WINDOW->Set(Nan::New("INPUT_GRABBED").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_INPUT_GRABBED));
  WINDOW->Set(Nan::New("ALLOW_HIGHDPI").ToLocalChecked(), Nan::New<Number>(SDL_WINDOW_ALLOW_HIGHDPI));
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
}

NAN_METHOD(sdl::InitSubSystem) {
  if (!(info.Length() == 1 && info[0]->IsNumber())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected InitSubSystem(Number)"));
		return;
  }

  if (SDL_InitSubSystem(info[0]->Int32Value()) < 0) {
    ThrowSDLException(__func__);
    return;
  }
}

NAN_METHOD(sdl::Quit) {
  if (!(info.Length() == 0)) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected Quit()"));
		return;
  }

  SDL_Quit();
}

NAN_METHOD(sdl::QuitSubSystem) {
  if (!(info.Length() == 1 && info[0]->IsNumber())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected QuitSubSystem(Number)"));
		return;
  }

  SDL_QuitSubSystem(info[0]->Int32Value());
}

NAN_METHOD(sdl::WasInit) {
  if (!(info.Length() == 1 && info[0]->IsNumber())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected WasInit(Number)"));
		return;
  }

  info.GetReturnValue().Set(Nan::New<Number>(SDL_WasInit(info[0]->Int32Value())));
}

////////////////////////////////////////////////////////////////////////////////
// Display and Window Management.


////////////////////////////////////////////////////////////////////////////////
// Global SDL functions.
NAN_METHOD(sdl::DisableScreenSaver) {
  SDL_DisableScreenSaver();
}

NAN_METHOD(sdl::EnableScreenSaver) {
  SDL_EnableScreenSaver();
}

NAN_METHOD(sdl::IsScreenSaverEnabled) {
  SDL_bool ret = SDL_IsScreenSaverEnabled();
  info.GetReturnValue().Set(Nan::New<Boolean>(ret));
}

NAN_METHOD(sdl::GetClosestDisplayMode) {
  if(info.Length() < 2) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected getClosestDisplayMode(Number, DisplayMode)"));
		return;
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
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected getCurrentDisplayMode(Number)"));
		return;
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

  info.GetReturnValue().Set(Nan::New(ret).ToLocalChecked());
}

NAN_METHOD(sdl::GetDesktopDisplayMode) {
  if(info.Length() < 1) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected getCurrentDisplayMode(Number)"));
		return;
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
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected getDisplayBounds(Number)"));
		return;
  }

  int index = info[0]->Int32Value();
  SDL_Rect* bounds = new SDL_Rect;
  int err = SDL_GetDisplayBounds(index, bounds);
  if(err < 0) {
    delete bounds;
    return ThrowSDLException(__func__);
  }


//   Handle<Value> argv[] = {External::New(bounds)};
//   Handle<Object> ret = RectWrapper::tpl->GetFunction()->NewInstance(1, argv);
//   Handle<Object> ret = Nan::New<Object>();
//   RectWrapper* wrap = new RectWrapper(ret);
//   wrap->wrapped = bounds;

  // TODO: Jesper
  // NEW_WRAPPED(bounds, RectWrapper, ret);
  // info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::GetDisplayMode) {
  if(info.Length() < 2) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected getDisplayMode(Number, Number)"));
		return;
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
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected getDisplayName(Number)"));
		return;
  }

  int index = info[0]->Int32Value();
  const char* ret = SDL_GetDisplayName(index);
  if(NULL == ret) {
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(Nan::New(ret).ToLocalChecked());
}

NAN_METHOD(sdl::GetNumDisplayModes) {
  if(info.Length() < 0) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected getNumDisplayModes(Number)"));
		return;
  }

  int index = info[0]->Int32Value();
  int ret = SDL_GetNumDisplayModes(index);
  if(ret < 0) {
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(Nan::New<Number>(ret));
}

NAN_METHOD(sdl::GetNumVideoDisplays) {
  int num = SDL_GetNumVideoDisplays();
  if(num < 0) {
    return ThrowSDLException(__func__);
  }
  info.GetReturnValue().Set(Nan::New<Number>(num));
}

NAN_METHOD(sdl::GetNumVideoDrivers) {
  int num = SDL_GetNumVideoDrivers();
  if(num < 0) {
    return ThrowSDLException(__func__);
  }
  info.GetReturnValue().Set(Nan::New<Number>(num));
}

NAN_METHOD(sdl::GetVideoDriver) {
  if(info.Length() < 1) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected getVideoDriver(Number)"));
		return;
  }

  int index = info[0]->Int32Value();
  const char* driver = SDL_GetVideoDriver(index);
  if(NULL == driver) {
    return ThrowSDLException(__func__);
  }
  info.GetReturnValue().Set(Nan::New(driver).ToLocalChecked());
}

// NAN_METHOD(sdl::ShowMessageBox) {
// }

NAN_METHOD(sdl::ShowSimpleMessageBox) {
  if(info.Length() < 3) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected showSimpleMessageBox(Number, String, String, [Window])"));
		return;
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
    WindowWrapper* window = Nan::ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[3]));
    int err = SDL_ShowSimpleMessageBox(flags, *title, *message, window->window_);
    if(err < 0) {
      return ThrowSDLException(__func__);
    }
  }
}

NAN_METHOD(sdl::VideoInit) {
  const char* driver = info[0]->IsUndefined() ? NULL : *(String::Utf8Value(info[0]));
  int err = SDL_VideoInit(driver);
  if(err < 0) {
    return ThrowSDLException(__func__);
  }
  info.GetReturnValue().Set(Nan::New(driver).ToLocalChecked());
}

NAN_METHOD(sdl::VideoQuit) {
  SDL_VideoQuit();
}

////////////////////////////////////////////////////////////////////////////////

NAN_METHOD(sdl::ClearError) {
  if (!(info.Length() == 0)) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected ClearError()"));
		return;
  }

  SDL_ClearError();
}

NAN_METHOD(sdl::GetError) {
  if (!(info.Length() == 0)) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetError()"));
		return;
  }

  info.GetReturnValue().Set(STRING_NEW(SDL_GetError()));
}

NAN_METHOD(sdl::SetError) {
  if (!(info.Length() == 1 && info[0]->IsString())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected SetError(String)"));
		return;
  }

  String::Utf8Value message(info[1]);

  SDL_SetError(*message);
}

NAN_METHOD(sdl::MapRGB) {
  if (!(info.Length() == 4 && info[0]->IsObject() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected MapRGB(PixelFormat, Number, Number, Number)"));
		return;
  }

  SDL_PixelFormat* fmt = UnwrapPixelFormat(info[0]->ToObject());
  int r = info[1]->Int32Value();
  int g = info[2]->Int32Value();
  int b = info[3]->Int32Value();

  info.GetReturnValue().Set(Nan::New<Number>(SDL_MapRGB(fmt, r, g, b)));
}

NAN_METHOD(sdl::MapRGBA) {
  if (!(info.Length() == 5 && info[0]->IsObject() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() && info[4]->IsNumber())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected MapRGBA(PixelFormat, Number, Number, Number, Number)"));
		return;
  }

  SDL_PixelFormat* fmt = UnwrapPixelFormat(info[0]->ToObject());
  int r = info[1]->Int32Value();
  int g = info[2]->Int32Value();
  int b = info[3]->Int32Value();
  int a = info[4]->Int32Value();

  info.GetReturnValue().Set(Nan::New<Number>(SDL_MapRGBA(fmt, r, g, b, a)));
}

NAN_METHOD(sdl::GetRGB) {
  if (!(info.Length() == 2 && info[0]->IsNumber() && info[1]->IsObject())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetRGB(Number, PixelFormat)"));
		return;
  }

  int pixel = info[0]->Int32Value();
  SDL_PixelFormat* fmt = UnwrapPixelFormat(info[1]->ToObject());
  ::Uint8 r, g, b;

  SDL_GetRGB(pixel, fmt, &r, &g, &b);

  Local<Object> rgb = Nan::New<Object>();
  rgb->Set(Nan::New("r").ToLocalChecked(), Nan::New<Number>(r));
  rgb->Set(Nan::New("g").ToLocalChecked(), Nan::New<Number>(g));
  rgb->Set(Nan::New("b").ToLocalChecked(), Nan::New<Number>(b));

  info.GetReturnValue().Set(rgb);
}

NAN_METHOD(sdl::GetRGBA) {
  if (!(info.Length() == 2 && info[0]->IsNumber() && info[1]->IsObject())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetRGBA(Number, PixelFormat)"));
		return;
  }

  int pixel = info[0]->Int32Value();
  SDL_PixelFormat* fmt = UnwrapPixelFormat(info[1]->ToObject());
  ::Uint8 r, g, b, a;

  SDL_GetRGBA(pixel, fmt, &r, &g, &b, &a);

  Local<Object> rgba = Nan::New<Object>();
  rgba->Set(Nan::New("r").ToLocalChecked(), Nan::New<Number>(r));
  rgba->Set(Nan::New("g").ToLocalChecked(), Nan::New<Number>(g));
  rgba->Set(Nan::New("b").ToLocalChecked(), Nan::New<Number>(b));
  rgba->Set(Nan::New("a").ToLocalChecked(), Nan::New<Number>(a));

  info.GetReturnValue().Set(rgba);
}

////////////////////////////////////////////////////////////////////////////////
// SDL Hint Handling.
static void HintCallbackHandler(void *userData, const char *name, const char *oldValue, const char *newValue) {
  Nan::Callback *callback = static_cast<Nan::Callback*>(userData);

  Local<Value> nodeName = Nan::New(name).ToLocalChecked();
  Local<Value> nodeOldValue = Nan::New(oldValue).ToLocalChecked();
  Local<Value> nodeNewValue = Nan::New(newValue).ToLocalChecked();

  Local<Value> argv[3] = {nodeName, nodeOldValue, nodeNewValue};
  Local<Value> retValue = callback->Call(Nan::GetCurrentContext()->Global(), 3, argv);
  Local<Boolean> ret = retValue->ToBoolean();
  if(ret->BooleanValue()) {
    SDL_DelHintCallback(name, HintCallbackHandler, userData);
    delete callback;
  }
}

NAN_METHOD(sdl::AddHintCallback) {
  if(info.Length() < 2) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected AddHintCallback(String, Function)"));
		return;
  }

  String::Utf8Value name(info[0]);
  Nan::Callback *callback = new Nan::Callback(info[1].As<Function>());
  SDL_AddHintCallback(*name, HintCallbackHandler, static_cast<void*>(callback));
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
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetHint(String)"));
		return;
  }

  String::Utf8Value name(info[0]);
  const char *value = SDL_GetHint(*name);
  if(NULL == value) {
    return;
  }

  info.GetReturnValue().Set(Nan::New(value).ToLocalChecked());
}

NAN_METHOD(sdl::SetHint) {
  if(info.Length() < 2) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected SetHint(String, String)"));
		return;
  }

  String::Utf8Value name(info[0]);
  String::Utf8Value value(info[1]);
  int err = SDL_SetHint(*name, *value);
  if(err < 0) {
    return ThrowSDLException(__func__);
  }
}

NAN_METHOD(sdl::SetHintWithPriority) {
  if(info.Length() < 3) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Excpected SetHintWithPriority(String, String, Number)"));
		return;
  }

  String::Utf8Value name(info[0]);
  String::Utf8Value value(info[1]);
  SDL_HintPriority priority = static_cast<SDL_HintPriority>(info[2]->Int32Value());
  SDL_bool ret = SDL_SetHintWithPriority(*name, *value, priority);

  info.GetReturnValue().Set(Nan::New<Boolean>(ret ? true : false));
}

NAN_METHOD(sdl::CompiledVersion) {
  SDL_version version;
  SDL_VERSION(&version);

  Handle<Object> ret = Nan::New<Object>();
  ret->Set(Nan::New("major").ToLocalChecked(), Nan::New<Number>(version.major));
  ret->Set(Nan::New("minor").ToLocalChecked(), Nan::New<Number>(version.minor));
  ret->Set(Nan::New("patch").ToLocalChecked(), Nan::New<Number>(version.patch));

  info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::CompiledRevision) {
  Handle<String> ret = Nan::New(SDL_REVISION).ToLocalChecked();

  info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::GetRevision) {
  const char *revision = SDL_GetRevision();
  Handle<String> ret = Nan::New(revision).ToLocalChecked();

  info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::GetRevisionNumber) {
  int revision = SDL_GetRevisionNumber();
  Handle<Value> ret = Nan::New<Number>(revision);

  info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::GetVersion) {
  SDL_version version;
  SDL_GetVersion(&version);

  Handle<Object> ret = Nan::New<Object>();
  ret->Set(Nan::New("major").ToLocalChecked(), Nan::New<Number>(version.major));
  ret->Set(Nan::New("minor").ToLocalChecked(), Nan::New<Number>(version.minor));
  ret->Set(Nan::New("patch").ToLocalChecked(), Nan::New<Number>(version.patch));

  info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::GetClipboardText) {
  char *text = SDL_GetClipboardText();
  if(NULL == text) {
    return ThrowSDLException(__func__);
  }

  info.GetReturnValue().Set(Nan::New(text).ToLocalChecked());
}

NAN_METHOD(sdl::HasClipboardText) {
  SDL_bool has = SDL_HasClipboardText();

  info.GetReturnValue().Set(Nan::New<Boolean>(has ? true : false));
}

NAN_METHOD(sdl::SetClipboardText) {
  if(info.Length() < 1) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected SetClipboardText(String)"));
		return;
  }

  String::Utf8Value text(info[0]);
  int err = SDL_SetClipboardText(*text);
  if(err < 0) {
    return ThrowSDLException(__func__);
  }
}

// TODO: make an async version so this can be used in loops or parallel load images
NAN_METHOD(sdl::IMG::Load) {
  if (!(info.Length() == 1 && info[0]->IsString())) {
    Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected IMG::Load(String)"));
		return;
  }

  String::Utf8Value file(info[0]);

  SDL_Surface *image;
  image=IMG_Load(*file);
  if(!image) {
    Nan::ThrowError(String::Concat(
      Nan::New("IMG::Load: ").ToLocalChecked(),
      STRING_NEW(IMG_GetError())
    ));
    return;
  }

  // TODO: Jesper
  // NEW_WRAPPED(image, SurfaceWrapper, ret)
  // info.GetReturnValue().Set(ret);
}

NODE_MODULE(node_sdl, init)
