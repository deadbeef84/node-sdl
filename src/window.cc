#include <string>
#include <iostream>

#include "window.h"
#include "helpers.h"
#include "struct_wrappers.h"
#include "surface.h"
#include "container.h"

using namespace v8;

////////////////////////////////////////////////////////////////////////////////
// WindowWrapper class definition.
Persistent<FunctionTemplate> sdl::WindowWrapper::constructor;

sdl::WindowWrapper::WindowWrapper() {
}

sdl::WindowWrapper::WindowWrapper(Handle<Object> obj) {
	Wrap(obj);
}

sdl::WindowWrapper::~WindowWrapper() {
	std::cout << "WindowWrapper destructor running." << std::endl;
	if(NULL != window_) {
		std::cout << "Destroying contained window." << std::endl;
		SDL_DestroyWindow(window_);
	}
}

NAN_MODULE_INIT(sdl::WindowWrapper::Init) {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("WindowWrapper"));

	Nan::SetPrototypeMethod(tpl, "getBrightness", GetBrightness);
	Nan::SetPrototypeMethod(tpl, "getDisplayMode", GetDisplayMode);
	Nan::SetPrototypeMethod(tpl, "getDisplayIndex", GetDisplayIndex);
	Nan::SetPrototypeMethod(tpl, "getFlags", GetFlags);
	Nan::SetPrototypeMethod(tpl, "getGammaRamp", GetGammaRamp);
	Nan::SetPrototypeMethod(tpl, "getGrab", GetGrab);
	Nan::SetPrototypeMethod(tpl, "getWindowID", GetWindowID);
	Nan::SetPrototypeMethod(tpl, "getMaximumSize", GetMaximumSize);
	Nan::SetPrototypeMethod(tpl, "getMinimumSize", GetMinimumSize);
	Nan::SetPrototypeMethod(tpl, "getPixelFormat", GetPixelFormat);
	Nan::SetPrototypeMethod(tpl, "getPosition", GetPosition);
	Nan::SetPrototypeMethod(tpl, "getSize", GetSize);
	Nan::SetPrototypeMethod(tpl, "getSurface", GetSurface);
	Nan::SetPrototypeMethod(tpl, "getTitle", GetTitle);

	Nan::SetPrototypeMethod(tpl, "hide", Hide);
	Nan::SetPrototypeMethod(tpl, "show", Show);

	Nan::SetPrototypeMethod(tpl, "minimize", Minimize);
	Nan::SetPrototypeMethod(tpl, "maximize", Maximize);

	Nan::SetPrototypeMethod(tpl, "raise", Raise);
	Nan::SetPrototypeMethod(tpl, "restore", Restore);

	Nan::SetPrototypeMethod(tpl, "setBordered", SetBordered);
	Nan::SetPrototypeMethod(tpl, "setBrightness", SetBrightness);
	Nan::SetPrototypeMethod(tpl, "setDisplayMode", SetDisplayMode);
	Nan::SetPrototypeMethod(tpl, "setFullscreen", SetFullscreen);
	Nan::SetPrototypeMethod(tpl, "setGammeRamp", SetGammaRamp);
	Nan::SetPrototypeMethod(tpl, "setGrab", SetGrab);
	Nan::SetPrototypeMethod(tpl, "setIcon", SetIcon);
	Nan::SetPrototypeMethod(tpl, "setMaximumSize", SetMaximumSize);
	Nan::SetPrototypeMethod(tpl, "setMinimumSize", SetMinimumSize);
	Nan::SetPrototypeMethod(tpl, "setPosition", SetPosition);
	Nan::SetPrototypeMethod(tpl, "setSize", SetSize);
	Nan::SetPrototypeMethod(tpl, "setTitle", SetTitle);

	Nan::SetPrototypeMethod(tpl, "updateWindowSurface", UpdateWindowSurface);
	Nan::SetPrototypeMethod(tpl, "updateWindowSurfaceRects", UpdateWindowSurfaceRects);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Window"), constructor);
}

NAN_METHOD(sdl::WindowWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Use the new operator to create instances of a Window.")));
	}



	std::string title = args[0]->IsUndefined() ? "" : *(String::Utf8Value(args[0]));
	int x = args[1]->IsUndefined() ? SDL_WINDOWPOS_UNDEFINED : args[1]->Int32Value();
	int y = args[2]->IsUndefined() ? SDL_WINDOWPOS_UNDEFINED : args[2]->Int32Value();
	int w = args[3]->IsUndefined() ? 640 : args[3]->Int32Value();
	int h = args[4]->IsUndefined() ? 480 : args[4]->Int32Value();
	uint32_t flags = args[5]->IsUndefined() ? 0 : args[5]->Int32Value();

	WindowWrapper* obj = new WindowWrapper();
	obj->window_ = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	if(NULL == obj->window_) {
		delete obj;
		return ThrowSDLException("Window->New");
	}

	obj->Wrap(args.This());
	info.GetReturnValue().Set(args.This());
}

