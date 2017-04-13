#include "render.h"
#include "SDL.h"
#include "helpers.h"
#include "texture.h"
#include "surface.h"
#include "struct_wrappers.h"
#include "window.h"
#include "container.h"

#include <iostream>

using namespace v8;

////////////////////////////////////////////////////////////////////////////////
// RendererWrapper Class Definition.
Persistent<FunctionTemplate> sdl::RendererWrapper::constructor;

sdl::RendererWrapper::RendererWrapper() {
}

sdl::RendererWrapper::~RendererWrapper() {
	if(NULL != renderer_) {
		SDL_DestroyRenderer(renderer_);
	}
}

NAN_MODULE_INIT(sdl::RendererWrapper::Init) {
  	// Setup hardware renderer construction.
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("RendererWrapper"));

	Nan::SetPrototypeMethod(tpl, "getDrawBlendMode", GetDrawBlendMode);
	Nan::SetPrototypeMethod(tpl, "getDrawColor", GetDrawColor);
	Nan::SetPrototypeMethod(tpl, "getOutputSize", GetOutputSize);
	Nan::SetPrototypeMethod(tpl, "getTarget", GetTarget);
	Nan::SetPrototypeMethod(tpl, "getInfo", GetInfo);
	Nan::SetPrototypeMethod(tpl, "getClipRect", GetClipRect);
	Nan::SetPrototypeMethod(tpl, "getLogicalSize", GetLogicalSize);
	Nan::SetPrototypeMethod(tpl, "getScale", GetScale);
	Nan::SetPrototypeMethod(tpl, "getViewport", GetViewport);
	Nan::SetPrototypeMethod(tpl, "targetSupported", TargetSupported);

	Nan::SetPrototypeMethod(tpl, "setClipRect", SetClipRect);
	Nan::SetPrototypeMethod(tpl, "setLogicalSize", SetLogicalSize);
	Nan::SetPrototypeMethod(tpl, "setScale", SetScale);
	Nan::SetPrototypeMethod(tpl, "setViewport", SetViewport);
	Nan::SetPrototypeMethod(tpl, "setDrawBlendMode", SetDrawBlendMode);
	Nan::SetPrototypeMethod(tpl, "setDrawColor", SetDrawColor);
	Nan::SetPrototypeMethod(tpl, "setTarget", SetTarget);

	Nan::SetPrototypeMethod(tpl, "clear", Clear);
	Nan::SetPrototypeMethod(tpl, "present", Present);
	Nan::SetPrototypeMethod(tpl, "copy", Copy);
	Nan::SetPrototypeMethod(tpl, "drawLine", DrawLine);
	Nan::SetPrototypeMethod(tpl, "drawLines", DrawLine);
	Nan::SetPrototypeMethod(tpl, "drawPoint", DrawPoint);
	Nan::SetPrototypeMethod(tpl, "drawRect", DrawRect);
	Nan::SetPrototypeMethod(tpl, "fillRect", FillRect);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Renderer"), constructor);
}

NAN_METHOD(sdl::RendererWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Use the new operator to create instances of a Renderer.")));
	}



	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid Arguments: Expected at least: new Renderer(sdl.Window)")));
	}
	else if(!args[0]->IsObject()) {
		return ThrowException(Exception::TypeError(String::New("Invalid Arguments: Expected at least: new Renderer(sdl.Window)")));
	}

	WindowWrapper* window = ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(args[0]));
	int index = args[1]->IsUndefined() ? -1 : args[1]->Int32Value();
	int flags = args[2]->IsUndefined() ? SDL_RENDERER_ACCELERATED : args[2]->Int32Value();
	SDL_Renderer* renderer = SDL_CreateRenderer(window->window_, index, flags);
	if(NULL == renderer) {
		return ThrowSDLException(__func__);
	}

	RendererWrapper* obj = new RendererWrapper();
	obj->renderer_ = renderer;
	obj->Wrap(args.This());
	return args.This();
}

NAN_METHOD(sdl::RendererWrapper::NewSoftware) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Use the new operator to create instances of a Renderer.")));
	}



	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid Arguments: Expected: new SoftwareRenderer(sdl.Surface)")));
	}
	else if(!args[0]->IsObject()) {
		return ThrowException(Exception::TypeError(String::New("Invalid Arguments: Expected: new SoftwareRenderer(sdl.Surface)")));
	}

	SurfaceWrapper* wrap = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(wrap->surface_);
	if(NULL == renderer) {
		return ThrowSDLException(__func__);
	}

	RendererWrapper* obj = new RendererWrapper();
	obj->renderer_ = renderer;
	obj->Wrap(args.This());
	return args.This();
}

// NAN_METHOD(sdl::RendererWrapper::CreateTexture) {
//
//   RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

//   return Undefined();
// }
// NAN_METHOD(sdl::RendererWrapper::CreateTextureFromSurface) {
//
//   RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

//   return Undefined();
// }

NAN_METHOD(sdl::RendererWrapper::GetDrawBlendMode) {

	RendererWrapper* obj = ObjectWrap::Unwrap<sdl::RendererWrapper>(args.This());
	SDL_BlendMode mode;
	int err = SDL_GetRenderDrawBlendMode(obj->renderer_, &mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(mode));
}

