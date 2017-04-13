#include "mouse.h"
#include "surface.h"
#include "helpers.h"
#include "window.h"

using namespace v8;
using namespace node;


NAN_MODULE_INIT(sdl::mouse::Init) {
	CursorWrapper::Init(exports);

	Nan::SetPrototypeMethod(exports, "showCursor", ShowCursor);
	Nan::SetPrototypeMethod(exports, "getCursor", GetCursor);
	Nan::SetPrototypeMethod(exports, "getDefaultCursor", GetDefaultCursor);
	Nan::SetPrototypeMethod(exports, "getMouseFocus", GetMouseFocus);
	Nan::SetPrototypeMethod(exports, "getMouseState", GetMouseState);
	Nan::SetPrototypeMethod(exports, "getRelativeMouseMode", GetRelativeMouseMode);
	Nan::SetPrototypeMethod(exports, "getRelativeMouseState", GetRelativeMouseState);

	Nan::SetPrototypeMethod(exports, "setRelativeMouseMode", SetRelativeMouseMode);

	Nan::SetPrototypeMethod(exports, "warpMouseInWindow", WarpMouseInWindow);

	Nan::SetPrototypeMethod(exports, "button", ButtonMacroWrapper);

	Handle<Object> SYSTEM_CURSOR = Object::New();
	exports->Set(String::NewSymbol("SYSTEM_CURSOR"), SYSTEM_CURSOR);
	SYSTEM_CURSOR->Set(String::NewSymbol("ARROW"), Number::New(SDL_SYSTEM_CURSOR_ARROW));
	SYSTEM_CURSOR->Set(String::NewSymbol("IBEAM"), Number::New(SDL_SYSTEM_CURSOR_IBEAM));
	SYSTEM_CURSOR->Set(String::NewSymbol("WAIT"), Number::New(SDL_SYSTEM_CURSOR_WAIT));
	SYSTEM_CURSOR->Set(String::NewSymbol("CROSSHAIR"), Number::New(SDL_SYSTEM_CURSOR_CROSSHAIR));
	SYSTEM_CURSOR->Set(String::NewSymbol("WAITARROW"), Number::New(SDL_SYSTEM_CURSOR_WAITARROW));
	SYSTEM_CURSOR->Set(String::NewSymbol("SIZENWSE"), Number::New(SDL_SYSTEM_CURSOR_SIZENWSE));
	SYSTEM_CURSOR->Set(String::NewSymbol("SIZENESW"), Number::New(SDL_SYSTEM_CURSOR_SIZENESW));
	SYSTEM_CURSOR->Set(String::NewSymbol("SIZEWE"), Number::New(SDL_SYSTEM_CURSOR_SIZEWE));
	SYSTEM_CURSOR->Set(String::NewSymbol("SIZENS"), Number::New(SDL_SYSTEM_CURSOR_SIZENS));
	SYSTEM_CURSOR->Set(String::NewSymbol("SIZEALL"), Number::New(SDL_SYSTEM_CURSOR_SIZEALL));
	SYSTEM_CURSOR->Set(String::NewSymbol("NO"), Number::New(SDL_SYSTEM_CURSOR_NO));
	SYSTEM_CURSOR->Set(String::NewSymbol("HAND"), Number::New(SDL_SYSTEM_CURSOR_HAND));

	Handle<Object> BUTTON = Object::New();
	exports->Set(String::NewSymbol("BUTTON"), BUTTON);
	BUTTON->Set(String::NewSymbol("LEFT"), Number::New(SDL_BUTTON_LEFT));
	BUTTON->Set(String::NewSymbol("MIDDLE"), Number::New(SDL_BUTTON_MIDDLE));
	BUTTON->Set(String::NewSymbol("RIGHT"), Number::New(SDL_BUTTON_RIGHT));
	BUTTON->Set(String::NewSymbol("X1"), Number::New(SDL_BUTTON_X1));
	BUTTON->Set(String::NewSymbol("X2"), Number::New(SDL_BUTTON_X2));
	BUTTON->Set(String::NewSymbol("LMASK"), Number::New(SDL_BUTTON_LMASK));
	BUTTON->Set(String::NewSymbol("MMASK"), Number::New(SDL_BUTTON_MMASK));
	BUTTON->Set(String::NewSymbol("RMASK"), Number::New(SDL_BUTTON_RMASK));
	BUTTON->Set(String::NewSymbol("X1MASK"), Number::New(SDL_BUTTON_X1MASK));
	BUTTON->Set(String::NewSymbol("X2MASK"), Number::New(SDL_BUTTON_X2MASK));
}

Persistent<FunctionTemplate> sdl::CursorWrapper::constructor;

sdl::CursorWrapper::CursorWrapper() {
}
sdl::CursorWrapper::CursorWrapper(Handle<Object> toWrap) {
	Wrap(toWrap);
}
sdl::CursorWrapper::~CursorWrapper() {
	if(NULL != cursor_) {
		SDL_FreeCursor(cursor_);
	}
}

NAN_MODULE_INIT(sdl::CursorWrapper::Init) {
	Handle<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("CursorWrapper"));

	Nan::SetPrototypeMethod(tpl, "free", FreeCursor);
	Nan::SetPrototypeMethod(tpl, "set", SetCursor);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Cursor"), constructor);
}