NAN_METHOD(sdl::WindowWrapper::GetBrightness) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
  // SDL documentation does not say this function can return an erroneous value, so
  // we don't do any error checking.
	info.GetReturnValue().Set(Number::New(SDL_GetWindowBrightness(obj->window_)));
}

NAN_METHOD(sdl::WindowWrapper::GetDisplayIndex) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	int ret = SDL_GetWindowDisplayIndex(obj->window_);
  // SDL documentation says that values less than 0 are returned upon error.
	if(ret < 0) {
		return ThrowSDLException("Window->GetDisplayIndex");
	}

	info.GetReturnValue().Set(Number::New(ret));
}

NAN_METHOD(sdl::WindowWrapper::GetDisplayMode) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_DisplayMode mode;
	int err = SDL_GetWindowDisplayIndex(obj->window_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
	err = SDL_GetCurrentDisplayMode(err, &mode);
  // SDL documentation says that 0 is success, and less than 0 is when an error
  // occurred.
	if(err < 0) {
		return ThrowSDLException("Window->GetDisplayMode");
	}

	info.GetReturnValue().Set(SDLDisplayModeToJavascriptObject(mode));
}

NAN_METHOD(sdl::WindowWrapper::GetFlags) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
  // TODO: Return an array of human-readable strings denoting each flag instead?
  // SDL documentation does not say this function can return an error code.
	info.GetReturnValue().Set(Number::New(SDL_GetWindowFlags(obj->window_)));
}

NAN_METHOD(sdl::WindowWrapper::GetGammaRamp) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	uint16_t redArr[256];
	uint16_t greenArr[256];
	uint16_t blueArr[256];
	int err = SDL_GetWindowGammaRamp(obj->window_, redArr, greenArr, blueArr);
	if(err < 0) {
		return ThrowSDLException("Window->GetGammaRamp");
	}

	Handle<Array> ret = Array::New(3);
	Handle<Array> jsRedArr = Array::New(256);
	Handle<Array> jsGreenArr = Array::New(256);
	Handle<Array> jsBlueArr = Array::New(256);
	for(int i = 0; i < 256; i++) {
		jsRedArr->Set(i, Number::New(redArr[i]));
		jsGreenArr->Set(i, Number::New(greenArr[i]));
		jsBlueArr->Set(i, Number::New(blueArr[i]));
	}

	ret->Set(0, jsRedArr);
	ret->Set(1, jsGreenArr);
	ret->Set(2, jsBlueArr);
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::WindowWrapper::GetGrab) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	info.GetReturnValue().Set(Boolean::New(SDL_GetWindowGrab(obj->window_)));
}

NAN_METHOD(sdl::WindowWrapper::GetWindowID) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	info.GetReturnValue().Set(Number::New(SDL_GetWindowID(obj->window_)));
}

NAN_METHOD(sdl::WindowWrapper::GetMaximumSize) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	int w, h;
	SDL_GetWindowMaximumSize(obj->window_, &w, &h);
	Handle<Array> ret = Array::New(2);
	ret->Set(0, Number::New(w));
	ret->Set(1, Number::New(h));
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::WindowWrapper::GetMinimumSize) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	int w, h;
	SDL_GetWindowMinimumSize(obj->window_, &w, &h);
	Handle<Array> ret = Array::New(2);
	ret->Set(0, Number::New(w));
	ret->Set(1, Number::New(h));
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::WindowWrapper::GetPixelFormat) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	uint32_t ret = SDL_GetWindowPixelFormat(obj->window_);
	if(SDL_PIXELFORMAT_UNKNOWN == ret) {
		return ThrowSDLException("Window->GetPixelFormat");
	}

	info.GetReturnValue().Set(Number::New(ret));
}

NAN_METHOD(sdl::WindowWrapper::GetPosition) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	int x, y;
	SDL_GetWindowPosition(obj->window_, &x, &y);

	Handle<Array> ret = Array::New(2);
	ret->Set(1, Number::New(x));
	ret->Set(2, Number::New(y));
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::WindowWrapper::GetSize) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	int w, h;
	SDL_GetWindowSize(obj->window_, &w, &h);

	Handle<Array> ret = Array::New(2);
	ret->Set(1, Number::New(w));
	ret->Set(2, Number::New(h));
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::WindowWrapper::GetSurface) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_Surface* surf = SDL_GetWindowSurface(obj->window_);
	if(NULL == surf) {
		return ThrowSDLException("Window->GetSurface");
	}

	Handle<Object> ret = Object::New();
	SurfaceWrapper* wrap = new SurfaceWrapper(ret);
	wrap->surface_ = surf;
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::WindowWrapper::GetTitle) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	info.GetReturnValue().Set(String::New(SDL_GetWindowTitle(obj->window_)));
}

