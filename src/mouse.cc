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

	Handle<Object> SYSTEM_CURSOR = Nan::New<Object>();
	exports->Set(STRING_NEW("SYSTEM_CURSOR"), SYSTEM_CURSOR);
	SYSTEM_CURSOR->Set(STRING_NEW("ARROW"), Nan::New<Number>(SDL_SYSTEM_CURSOR_ARROW));
	SYSTEM_CURSOR->Set(STRING_NEW("IBEAM"), Nan::New<Number>(SDL_SYSTEM_CURSOR_IBEAM));
	SYSTEM_CURSOR->Set(STRING_NEW("WAIT"), Nan::New<Number>(SDL_SYSTEM_CURSOR_WAIT));
	SYSTEM_CURSOR->Set(STRING_NEW("CROSSHAIR"), Nan::New<Number>(SDL_SYSTEM_CURSOR_CROSSHAIR));
	SYSTEM_CURSOR->Set(STRING_NEW("WAITARROW"), Nan::New<Number>(SDL_SYSTEM_CURSOR_WAITARROW));
	SYSTEM_CURSOR->Set(STRING_NEW("SIZENWSE"), Nan::New<Number>(SDL_SYSTEM_CURSOR_SIZENWSE));
	SYSTEM_CURSOR->Set(STRING_NEW("SIZENESW"), Nan::New<Number>(SDL_SYSTEM_CURSOR_SIZENESW));
	SYSTEM_CURSOR->Set(STRING_NEW("SIZEWE"), Nan::New<Number>(SDL_SYSTEM_CURSOR_SIZEWE));
	SYSTEM_CURSOR->Set(STRING_NEW("SIZENS"), Nan::New<Number>(SDL_SYSTEM_CURSOR_SIZENS));
	SYSTEM_CURSOR->Set(STRING_NEW("SIZEALL"), Nan::New<Number>(SDL_SYSTEM_CURSOR_SIZEALL));
	SYSTEM_CURSOR->Set(STRING_NEW("NO"), Nan::New<Number>(SDL_SYSTEM_CURSOR_NO));
	SYSTEM_CURSOR->Set(STRING_NEW("HAND"), Nan::New<Number>(SDL_SYSTEM_CURSOR_HAND));

	Handle<Object> BUTTON = Nan::New<Object>();
	exports->Set(STRING_NEW("BUTTON"), BUTTON);
	BUTTON->Set(STRING_NEW("LEFT"), Nan::New<Number>(SDL_BUTTON_LEFT));
	BUTTON->Set(STRING_NEW("MIDDLE"), Nan::New<Number>(SDL_BUTTON_MIDDLE));
	BUTTON->Set(STRING_NEW("RIGHT"), Nan::New<Number>(SDL_BUTTON_RIGHT));
	BUTTON->Set(STRING_NEW("X1"), Nan::New<Number>(SDL_BUTTON_X1));
	BUTTON->Set(STRING_NEW("X2"), Nan::New<Number>(SDL_BUTTON_X2));
	BUTTON->Set(STRING_NEW("LMASK"), Nan::New<Number>(SDL_BUTTON_LMASK));
	BUTTON->Set(STRING_NEW("MMASK"), Nan::New<Number>(SDL_BUTTON_MMASK));
	BUTTON->Set(STRING_NEW("RMASK"), Nan::New<Number>(SDL_BUTTON_RMASK));
	BUTTON->Set(STRING_NEW("X1MASK"), Nan::New<Number>(SDL_BUTTON_X1MASK));
	BUTTON->Set(STRING_NEW("X2MASK"), Nan::New<Number>(SDL_BUTTON_X2MASK));
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
	tpl->SetClassName(STRING_NEW("CursorWrapper"));

	Nan::SetPrototypeMethod(tpl, "free", FreeCursor);
	Nan::SetPrototypeMethod(tpl, "set", SetCursor);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(STRING_NEW("Cursor"), constructor);
}

