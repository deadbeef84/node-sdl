#include "surface.h"
#include "helpers.h"
#include "struct_wrappers.h"
#include "container.h"
#include <iostream>

using namespace v8;
using namespace node;

Persistent<FunctionTemplate> sdl::SurfaceWrapper::constructor;

sdl::SurfaceWrapper::SurfaceWrapper() {
}

sdl::SurfaceWrapper::SurfaceWrapper(Handle<Object> toWrap) {
	Wrap(toWrap);
}

sdl::SurfaceWrapper::~SurfaceWrapper() {
	if(NULL != surface_) {
		SDL_FreeSurface(surface_);
	}
}

NAN_MODULE_INIT(sdl::SurfaceWrapper::Init) {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("SurfaceWrapper"));

	Nan::SetPrototypeMethod(tpl, "loadBMP", LoadBMP);
	Nan::SetPrototypeMethod(tpl, "loadBMPRW", LoadBMPRW);
	Nan::SetPrototypeMethod(tpl, "saveBMP", SaveBMP);
	Nan::SetPrototypeMethod(tpl, "saveBMPRW", SaveBMPRW);

	Nan::SetPrototypeMethod(tpl, "blitScaled", BlitScaled);
	Nan::SetPrototypeMethod(tpl, "blitSurface", BlitSurface);
	Nan::SetPrototypeMethod(tpl, "lowerBlit", LowerBlit);
	Nan::SetPrototypeMethod(tpl, "lowerBlitScaled", LowerBlitScaled);
	Nan::SetPrototypeMethod(tpl, "convertSurface", ConvertSurface);
	Nan::SetPrototypeMethod(tpl, "convertSurfaceFormat", ConvertSurfaceFormat);
	Nan::SetPrototypeMethod(tpl, "getWidth", GetWidth);
	Nan::SetPrototypeMethod(tpl, "getHeight", GetHeight);
	Nan::SetPrototypeMethod(tpl, "getPitch", GetPitch);
	Nan::SetPrototypeMethod(tpl, "getPixelFormat", GetPixelFormat);

	Nan::SetPrototypeMethod(tpl, "fillRect", FillRect);
	Nan::SetPrototypeMethod(tpl, "fillRects", FillRects);

	Nan::SetPrototypeMethod(tpl, "getClipRect", GetClipRect);
	Nan::SetPrototypeMethod(tpl, "getColorKey", GetColorKey);
	Nan::SetPrototypeMethod(tpl, "getAlphaMod", GetAlphaMod);
	Nan::SetPrototypeMethod(tpl, "getBlendMode", GetBlendMode);
	Nan::SetPrototypeMethod(tpl, "getColorMod", GetColorMod);

	Nan::SetPrototypeMethod(tpl, "setClipRect", SetClipRect);
	Nan::SetPrototypeMethod(tpl, "setColorKey", SetColorKey);
	Nan::SetPrototypeMethod(tpl, "setAlphaMod", SetAlphaMod);
	Nan::SetPrototypeMethod(tpl, "setBlendMode", SetBlendMode);
	Nan::SetPrototypeMethod(tpl, "setColorMod", SetColorMod);
	Nan::SetPrototypeMethod(tpl, "setPalette", SetPalette);
	Nan::SetPrototypeMethod(tpl, "setRLE", SetRLE);

	Nan::SetPrototypeMethod(tpl, "lock", Lock);
	Nan::SetPrototypeMethod(tpl, "unlock", Unlock);
	Nan::SetPrototypeMethod(tpl, "mustLock", MustLock);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Surface"), constructor);
}
NAN_METHOD(sdl::SurfaceWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Use the new operator to create instances of a Surface.")));
	}


	if(args[0]->IsExternal()) {
		SurfaceWrapper* obj = new SurfaceWrapper();
		obj->surface_ = static_cast<SDL_Surface*>(Handle<External>::Cast(args[0])->Value());
		obj->Wrap(args.This());
		return args.This();
	}
	else {
		if(args.Length() < 2) {
			return ThrowException(Exception::TypeError(
				String::New("Invalid arguments: expected new sdl.Surface(Number, Number)")));
		}

		int flags = 0;
		int width = args[0]->Int32Value();
		int height = args[1]->Int32Value();
		int depth = args[2]->IsUndefined() ? 32 : args[2]->Int32Value();
		int rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
	#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
	#endif
	    SDL_Surface* surface = SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask);
	    if(NULL == surface) {
	    	return ThrowSDLException(__func__);
	    }

	    SurfaceWrapper* obj = new SurfaceWrapper();
	    obj->surface_ = surface;
	    obj->Wrap(args.This());
	    return args.This();
	}
}

