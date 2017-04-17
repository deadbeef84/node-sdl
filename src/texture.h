#ifndef NODESDL_TEXTURE_H
#define NODESDL_TEXTURE_H

#include <nan.h>
#include <node.h>
#include <v8.h>

#include "SDL.h"


namespace sdl {
	class TextureWrapper : public Nan::ObjectWrap {
	public:
		static Nan::Persistent<v8::FunctionTemplate> constructor;

		TextureWrapper();
		TextureWrapper(v8::Handle<v8::Object> toWrap);
		~TextureWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);
		static NAN_METHOD(NewFromSurface);

		static NAN_METHOD(GetAlphaMod);
		static NAN_METHOD(GetBlendMode);
		static NAN_METHOD(GetColorMod);
		static NAN_METHOD(GetFormat);
		static NAN_METHOD(GetSize);
		static NAN_METHOD(GetWidth);
		static NAN_METHOD(GetHeight);

		static NAN_METHOD(SetAlphaMod);
		static NAN_METHOD(SetBlendMode);
		static NAN_METHOD(SetColorMod);

		// TODO: Implement for streaming to a texture.
		// static NAN_METHOD(Lock);
		// static NAN_METHOD(Unlock);

		static NAN_METHOD(Update);

		SDL_Texture* texture_;
	};
}

#endif