NAN_METHOD(sdl::CursorWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("A new Cursor must be created with the new operator.").ToLocalChecked());
		return;
	}

	if(info.Length() < 3) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected CreateColorCursor(Surface, Number, Number)"));
		return;
	}

	SurfaceWrapper* surface = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[0]));
	int x = info[1]->Int32Value();
	int y = info[2]->Int32Value();
	SDL_Cursor* cursor = SDL_CreateColorCursor(surface->surface_, x, y);
	if(NULL == cursor) {
		return ThrowSDLException(__func__);
	}

	CursorWrapper* wrap = new CursorWrapper();
	wrap->cursor_ = cursor;
	wrap->Wrap(info.This());

	return info.This();
}
NAN_METHOD(sdl::CursorWrapper::NewSystem) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("A new Cursor must be created with the new operator.").ToLocalChecked());
		return;
	}

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected CreateColorCursor(Number)"));
		return;
	}

	SDL_SystemCursor id = static_cast<SDL_SystemCursor>(info[0]->Int32Value());
	SDL_Cursor* cursor = SDL_CreateSystemCursor(id);
	if(NULL == cursor) {
		return ThrowSDLException(__func__);
	}

	CursorWrapper* wrap = new CursorWrapper();
	wrap->cursor_ = cursor;
	wrap->Wrap(info.This());

	return info.This();
}

// TODO: Implement this function. See:
//       http://wiki.libsdl.org/SDL_CreateCursor?highlight=%28\bCategoryMouse\b%29|%28CategoryEnum%29|%28CategoryStruct%29
// NAN_METHOD(sdl::CreateCursor) {
//

// 	return Undefined();
// }
NAN_METHOD(sdl::CursorWrapper::FreeCursor) {
	CursorWrapper* wrap = ObjectWrap::Unwrap<CursorWrapper>(info.This());
	SDL_FreeCursor(wrap->cursor_);
	wrap->cursor_ = NULL;
}

NAN_METHOD(sdl::CursorWrapper::SetCursor) {
	CursorWrapper* wrap = ObjectWrap::Unwrap<CursorWrapper>(info.This());
	SDL_SetCursor(wrap->cursor_);
}

NAN_METHOD(sdl::ShowCursor) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected Cursor.show(Number)"));
		return;
	}

	int toggle = info[0]->Int32Value();
	int err = SDL_ShowCursor(toggle);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(err));
}

NAN_METHOD(sdl::GetCursor) {
	SDL_Cursor* cursor = SDL_GetCursor();
	if(NULL == cursor) {
		return Null();
	}

	Handle<Object> toWrap = Nan::New<Object>();
	CursorWrapper* wrap = new CursorWrapper(toWrap);
	wrap->cursor_ = cursor;

	info.GetReturnValue().Set(toWrap);
}

NAN_METHOD(sdl::GetDefaultCursor) {
	SDL_Cursor* cursor = SDL_GetDefaultCursor();
	if(NULL == cursor) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> toWrap = Nan::New<Object>();
	CursorWrapper* wrap = new CursorWrapper(toWrap);
	wrap->cursor_ = cursor;

	info.GetReturnValue().Set(toWrap);
}

NAN_METHOD(sdl::GetMouseFocus) {
	SDL_Window* window = SDL_GetMouseFocus();
	if(NULL == window) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> toWrap = Nan::New<Object>();
	WindowWrapper* wrap = new WindowWrapper(toWrap);
	wrap->window_ = window;

	info.GetReturnValue().Set(toWrap);
}

NAN_METHOD(sdl::GetMouseState) {
	int x, y;
	uint32_t mask = SDL_GetMouseState(&x, &y);

	Handle<Array> ret = Array::New(3);
	ret->Set(0, Nan::New<Number>(x));
	ret->Set(1, Nan::New<Number>(y));
	ret->Set(2, Nan::New<Number>(mask));

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::GetRelativeMouseMode) {
	SDL_bool ret = SDL_GetRelativeMouseMode();

	info.GetReturnValue().Set(Nan::New<Boolean>(ret ? true : false));
}

NAN_METHOD(sdl::GetRelativeMouseState) {
	int x, y;
	uint32_t mask = SDL_GetRelativeMouseState(&x, &y);

	Handle<Array> ret = Array::New(3);
	ret->Set(0, Nan::New<Number>(x));
	ret->Set(1, Nan::New<Number>(y));
	ret->Set(2, Nan::New<Number>(mask));

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::SetRelativeMouseMode) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected SetRelativeMouseMode(Boolean)"));
		return;
	}

	bool enabled = info[0]->BooleanValue();
	int err = SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::WarpMouseInWindow) {
	if(info.Length() < 3) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected WarpMouseInWindow(Window, Number, Number)"));
		return;
	}

	WindowWrapper* window = ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[0]));
	int x = info[1]->Int32Value();
	int y = info[2]->Int32Value();
	SDL_WarpMouseInWindow(window->window_, x, y);
}

NAN_METHOD(sdl::ButtonMacroWrapper) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected button(Number)"));
		return;
	}

	int button = info[0]->Int32Value();
	int ret = SDL_BUTTON(button);

	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