NAN_METHOD(sdl::RendererWrapper::GetDrawColor) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());
	uint8_t r, g, b, a;
	int err = SDL_GetRenderDrawColor(obj->renderer_, &r, &g, &b, &a);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
	SDL_Color* color = new SDL_Color;
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;

	info.GetReturnValue().Set(WrapColor(color));
}

NAN_METHOD(sdl::RendererWrapper::GetTarget) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	SDL_Texture* texture = SDL_GetRenderTarget(obj->renderer_);
	if(NULL == texture) {
		return Null();
	}

	Handle<Object> toWrap = Object::New();
	TextureWrapper* texWrap = new TextureWrapper(toWrap);
	texWrap->texture_ = texture;
	info.GetReturnValue().Set(toWrap);
}

NAN_METHOD(sdl::RendererWrapper::GetInfo) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	SDL_RendererInfo* info = new SDL_RendererInfo;
	int err = SDL_GetRendererInfo(obj->renderer_, info);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
	info.GetReturnValue().Set(WrapRendererInfo(info));
}

NAN_METHOD(sdl::RendererWrapper::GetOutputSize) {

	RendererWrapper* obj = ObjectWrap::Unwrap<sdl::RendererWrapper>(args.This());

	int w, h;
	int err = SDL_GetRendererOutputSize(obj->renderer_, &w, &h);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
	Local<Array> ret = Array::New(2);
	ret->Set(0, Number::New(w));
	ret->Set(1, Number::New(h));
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::RendererWrapper::GetClipRect) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	SDL_Rect* rect = new SDL_Rect;
	SDL_RenderGetClipRect(obj->renderer_, rect);

  NEW_WRAPPED(rect, RectWrapper, ret)

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::RendererWrapper::GetLogicalSize) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	int w, h;
	SDL_RenderGetLogicalSize(obj->renderer_, &w, &h);
	Handle<Array> ret = Array::New(2);
	ret->Set(0, Number::New(w));
	ret->Set(1, Number::New(h));

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::RendererWrapper::GetScale) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	float scaleX, scaleY;
	SDL_RenderGetScale(obj->renderer_, &scaleX, &scaleY);
	Handle<Array> ret = Array::New(2);
	ret->Set(0, Number::New(scaleX));
	ret->Set(1, Number::New(scaleY));

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::RendererWrapper::GetViewport) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	SDL_Rect* rect = new SDL_Rect;
	SDL_RenderGetViewport(obj->renderer_, rect);

  NEW_WRAPPED(rect, RectWrapper, ret)

	info.GetReturnValue().Set(ret);
}
// TODO: Implement.
NAN_METHOD(sdl::RendererWrapper::ReadPixels) {

	// RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	return ThrowException(Exception::Error(String::New("Not implemented.")));
}
NAN_METHOD(sdl::RendererWrapper::TargetSupported) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	info.GetReturnValue().Set(Boolean::New(SDL_RenderTargetSupported(obj->renderer_)));
}

NAN_METHOD(sdl::RendererWrapper::SetClipRect) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	int err;
	if(args[0]->IsUndefined()) {
		err = SDL_RenderSetClipRect(obj->renderer_, NULL);
	}
	else {
		RectWrapper* clip = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[0]));
		err = SDL_RenderSetClipRect(obj->renderer_, clip->wrapped);
	}
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::SetLogicalSize) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected setLogicalSize(Number, Number)")));
	}
	int w = args[0]->IsUndefined() ? 1 : args[0]->Int32Value();
	int h = args[1]->IsUndefined() ? 1 : args[1]->Int32Value();
	int err = SDL_RenderSetLogicalSize(obj->renderer_, w, h);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::SetScale) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected setLogicalSize(Number, Number)")));
	}
	double scaleX = args[0]->IsUndefined() ? 1 : args[0]->NumberValue();
	double scaleY = args[1]->IsUndefined() ? 1 : args[1]->NumberValue();
	int err = SDL_RenderSetLogicalSize(obj->renderer_, scaleX, scaleY);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::SetViewport) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	int err;
	if(args[0]->IsUndefined()) {
		err = SDL_RenderSetViewport(obj->renderer_, NULL);
	}
	else {
		RectWrapper* wrap = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[0]));
		err = SDL_RenderSetViewport(obj->renderer_, wrap->wrapped);
	}
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::SetDrawBlendMode) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	SDL_BlendMode mode = args[0]->IsUndefined() ? SDL_BLENDMODE_NONE : static_cast<SDL_BlendMode>(args[0]->Int32Value());
	int err = SDL_SetRenderDrawBlendMode(obj->renderer_, mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::SetDrawColor) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 4) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected setDrawColor(Number, Number, Number, Number)")));
	}
	int r = args[0]->IsUndefined() ? 0 : args[0]->Int32Value();
	int g = args[1]->IsUndefined() ? 0 : args[1]->Int32Value();
	int b = args[2]->IsUndefined() ? 0 : args[2]->Int32Value();
	int a = args[3]->IsUndefined() ? 0 : args[4]->Int32Value();
	int err = SDL_SetRenderDrawColor(obj->renderer_, r, g, b, a);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::SetTarget) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected setTarget(Texture)")));
	}
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(args[0]));
	int err = SDL_SetRenderTarget(obj->renderer_, tex->texture_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}

