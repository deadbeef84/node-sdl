#ifndef NODESDL_CONTAINER_H
#define NODESDL_CONTAINER_H

#include <nan.h>
#include <node.h>
#include <v8.h>

#include "SDL.h"
#include "helpers.h"


namespace sdl {


	class RectWrapper : public Nan::ObjectWrap {
	public:
		static Nan::Persistent<v8::FunctionTemplate> constructor;

		~RectWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);

		static NAN_GETTER(GetX);
		static NAN_GETTER(GetY);
		static NAN_GETTER(GetW);
		static NAN_GETTER(GetH);

		static NAN_SETTER(SetX);
		static NAN_SETTER(SetY);
		static NAN_SETTER(SetW);
		static NAN_SETTER(SetH);

		SDL_Rect* rect_;
	};

	class ColorWrapper : public Nan::ObjectWrap {
	public:
		static Nan::Persistent<v8::FunctionTemplate> constructor;

		~ColorWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);

		static NAN_GETTER(GetRed);
		static NAN_GETTER(GetGreen);
		static NAN_GETTER(GetBlue);
		static NAN_GETTER(GetAlpha);

		static NAN_METHOD(GetColor);

		static NAN_SETTER(SetRed);
		static NAN_SETTER(SetGreen);
		static NAN_SETTER(SetBlue);
		static NAN_SETTER(SetAlpha);

		static NAN_METHOD(ToString);

		SDL_Color* color_;
	};

	class FingerWrapper : public Nan::ObjectWrap {
	public:
		static Nan::Persistent<v8::FunctionTemplate> constructor;

		FingerWrapper();
		FingerWrapper(v8::Handle<v8::Object> toWrap);
		~FingerWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);

		static NAN_GETTER(GetFingerID);
		static NAN_GETTER(GetX);
		static NAN_GETTER(GetY);
		static NAN_GETTER(GetPressure);

		SDL_Finger* finger_;
	};

	class PointWrapper : public Nan::ObjectWrap {
	public:
		static Nan::Persistent<v8::FunctionTemplate> constructor;

		~PointWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);

		static NAN_GETTER(GetX);
		static NAN_GETTER(GetY);

		static NAN_SETTER(SetX);
		static NAN_SETTER(SetY);

		SDL_Point* point_;
	};
}

#endif
