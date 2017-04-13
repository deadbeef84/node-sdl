#ifndef NODESDL_CONTAINER_H
#define NODESDL_CONTAINER_H

#include <nan.h>
#include <node.h>
#include <v8.h>

#include "SDL.h"
#include "helpers.h"


namespace sdl {
	OPEN_OBJECTWRAP(RectWrapper)
		static GETTER_DEF(GetX);
		static GETTER_DEF(GetY);
		static GETTER_DEF(GetW);
		static GETTER_DEF(GetH);

		static SETTER_DEF(SetX);
		static SETTER_DEF(SetY);
		static SETTER_DEF(SetW);
		static SETTER_DEF(SetH);
	CLOSE_OBJECTWRAP(SDL_Rect)
	// class RectWrapper : public node::ObjectWrap {
	// public:
	// 	static v8::Persistent<v8::FunctionTemplate> constructor;

	// 	RectWrapper();
	// 	RectWrapper(v8::Handle<v8::Object> toWrap);
	// 	~RectWrapper();

	// 	static NAN_MODULE_INIT(Init);
	// 	static NAN_METHOD(New);

	// 	static GETTER_DEF(GetX);
	// 	static GETTER_DEF(GetY);
	// 	static GETTER_DEF(GetW);
	// 	static GETTER_DEF(GetH);

	// 	static void SetX(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
	// 	static void SetY(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
	// 	static void SetW(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
	// 	static void SetH(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

	// 	SDL_Rect* wrapped;
	// };

	class ColorWrapper : public node::ObjectWrap {
	public:
		static v8::Persistent<v8::FunctionTemplate> constructor;

		~ColorWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);

		static v8::Handle<v8::Value> GetRed(v8::Local<v8::String> name, const v8::AccessorInfo& info);
		static v8::Handle<v8::Value> GetGreen(v8::Local<v8::String> name, const v8::AccessorInfo& info);
		static v8::Handle<v8::Value> GetBlue(v8::Local<v8::String> name, const v8::AccessorInfo& info);
		static v8::Handle<v8::Value> GetAlpha(v8::Local<v8::String> name, const v8::AccessorInfo& info);
		static NAN_METHOD(GetColor);

		static void SetRed(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
		static void SetGreen(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
		static void SetBlue(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
		static void SetAlpha(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

		static NAN_METHOD(ToString);

		SDL_Color* color_;
	};

	class FingerWrapper : public node::ObjectWrap {
	public:
		static v8::Persistent<v8::FunctionTemplate> constructor;

		FingerWrapper();
		FingerWrapper(v8::Handle<v8::Object> toWrap);
		~FingerWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);

		static v8::Handle<v8::Value> GetFingerID(v8::Local<v8::String> name, const v8::AccessorInfo& info);
		static v8::Handle<v8::Value> GetX(v8::Local<v8::String> name, const v8::AccessorInfo& info);
		static v8::Handle<v8::Value> GetY(v8::Local<v8::String> name, const v8::AccessorInfo& info);
		static v8::Handle<v8::Value> GetPressure(v8::Local<v8::String> name, const v8::AccessorInfo& info);

		SDL_Finger* finger_;
	};
}

#endif
