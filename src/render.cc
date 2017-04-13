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
	tpl->SetClassName(STRING_NEW("RendererWrapper"));

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
	exports->Set(STRING_NEW("Renderer"), constructor);
}

NAN_METHOD(sdl::RendererWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("Use the new operator to create instances of a Renderer.").ToLocalChecked());
		return;
	}

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid Arguments: Expected at least: new Renderer(sdl.Window)"));
		return;
	}
	else if(!info[0]->IsObject()) {
		Nan::ThrowTypeError(STRING_NEW("Invalid Arguments: Expected at least: new Renderer(sdl.Window)"));
		return;
	}

	WindowWrapper* window = ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[0]));
	int index = info[1]->IsUndefined() ? -1 : info[1]->Int32Value();
	int flags = info[2]->IsUndefined() ? SDL_RENDERER_ACCELERATED : info[2]->Int32Value();
	SDL_Renderer* renderer = SDL_CreateRenderer(window->window_, index, flags);
	if(NULL == renderer) {
		return ThrowSDLException(__func__);
	}

	RendererWrapper* obj = new RendererWrapper();
	obj->renderer_ = renderer;
	obj->Wrap(info.This());
	return info.This();
}

NAN_METHOD(sdl::RendererWrapper::NewSoftware) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("Use the new operator to create instances of a Renderer.").ToLocalChecked());
		return;
	}

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid Arguments: Expected: new SoftwareRenderer(sdl.Surface)"));
		return;
	}
	else if(!info[0]->IsObject()) {
		Nan::ThrowTypeError(STRING_NEW("Invalid Arguments: Expected: new SoftwareRenderer(sdl.Surface)"));
		return;
	}

	SurfaceWrapper* wrap = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[0]));
	SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(wrap->surface_);
	if(NULL == renderer) {
		return ThrowSDLException(__func__);
	}

	RendererWrapper* obj = new RendererWrapper();
	obj->renderer_ = renderer;
	obj->Wrap(info.This());
	return info.This();
}

// NAN_METHOD(sdl::RendererWrapper::CreateTexture) {
//   RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());
// }

// NAN_METHOD(sdl::RendererWrapper::CreateTextureFromSurface) {
//   RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());
// }

NAN_METHOD(sdl::RendererWrapper::GetDrawBlendMode) {

	RendererWrapper* obj = ObjectWrap::Unwrap<sdl::RendererWrapper>(info.This());
	SDL_BlendMode mode;
	int err = SDL_GetRenderDrawBlendMode(obj->renderer_, &mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(mode));
}

NAN_METHOD(sdl::RendererWrapper::GetDrawColor) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

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
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	SDL_Texture* texture = SDL_GetRenderTarget(obj->renderer_);
	if(NULL == texture) {
		return Null();
	}

	Handle<Object> toWrap = Nan::New<Object>();
	TextureWrapper* texWrap = new TextureWrapper(toWrap);
	texWrap->texture_ = texture;
	info.GetReturnValue().Set(toWrap);
}

NAN_METHOD(sdl::RendererWrapper::GetInfo) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	SDL_RendererInfo* info = new SDL_RendererInfo;
	int err = SDL_GetRendererInfo(obj->renderer_, info);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
	info.GetReturnValue().Set(WrapRendererInfo(info));
}

NAN_METHOD(sdl::RendererWrapper::GetOutputSize) {
	RendererWrapper* obj = ObjectWrap::Unwrap<sdl::RendererWrapper>(info.This());

	int w, h;
	int err = SDL_GetRendererOutputSize(obj->renderer_, &w, &h);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
	Local<Array> ret = Array::New(2);
	ret->Set(0, Nan::New<Number>(w));
	ret->Set(1, Nan::New<Number>(h));
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::RendererWrapper::GetClipRect) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	SDL_Rect* rect = new SDL_Rect;
	SDL_RenderGetClipRect(obj->renderer_, rect);

  NEW_WRAPPED(rect, RectWrapper, ret)

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::RendererWrapper::GetLogicalSize) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	int w, h;
	SDL_RenderGetLogicalSize(obj->renderer_, &w, &h);
	Handle<Array> ret = Array::New(2);
	ret->Set(0, Nan::New<Number>(w));
	ret->Set(1, Nan::New<Number>(h));

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::RendererWrapper::GetScale) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	float scaleX, scaleY;
	SDL_RenderGetScale(obj->renderer_, &scaleX, &scaleY);
	Handle<Array> ret = Array::New(2);
	ret->Set(0, Nan::New<Number>(scaleX));
	ret->Set(1, Nan::New<Number>(scaleY));

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::RendererWrapper::GetViewport) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	SDL_Rect* rect = new SDL_Rect;
	SDL_RenderGetViewport(obj->renderer_, rect);

  NEW_WRAPPED(rect, RectWrapper, ret)

	info.GetReturnValue().Set(ret);
}

// TODO: Implement.
NAN_METHOD(sdl::RendererWrapper::ReadPixels) {
	// RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());
	Nan::ThrowError("Not implemented.");
}

NAN_METHOD(sdl::RendererWrapper::TargetSupported) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	info.GetReturnValue().Set(Nan::New<Boolean>(SDL_RenderTargetSupported(obj->renderer_)));
}