NAN_METHOD(sdl::CursorWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("A new Cursor must be created with the new operator.")));
	}



	if(args.Length() < 3) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected CreateColorCursor(Surface, Number, Number)")));
	}

	SurfaceWrapper* surface = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	int x = args[1]->Int32Value();
	int y = args[2]->Int32Value();
	SDL_Cursor* cursor = SDL_CreateColorCursor(surface->surface_, x, y);
	if(NULL == cursor) {
		return ThrowSDLException(__func__);
	}

	CursorWrapper* wrap = new CursorWrapper();
	wrap->cursor_ = cursor;
	wrap->Wrap(args.This());

	return args.This();
}
NAN_METHOD(sdl::CursorWrapper::NewSystem) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("A new Cursor must be created with the new operator.")));
	}



	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected CreateColorCursor(Number)")));
	}

	SDL_SystemCursor id = static_cast<SDL_SystemCursor>(args[0]->Int32Value());
	SDL_Cursor* cursor = SDL_CreateSystemCursor(id);
	if(NULL == cursor) {
		return ThrowSDLException(__func__);
	}

	CursorWrapper* wrap = new CursorWrapper();
	wrap->cursor_ = cursor;
	wrap->Wrap(args.This());

	return args.This();
}

// TODO: Implement this function. See:
//       http://wiki.libsdl.org/SDL_CreateCursor?highlight=%28\bCategoryMouse\b%29|%28CategoryEnum%29|%28CategoryStruct%29
// NAN_METHOD(sdl::CreateCursor) {
//

// 	return Undefined();
// }
NAN_METHOD(sdl::CursorWrapper::FreeCursor) {


	CursorWrapper* wrap = ObjectWrap::Unwrap<CursorWrapper>(args.This());
	SDL_FreeCursor(wrap->cursor_);
	wrap->cursor_ = NULL;

	return Undefined();
}
NAN_METHOD(sdl::CursorWrapper::SetCursor) {


	CursorWrapper* wrap = ObjectWrap::Unwrap<CursorWrapper>(args.This());
	SDL_SetCursor(wrap->cursor_);

	return Undefined();
}

NAN_METHOD(sdl::ShowCursor) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected Cursor.show(Number)")));
	}

	int toggle = args[0]->Int32Value();
	int err = SDL_ShowCursor(toggle);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(err));
}
NAN_METHOD(sdl::GetCursor) {


	SDL_Cursor* cursor = SDL_GetCursor();
	if(NULL == cursor) {
		return Null();
	}

	Handle<Object> toWrap = Object::New();
	CursorWrapper* wrap = new CursorWrapper(toWrap);
	wrap->cursor_ = cursor;

	info.GetReturnValue().Set(toWrap);
}
NAN_METHOD(sdl::GetDefaultCursor) {


	SDL_Cursor* cursor = SDL_GetDefaultCursor();
	if(NULL == cursor) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> toWrap = Object::New();
	CursorWrapper* wrap = new CursorWrapper(toWrap);
	wrap->cursor_ = cursor;

	info.GetReturnValue().Set(toWrap);

	return Undefined();
}
NAN_METHOD(sdl::GetMouseFocus) {


	SDL_Window* window = SDL_GetMouseFocus();
	if(NULL == window) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> toWrap = Object::New();
	WindowWrapper* wrap = new WindowWrapper(toWrap);
	wrap->window_ = window;

	info.GetReturnValue().Set(toWrap);
}
NAN_METHOD(sdl::GetMouseState) {


	int x, y;
	uint32_t mask = SDL_GetMouseState(&x, &y);

	Handle<Array> ret = Array::New(3);
	ret->Set(0, Number::New(x));
	ret->Set(1, Number::New(y));
	ret->Set(2, Number::New(mask));

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::GetRelativeMouseMode) {


	SDL_bool ret = SDL_GetRelativeMouseMode();

	info.GetReturnValue().Set(Boolean::New(ret ? true : false));
}
NAN_METHOD(sdl::GetRelativeMouseState) {


	int x, y;
	uint32_t mask = SDL_GetRelativeMouseState(&x, &y);

	Handle<Array> ret = Array::New(3);
	ret->Set(0, Number::New(x));
	ret->Set(1, Number::New(y));
	ret->Set(2, Number::New(mask));

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::SetRelativeMouseMode) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected SetRelativeMouseMode(Boolean)")));
	}

	bool enabled = args[0]->BooleanValue();
	int err = SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}

NAN_METHOD(sdl::WarpMouseInWindow) {


	if(args.Length() < 3) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected WarpMouseInWindow(Window, Number, Number)")));
	}

	WindowWrapper* window = ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(args[0]));
	int x = args[1]->Int32Value();
	int y = args[2]->Int32Value();
	SDL_WarpMouseInWindow(window->window_, x, y);

	return Undefined();
}

NAN_METHOD(sdl::ButtonMacroWrapper) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected button(Number)")));
	}

	int button = args[0]->Int32Value();
	int ret = SDL_BUTTON(button);

	info.GetReturnValue().Set(Number::New(ret));
}
