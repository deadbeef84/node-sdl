#ifndef NODEJS_MOUSE_H
#define NODEJS_MOUSE_H

#include <nan.h>
#include <v8.h>
#include <node.h>

#include "SDL.h"


namespace sdl {
	namespace mouse {
		NAN_MODULE_INIT(Init);
	}

	class CursorWrapper : public Nan::ObjectWrap {
	public:
		static Nan::Persistent<v8::FunctionTemplate> constructor;

		CursorWrapper();
		CursorWrapper(v8::Handle<v8::Object> toWrap);
		~CursorWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);
		static NAN_METHOD(NewSystem);

		static NAN_METHOD(FreeCursor);
		static NAN_METHOD(SetCursor);

		SDL_Cursor* cursor_;
	};

	// NAN_METHOD(CreateCursor);
	// NAN_METHOD(CreateSystemCursor);

	NAN_METHOD(ShowCursor);
	NAN_METHOD(GetCursor);
	NAN_METHOD(GetDefaultCursor);
	NAN_METHOD(GetMouseFocus);
	NAN_METHOD(GetMouseState);
	NAN_METHOD(GetRelativeMouseMode);
	NAN_METHOD(GetRelativeMouseState);

	NAN_METHOD(SetRelativeMouseMode);

	NAN_METHOD(WarpMouseInWindow);

	NAN_METHOD(ButtonMacroWrapper);
}

#endif