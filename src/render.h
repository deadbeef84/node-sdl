#ifndef NODESDL_RENDER_H
#define NODESDL_RENDER_H

#include <node.h>
#include <v8.h>

#include "SDL.h"


namespace sdl {
	class RendererWrapper : public node::ObjectWrap {
	public:
		static v8::Persistent<v8::FunctionTemplate> constructor;

		RendererWrapper();
		~RendererWrapper();

		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);
		static NAN_METHOD(NewSoftware);

		static NAN_METHOD(GetDrawBlendMode);
		static NAN_METHOD(GetDrawColor);
		static NAN_METHOD(GetOutputSize);
		static NAN_METHOD(GetTarget);
		static NAN_METHOD(GetInfo);
		static NAN_METHOD(GetClipRect);
		static NAN_METHOD(GetLogicalSize);
		static NAN_METHOD(GetScale);
		static NAN_METHOD(GetViewport);
		static NAN_METHOD(ReadPixels);
		static NAN_METHOD(TargetSupported);

		static NAN_METHOD(SetClipRect);
		static NAN_METHOD(SetLogicalSize);
		static NAN_METHOD(SetScale);
		static NAN_METHOD(SetViewport);
		static NAN_METHOD(SetDrawBlendMode);
		static NAN_METHOD(SetDrawColor);
		static NAN_METHOD(SetTarget);

		static NAN_METHOD(Clear);
		static NAN_METHOD(Present);
		static NAN_METHOD(Copy);
		static NAN_METHOD(DrawLine);
		static NAN_METHOD(DrawLines);
		static NAN_METHOD(DrawPoint);
		static NAN_METHOD(DrawPoints);
		static NAN_METHOD(DrawRect);
		static NAN_METHOD(DrawRects);
		static NAN_METHOD(FillRect);
		static NAN_METHOD(FillRects);

		SDL_Renderer* renderer_;
	};
}

#endif