NAN_METHOD(sdl::RendererWrapper::SetClipRect) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	int err;
	if(info[0]->IsUndefined()) {
		err = SDL_RenderSetClipRect(obj->renderer_, NULL);
	}
	else {
		RectWrapper* clip = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[0]));
		err = SDL_RenderSetClipRect(obj->renderer_, clip->wrapped);
	}
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::SetLogicalSize) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected setLogicalSize(Number, Number)"));
		return;
	}
	int w = info[0]->IsUndefined() ? 1 : info[0]->Int32Value();
	int h = info[1]->IsUndefined() ? 1 : info[1]->Int32Value();
	int err = SDL_RenderSetLogicalSize(obj->renderer_, w, h);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::SetScale) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected setLogicalSize(Number, Number)"));
		return;
	}
	double scaleX = info[0]->IsUndefined() ? 1 : info[0]->NumberValue();
	double scaleY = info[1]->IsUndefined() ? 1 : info[1]->NumberValue();
	int err = SDL_RenderSetLogicalSize(obj->renderer_, scaleX, scaleY);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}
NAN_METHOD(sdl::RendererWrapper::SetViewport) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	int err;
	if(info[0]->IsUndefined()) {
		err = SDL_RenderSetViewport(obj->renderer_, NULL);
	}
	else {
		RectWrapper* wrap = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[0]));
		err = SDL_RenderSetViewport(obj->renderer_, wrap->wrapped);
	}
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}
NAN_METHOD(sdl::RendererWrapper::SetDrawBlendMode) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	SDL_BlendMode mode = info[0]->IsUndefined() ? SDL_BLENDMODE_NONE : static_cast<SDL_BlendMode>(info[0]->Int32Value());
	int err = SDL_SetRenderDrawBlendMode(obj->renderer_, mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::SetDrawColor) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 4) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected setDrawColor(Number, Number, Number, Number)"));
		return;
	}
	int r = info[0]->IsUndefined() ? 0 : info[0]->Int32Value();
	int g = info[1]->IsUndefined() ? 0 : info[1]->Int32Value();
	int b = info[2]->IsUndefined() ? 0 : info[2]->Int32Value();
	int a = info[3]->IsUndefined() ? 0 : info[4]->Int32Value();
	int err = SDL_SetRenderDrawColor(obj->renderer_, r, g, b, a);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::SetTarget) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected setTarget(Texture)"));
		return;
	}
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(info[0]));
	int err = SDL_SetRenderTarget(obj->renderer_, tex->texture_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::Clear) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	int err = SDL_RenderClear(obj->renderer_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::Present) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());
	SDL_RenderPresent(obj->renderer_);
}

NAN_METHOD(sdl::RendererWrapper::Copy) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() > 3) {
		TextureWrapper* texture = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(info[0]));
		RectWrapper* src = info[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[1]));
		RectWrapper* dst = info[2]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[2]));
		double angle = info[3]->IsUndefined() ? 0 : info[3]->NumberValue();
		PointWrapper* point = info[4]->IsUndefined() ? NULL : ObjectWrap::Unwrap<PointWrapper>(Handle<Object>::Cast(info[4]));
		SDL_RendererFlip flip = info[5]->IsUndefined() ? SDL_FLIP_NONE : static_cast<SDL_RendererFlip>(info[5]->Int32Value());
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
		TextureWrapper* texture = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(info[0]));
		RectWrapper* src = info[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[1]));
		RectWrapper* dst = info[2]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[2]));
		int err = SDL_RenderCopy(obj->renderer_, texture->texture_,
			src == NULL ? NULL : src->wrapped,
			dst == NULL ? NULL : dst->wrapped);
		if(err < 0) {
			return ThrowSDLException(__func__);
		}
	}
}

NAN_METHOD(sdl::RendererWrapper::DrawLine) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 4) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected drawLine(Number, Number, Number, Number)"));
		return;
	}

	int x1 = info[0]->Int32Value();
	int y1 = info[1]->Int32Value();
	int x2 = info[2]->Int32Value();
	int y2 = info[3]->Int32Value();
	int err = SDL_RenderDrawLine(obj->renderer_, x1, y1, x2, y2);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::DrawLines) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected drawLines(Array)"));
		return;
	}

	Handle<Array> arr = Handle<Array>::Cast(info[0]);
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
}

NAN_METHOD(sdl::RendererWrapper::DrawPoint) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected drawPoint(Point)"));
		return;
	}

	int x = info[0]->Int32Value();
	int y = info[1]->Int32Value();
	int err = SDL_RenderDrawPoint(obj->renderer_, x, y);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::DrawPoints) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected drawPoints(Array)"));
		return;
	}

	Handle<Array> arr = Handle<Array>::Cast(info[0]);
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
}

NAN_METHOD(sdl::RendererWrapper::DrawRect) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected drawRect(Rect)"));
		return;
	}

	RectWrapper* rect = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[0]));
	int err = SDL_RenderDrawRect(obj->renderer_, rect->wrapped);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::DrawRects) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected drawRects(Array)"));
		return;
	}

	Handle<Array> arr = Handle<Array>::Cast(info[0]);
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
}

NAN_METHOD(sdl::RendererWrapper::FillRect) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected drawRect(Rect)"));
		return;
	}

	RectWrapper* rect = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[0]));
	int err = SDL_RenderFillRect(obj->renderer_, rect->wrapped);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::RendererWrapper::FillRects) {
	RendererWrapper* obj = ObjectWrap::Unwrap<RendererWrapper>(info.This());

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected drawRects(Array)"));
		return;
	}

	Handle<Array> arr = Handle<Array>::Cast(info[0]);
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
}