NAN_METHOD(sdl::SurfaceWrapper::LoadBMP) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected loadBMP(String)")));
	}

	String::Utf8Value file(args[0]);
	SDL_Surface* surface = SDL_LoadBMP(*file);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	SurfaceWrapper* obj = new SurfaceWrapper();
	obj->surface_ = surface;
	Handle<Object> ret = Object::New();
	obj->Wrap(ret);

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::SurfaceWrapper::LoadBMPRW) {
	// TODO: Implement LoadBMPRW.
	return ThrowException(Exception::TypeError(
		String::New("LoadBMPRW is not implemented yet.")));
}
NAN_METHOD(sdl::SurfaceWrapper::SaveBMP) {


	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected saveBMP(Surface, String)")));
	}

	SurfaceWrapper* wrap = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	String::Utf8Value file(args[1]);
	int err = SDL_SaveBMP(wrap->surface_, *file);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::SaveBMPRW) {
	// TODO Implement SaveBMPRW.
	return ThrowException(Exception::TypeError(
		String::New("SaveBMPRW is not implemented yet.")));
}

NAN_METHOD(sdl::SurfaceWrapper::BlitScaled) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected blitScaled(Surface, Rect[, Rect])")));
	}

	SurfaceWrapper* obj = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SurfaceWrapper* other = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	RectWrapper* dst = args[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[1]));
	RectWrapper* src = args[2]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[2]));
	int err = SDL_BlitScaled(obj->surface_,
		src == NULL ? NULL : src->wrapped,
		other->surface_,
		dst == NULL ? NULL : dst->wrapped);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::BlitSurface) {


	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected blitSurface(Surface, Rect[, Rect])")));
	}

	SurfaceWrapper* obj = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SurfaceWrapper* other = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	RectWrapper* dst = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[1]));
	RectWrapper* src = args[2]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[2]));
	int err = SDL_BlitSurface(obj->surface_, src->wrapped, other->surface_, dst == NULL ? NULL : dst->wrapped);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::LowerBlit) {


	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected lowerBlit(Surface, Rect[, Rect])")));
	}

	SurfaceWrapper* obj = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SurfaceWrapper* other = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	RectWrapper* dst = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[1]));
	RectWrapper* src = args[2]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[2]));
	int err = SDL_LowerBlit(obj->surface_, src->wrapped, other->surface_, dst == NULL ? NULL : dst->wrapped);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::LowerBlitScaled) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected lowerBlitScaled(Surface, Rect[, Rect])")));
	}

	SurfaceWrapper* obj = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SurfaceWrapper* other = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	RectWrapper* dst = args[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[1]));
	RectWrapper* src = args[2]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[2]));
	int err = SDL_LowerBlitScaled(obj->surface_,
		src == NULL ? NULL : src->wrapped,
		other->surface_,
		dst == NULL ? NULL : dst->wrapped);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::ConvertSurface) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected convertSurface(PixelFormat)")));
	}

	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SDL_PixelFormat* fmt = UnwrapPixelFormat(Handle<Object>::Cast(args[0]));
	SDL_Surface* ret = SDL_ConvertSurface(self->surface_, fmt, 0);
	if(NULL == ret) {
		return ThrowSDLException(__func__);
	}

	SurfaceWrapper* obj = new SurfaceWrapper();
	obj->surface_ = ret;
	Handle<Object> objRet = Object::New();
	obj->Wrap(objRet);
	info.GetReturnValue().Set(objRet);
}
NAN_METHOD(sdl::SurfaceWrapper::ConvertSurfaceFormat) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected convertSurfaceFormat(Number)")));
	}

	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	int fmt = args[0]->Int32Value();
	SDL_Surface* ret = SDL_ConvertSurfaceFormat(self->surface_, fmt, 0);
	if(NULL == ret) {
		return ThrowSDLException(__func__);
	}

	SurfaceWrapper* obj = new SurfaceWrapper();
	obj->surface_ = ret;
	Handle<Object> objRet = Object::New();
	obj->Wrap(objRet);
	info.GetReturnValue().Set(objRet);
}

NAN_METHOD(sdl::SurfaceWrapper::FillRect) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected fillRect(Number[, Rect])")));
	}

	Handle<Object> handleObj = Handle<Object>::Cast(args.This());
	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(handleObj);
	int color = args[0]->Int32Value();
	RectWrapper* rect = args[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[1]));
	int err = SDL_FillRect(self->surface_, rect == NULL ? NULL : rect->wrapped, color);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::FillRects) {


	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected fillRect(Number, Array)")));
	}

	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	int color = args[0]->Int32Value();
	Handle<Array> arr = Handle<Array>::Cast(args[1]);
	int numRects = arr->Length();
	SDL_Rect* rects = new SDL_Rect[numRects];
	for(int i = 0; i < numRects; i++) {
		RectWrapper* rect = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(arr->Get(i)));
		rects[i] = *rect->wrapped;
	}
	int err = SDL_FillRects(self->surface_, rects, numRects, color);
	delete rects;
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}