NAN_METHOD(sdl::RendererWrapper::Clear) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	int err = SDL_RenderClear(obj->renderer_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::Present) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());
	SDL_RenderPresent(obj->renderer_);

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::Copy) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() > 3) {
		TextureWrapper* texture = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(args[0]));
		RectWrapper* src = args[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[1]));
		RectWrapper* dst = args[2]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[2]));
		double angle = args[3]->IsUndefined() ? 0 : args[3]->NumberValue();
		PointWrapper* point = args[4]->IsUndefined() ? NULL : ObjectWrap::Unwrap<PointWrapper>(Handle<Object>::Cast(args[4]));
		SDL_RendererFlip flip = args[5]->IsUndefined() ? SDL_FLIP_NONE : static_cast<SDL_RendererFlip>(args[5]->Int32Value());
		int err = SDL_RenderCopyEx(obj->renderer_, texture->texture_,
			src == NULL ? NULL : src->wrapped,
			dst == NULL ? NULL : dst->wrapped,
			angle,
			point == NULL ? NULL : point->point_,
			flip);
		if(err < 0) {
			return ThrowSDLException(__func__);
		}
	}
	else {
		TextureWrapper* texture = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(args[0]));
		RectWrapper* src = args[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[1]));
		RectWrapper* dst = args[2]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[2]));
		int err = SDL_RenderCopy(obj->renderer_, texture->texture_,
			src == NULL ? NULL : src->wrapped,
			dst == NULL ? NULL : dst->wrapped);
		if(err < 0) {
			return ThrowSDLException(__func__);
		}
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::DrawLine) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 4) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected drawLine(Number, Number, Number, Number)")));
	}

	int x1 = args[0]->Int32Value();
	int y1 = args[1]->Int32Value();
	int x2 = args[2]->Int32Value();
	int y2 = args[3]->Int32Value();
	int err = SDL_RenderDrawLine(obj->renderer_, x1, y1, x2, y2);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::DrawLines) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected drawLines(Array)")));
	}

	Handle<Array> arr = Handle<Array>::Cast(args[0]);
	const int numPoints = arr->Length();
	SDL_Point* points = new SDL_Point[numPoints];
	for(int i = 0; i < numPoints; i++) {
		PointWrapper* wrap = ObjectWrap::Unwrap<PointWrapper>(Handle<Object>::Cast(arr->Get(0)));
		points[i] = *wrap->point_;
	}
	int err = SDL_RenderDrawLines(obj->renderer_, points, numPoints);
	delete points;
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::DrawPoint) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected drawPoint(Point)")));
	}

	int x = args[0]->Int32Value();
	int y = args[1]->Int32Value();
	int err = SDL_RenderDrawPoint(obj->renderer_, x, y);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::DrawPoints) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected drawPoints(Array)")));
	}

	Handle<Array> arr = Handle<Array>::Cast(args[0]);
	int numPoints = arr->Length();
	SDL_Point* points = new SDL_Point[numPoints];
	for(int i = 0; i < numPoints; i++) {
		PointWrapper* point = ObjectWrap::Unwrap<PointWrapper>(Handle<Object>::Cast(arr->Get(i)));
		points[i] = *point->point_;
	}
	int err = SDL_RenderDrawPoints(obj->renderer_, points, numPoints);
	delete points;
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::DrawRect) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected drawRect(Rect)")));
	}

	RectWrapper* rect = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[0]));
	int err = SDL_RenderDrawRect(obj->renderer_, rect->wrapped);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::DrawRects) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected drawRects(Array)")));
	}

	Handle<Array> arr = Handle<Array>::Cast(args[0]);
	int numRects = arr->Length();
	SDL_Rect* rects = new SDL_Rect[numRects];
	for(int i = 0; i < numRects; i++) {
		RectWrapper* rect = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(arr->Get(i)));
		rects[i] = *rect->wrapped;
	}
	int err = SDL_RenderDrawRects(obj->renderer_, rects, numRects);
	delete rects;
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::FillRect) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected drawRect(Rect)")));
	}

	RectWrapper* rect = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[0]));
	int err = SDL_RenderFillRect(obj->renderer_, rect->wrapped);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::RendererWrapper::FillRects) {

	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(args.This());

	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected drawRects(Array)")));
	}

	Handle<Array> arr = Handle<Array>::Cast(args[0]);
	int numRects = arr->Length();
	SDL_Rect* rects = new SDL_Rect[numRects];
	for(int i = 0; i < numRects; i++) {
		RectWrapper* rect = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(arr->Get(i)));
		rects[i] = *rect->wrapped;
	}
	int err = SDL_RenderFillRects(obj->renderer_, rects, numRects);
	delete rects;
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