NAN_METHOD(sdl::WindowWrapper::Hide) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_HideWindow(obj->window_);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::Show) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_ShowWindow(obj->window_);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::Maximize) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_MaximizeWindow(obj->window_);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::Minimize) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_MinimizeWindow(obj->window_);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::Raise) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_RaiseWindow(obj->window_);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::Restore) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_RestoreWindow(obj->window_);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetBordered) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	bool bordered = args[0]->IsUndefined() ? true : args[0]->BooleanValue();
	SDL_SetWindowBordered(obj->window_, bordered ? SDL_TRUE : SDL_FALSE);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetBrightness) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	double brightness = args[0]->IsUndefined() ? 1.0 : args[0]->NumberValue();
	if(brightness > 1.0) {
		brightness = 1.0;
	}
	else if(brightness < 0.0) {
		brightness = 0.0;
	}

	SDL_SetWindowBrightness(obj->window_, static_cast<float>(brightness));
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetDisplayMode) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args[0]->IsUndefined()) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetDisplayMode(DisplayMode)")));
	}
	SDL_DisplayMode* mode = UnwrapDisplayMode(args[0]);
	int err = SDL_SetWindowDisplayMode(obj->window_, mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetFullscreen) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args[0]->IsUndefined()) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetFullscreen(Number)")));
	}
	int fullscreen = args[0]->Int32Value();
	int err = SDL_SetWindowFullscreen(obj->window_, fullscreen);
	if(err < 0) {
		return ThrowSDLException("Window->SetFullscreen");
	}
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetGammaRamp) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 3 ) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetGammaRamp(Array, Array, Array)")));
	}
	if(!args[0]->IsArray() || !args[1]->IsArray() || !args[2]->IsArray()) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetGammaRamp(Array, Array, Array)")));
	}

	Handle<Array> red = Handle<Array>::Cast(args[0]);
	Handle<Array> green = Handle<Array>::Cast(args[1]);
	Handle<Array> blue = Handle<Array>::Cast(args[2]);
	uint16_t redArr[256];
	uint16_t greenArr[256];
	uint16_t blueArr[256];
	for(int i = 0; i < 256; i++) {
		redArr[i] = red->CloneElementAt(i)->Int32Value();
		greenArr[i] = green->CloneElementAt(i)->Int32Value();
		blueArr[i] = blue->CloneElementAt(i)->Int32Value();
	}
	int err = SDL_SetWindowGammaRamp(obj->window_, redArr, greenArr, blueArr);
	if(err < 0) {
		return ThrowSDLException("Window->SetGammaRamp");
	}

	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetGrab) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetGrab(Boolean)")));
	}
	bool grab = args[0]->ToBoolean()->BooleanValue();
	SDL_SetWindowGrab(obj->window_, grab ? SDL_TRUE : SDL_FALSE);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetIcon) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetIcon(Surface)")));
	}
	SurfaceWrapper* wrap = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	SDL_SetWindowIcon(obj->window_, wrap->surface_);

	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetMaximumSize) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetMaximumSize(Number, Number)")));
	}
	int max_w = args[0]->Int32Value();
	int max_h = args[0]->Int32Value();
	SDL_SetWindowMaximumSize(obj->window_, max_w, max_h);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetMinimumSize) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetMinimumSize(Number, Number)")));
	}
	int min_w = args[0]->Int32Value();
	int min_h = args[0]->Int32Value();
	SDL_SetWindowMinimumSize(obj->window_, min_w, min_h);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetPosition) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetPosition(Number, Number)")));
	}
	int x = args[0]->Int32Value();
	int y = args[0]->Int32Value();
	SDL_SetWindowPosition(obj->window_, x, y);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetSize) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetSize(Number, Number)")));
	}
	int w = args[0]->Int32Value();
	int h = args[0]->Int32Value();
	SDL_SetWindowSize(obj->window_, w, h);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::SetTitle) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetTitle(String)")));
	}
	String::Utf8Value title(args[0]);
	SDL_SetWindowTitle(obj->window_, *title);
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::UpdateWindowSurface) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	int err = SDL_UpdateWindowSurface(obj->window_);
	if(err < 0) {
		return ThrowSDLException("Window->SetTitle");
	}
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::UpdateWindowSurfaceRects) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected UpdateWindowSurfaceRects(Array)")));
	}

	Handle<Array> arr = Handle<Array>::Cast(args[0]);
	int len = arr->Length();
	SDL_Rect* rects = new SDL_Rect[len];
	for(int i = 0; i < len; i++) {
		RectWrapper* wrap = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(arr->Get(i)));
		rects[i] = *wrap->wrapped;
	}

	int err = SDL_UpdateWindowSurfaceRects(obj->window_, rects, len);
	delete rects;
	if(err < 0) {
		return ThrowSDLException("Window->SetTitle");
	}
	return Undefined();
}

NAN_METHOD(sdl::WindowWrapper::Swap) {


	WindowWrapper* obj = ObjectWrap::Unwrap<WindowWrapper>(args.This());
	SDL_GL_SwapWindow(obj->window_);
	return Undefined();
}