NAN_METHOD(sdl::SurfaceWrapper::GetClipRect) {


	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SDL_Rect* rect = new SDL_Rect;
	SDL_GetClipRect(self->surface_, rect);

  NEW_WRAPPED(rect, RectWrapper, ret)

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::SurfaceWrapper::GetColorKey) {


	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	uint32_t colorKey;
	int err = SDL_GetColorKey(self->surface_, &colorKey);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(colorKey));
}
NAN_METHOD(sdl::SurfaceWrapper::GetAlphaMod) {


	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	uint8_t alphaMod;
	int err = SDL_GetSurfaceAlphaMod(self->surface_, &alphaMod);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(alphaMod));
}
NAN_METHOD(sdl::SurfaceWrapper::GetBlendMode) {


	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SDL_BlendMode mode;
	int err = SDL_GetSurfaceBlendMode(self->surface_, &mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(mode));
}
NAN_METHOD(sdl::SurfaceWrapper::GetColorMod) {


	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	uint8_t r, g, b;
	int err = SDL_GetSurfaceColorMod(self->surface_, &r, &g, &b);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	Handle<Array> ret = Array::New(3);
	ret->Set(0, Number::New(r));
	ret->Set(1, Number::New(g));
	ret->Set(2, Number::New(b));
	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::SurfaceWrapper::GetWidth) {

	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	info.GetReturnValue().Set(Number::New(self->surface_->w));
}
NAN_METHOD(sdl::SurfaceWrapper::GetHeight) {

	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	info.GetReturnValue().Set(Number::New(self->surface_->h));
}
NAN_METHOD(sdl::SurfaceWrapper::GetPitch) {

	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	info.GetReturnValue().Set(Number::New(self->surface_->pitch));
}
NAN_METHOD(sdl::SurfaceWrapper::GetPixelFormat) {

	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	info.GetReturnValue().Set(WrapPixelFormat(self->surface_->format));
}

NAN_METHOD(sdl::SurfaceWrapper::SetClipRect) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected setClipRect(Rect)")));
	}
	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	RectWrapper* clip = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[0]));
	SDL_bool ret = SDL_SetClipRect(self->surface_, clip->wrapped);

	info.GetReturnValue().Set(Boolean::New(ret));
}
NAN_METHOD(sdl::SurfaceWrapper::SetColorKey) {


	if(args.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected setColorKey(Boolean, Number)")));
	}
	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	int flag = args[0]->BooleanValue() ? 1 : 0;
	uint32_t key = args[1]->Int32Value();
	int err = SDL_SetColorKey(self->surface_, flag, key);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::SetAlphaMod) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected setAlphaMod(Number)")));
	}
	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	uint8_t alpha = static_cast<uint8_t>(args[0]->Int32Value());
	int err = SDL_SetSurfaceAlphaMod(self->surface_, alpha);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::SetBlendMode) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected setBlendMode(Number)")));
	}
	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SDL_BlendMode mode = static_cast<SDL_BlendMode>(args[0]->Int32Value());
	int err = SDL_SetSurfaceBlendMode(self->surface_, mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::SetColorMod) {


	if(args.Length() < 3) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected setColorMod(Number, Number, Number)")));
	}
	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	uint8_t r = static_cast<uint8_t>(args[0]->Int32Value());
	uint8_t g = static_cast<uint8_t>(args[1]->Int32Value());
	uint8_t b = static_cast<uint8_t>(args[2]->Int32Value());
	int err = SDL_SetSurfaceColorMod(self->surface_, r, g, b);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::SetPalette) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected setPalette(Palette)")));
	}
	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SDL_Palette* palette = UnwrapPalette(Handle<Object>::Cast(args[0]));
	int err = SDL_SetSurfacePalette(self->surface_, palette);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::SetRLE) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expected setRLE(Number)")));
	}
	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	int flags = args[0]->Int32Value();
	int err = SDL_SetSurfaceRLE(self->surface_, flags);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}

NAN_METHOD(sdl::SurfaceWrapper::Lock) {


	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	int err = SDL_LockSurface(self->surface_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::Unlock) {


	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	SDL_UnlockSurface(self->surface_);

	return Undefined();
}
NAN_METHOD(sdl::SurfaceWrapper::MustLock) {


	SurfaceWrapper* self = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args.This()));
	info.GetReturnValue().Set(Boolean::New(SDL_MUSTLOCK(self->surface_)));
}
