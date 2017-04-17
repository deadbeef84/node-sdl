#include "surface.h"
#include "helpers.h"
#include "struct_wrappers.h"
#include "container.h"
#include <iostream>

using namespace v8;
using namespace node;

Nan::Persistent<FunctionTemplate> sdl::SurfaceWrapper::constructor;

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
	Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(STRING_NEW("SurfaceWrapper"));

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

	constructor.Reset(tpl);
	Nan::Set(target, STRING_NEW("Surface"), tpl->GetFunction());
}
NAN_METHOD(sdl::SurfaceWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("Use the new operator to create instances of a Surface.").ToLocalChecked());
		return;
	}

	if(info[0]->IsExternal()) {
		SurfaceWrapper* obj = new SurfaceWrapper();
		obj->surface_ = static_cast<SDL_Surface*>(Handle<External>::Cast(info[0])->Value());
		obj->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}
	else {
		if(info.Length() < 2) {
			Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected new sdl.Surface(Number, Number)"));
		return;
		}

		int flags = 0;
		int width = info[0]->Int32Value();
		int height = info[1]->Int32Value();
		int depth = info[2]->IsUndefined() ? 32 : info[2]->Int32Value();
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
	    obj->Wrap(info.This());
	    info.GetReturnValue().Set(info.This());
	}
}

NAN_METHOD(sdl::SurfaceWrapper::LoadBMP) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected loadBMP(String)"));
		return;
	}

	String::Utf8Value file(info[0]);
	SDL_Surface* surface = SDL_LoadBMP(*file);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	SurfaceWrapper* obj = new SurfaceWrapper();
	obj->surface_ = surface;
	Handle<Object> ret = Nan::New<Object>();
	obj->Wrap(ret);

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::SurfaceWrapper::LoadBMPRW) {
	// TODO: Implement LoadBMPRW.
	Nan::ThrowTypeError(Nan::New("LoadBMPRW is not implemented yet.").ToLocalChecked());
}

NAN_METHOD(sdl::SurfaceWrapper::SaveBMP) {
	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected saveBMP(Surface, String)"));
		return;
	}

	SurfaceWrapper* wrap = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[0]));
	String::Utf8Value file(info[1]);
	int err = SDL_SaveBMP(wrap->surface_, *file);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::SaveBMPRW) {
	// TODO Implement SaveBMPRW.
	Nan::ThrowTypeError(Nan::New("SaveBMPRW is not implemented yet.").ToLocalChecked());
		return;
}

NAN_METHOD(sdl::SurfaceWrapper::BlitScaled) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected blitScaled(Surface, Rect[, Rect])"));
		return;
	}

	SurfaceWrapper* obj = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SurfaceWrapper* other = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[0]));
	RectWrapper* dst = info[1]->IsUndefined() ? NULL : Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[1]));
	RectWrapper* src = info[2]->IsUndefined() ? NULL : Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[2]));
	int err = SDL_BlitScaled(obj->surface_,
		src == NULL ? NULL : src->rect_,
		other->surface_,
		dst == NULL ? NULL : dst->rect_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::BlitSurface) {
	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected blitSurface(Surface, Rect[, Rect])"));
		return;
	}

	SurfaceWrapper* obj = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SurfaceWrapper* other = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[0]));
	RectWrapper* dst = Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[1]));
	RectWrapper* src = info[2]->IsUndefined() ? NULL : Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[2]));
	int err = SDL_BlitSurface(obj->surface_, src->rect_, other->surface_, dst == NULL ? NULL : dst->rect_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::LowerBlit) {
	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected lowerBlit(Surface, Rect[, Rect])"));
		return;
	}

	SurfaceWrapper* obj = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SurfaceWrapper* other = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[0]));
	RectWrapper* dst = Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[1]));
	RectWrapper* src = info[2]->IsUndefined() ? NULL : Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[2]));
	int err = SDL_LowerBlit(obj->surface_, src->rect_, other->surface_, dst == NULL ? NULL : dst->rect_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::LowerBlitScaled) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected lowerBlitScaled(Surface, Rect[, Rect])"));
		return;
	}

	SurfaceWrapper* obj = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SurfaceWrapper* other = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[0]));
	RectWrapper* dst = info[1]->IsUndefined() ? NULL : Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[1]));
	RectWrapper* src = info[2]->IsUndefined() ? NULL : Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[2]));
	int err = SDL_LowerBlitScaled(obj->surface_,
		src == NULL ? NULL : src->rect_,
		other->surface_,
		dst == NULL ? NULL : dst->rect_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::ConvertSurface) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected convertSurface(PixelFormat)"));
		return;
	}

	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SDL_PixelFormat* fmt = UnwrapPixelFormat(Handle<Object>::Cast(info[0]));
	SDL_Surface* ret = SDL_ConvertSurface(self->surface_, fmt, 0);
	if(NULL == ret) {
		return ThrowSDLException(__func__);
	}

	SurfaceWrapper* obj = new SurfaceWrapper();
	obj->surface_ = ret;
	Handle<Object> objRet = Nan::New<Object>();
	obj->Wrap(objRet);
	info.GetReturnValue().Set(objRet);
}

NAN_METHOD(sdl::SurfaceWrapper::ConvertSurfaceFormat) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected convertSurfaceFormat(Number)"));
		return;
	}

	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	int fmt = info[0]->Int32Value();
	SDL_Surface* ret = SDL_ConvertSurfaceFormat(self->surface_, fmt, 0);
	if(NULL == ret) {
		return ThrowSDLException(__func__);
	}

	SurfaceWrapper* obj = new SurfaceWrapper();
	obj->surface_ = ret;
	Handle<Object> objRet = Nan::New<Object>();
	obj->Wrap(objRet);
	info.GetReturnValue().Set(objRet);
}

NAN_METHOD(sdl::SurfaceWrapper::FillRect) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected fillRect(Number[, Rect])"));
		return;
	}

	Handle<Object> handleObj = Handle<Object>::Cast(info.This());
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(handleObj);
	int color = info[0]->Int32Value();
	RectWrapper* rect = info[1]->IsUndefined() ? NULL : Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[1]));
	int err = SDL_FillRect(self->surface_, rect == NULL ? NULL : rect->rect_, color);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::FillRects) {
	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected fillRect(Number, Array)"));
		return;
	}

	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	int color = info[0]->Int32Value();
	Handle<Array> arr = Handle<Array>::Cast(info[1]);
	int numRects = arr->Length();
	SDL_Rect* rects = new SDL_Rect[numRects];
	for(int i = 0; i < numRects; i++) {
		RectWrapper* rect = Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(arr->Get(i)));
		rects[i] = *rect->rect_;
	}
	int err = SDL_FillRects(self->surface_, rects, numRects, color);
	delete rects;
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::GetClipRect) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SDL_Rect* rect = new SDL_Rect;
	SDL_GetClipRect(self->surface_, rect);

  NEW_WRAPPED(rect, RectWrapper, ret)

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::SurfaceWrapper::GetColorKey) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	uint32_t colorKey;
	int err = SDL_GetColorKey(self->surface_, &colorKey);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(colorKey));
}

NAN_METHOD(sdl::SurfaceWrapper::GetAlphaMod) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	uint8_t alphaMod;
	int err = SDL_GetSurfaceAlphaMod(self->surface_, &alphaMod);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(alphaMod));
}

NAN_METHOD(sdl::SurfaceWrapper::GetBlendMode) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SDL_BlendMode mode;
	int err = SDL_GetSurfaceBlendMode(self->surface_, &mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(mode));
}

NAN_METHOD(sdl::SurfaceWrapper::GetColorMod) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	uint8_t r, g, b;
	int err = SDL_GetSurfaceColorMod(self->surface_, &r, &g, &b);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	Handle<Array> ret = Nan::New<Array>(3);
	ret->Set(0, Nan::New<Number>(r));
	ret->Set(1, Nan::New<Number>(g));
	ret->Set(2, Nan::New<Number>(b));
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::SurfaceWrapper::GetWidth) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	info.GetReturnValue().Set(Nan::New<Number>(self->surface_->w));
}

NAN_METHOD(sdl::SurfaceWrapper::GetHeight) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	info.GetReturnValue().Set(Nan::New<Number>(self->surface_->h));
}

NAN_METHOD(sdl::SurfaceWrapper::GetPitch) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	info.GetReturnValue().Set(Nan::New<Number>(self->surface_->pitch));
}

NAN_METHOD(sdl::SurfaceWrapper::GetPixelFormat) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	info.GetReturnValue().Set(WrapPixelFormat(self->surface_->format));
}

NAN_METHOD(sdl::SurfaceWrapper::SetClipRect) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected setClipRect(Rect)"));
		return;
	}
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	RectWrapper* clip = Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[0]));
	SDL_bool ret = SDL_SetClipRect(self->surface_, clip->rect_);

	info.GetReturnValue().Set(Nan::New<Boolean>(ret));
}

NAN_METHOD(sdl::SurfaceWrapper::SetColorKey) {
	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected setColorKey(Boolean, Number)"));
		return;
	}
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	int flag = info[0]->BooleanValue() ? 1 : 0;
	uint32_t key = info[1]->Int32Value();
	int err = SDL_SetColorKey(self->surface_, flag, key);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::SetAlphaMod) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected setAlphaMod(Number)"));
		return;
	}
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	uint8_t alpha = static_cast<uint8_t>(info[0]->Int32Value());
	int err = SDL_SetSurfaceAlphaMod(self->surface_, alpha);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::SetBlendMode) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected setBlendMode(Number)"));
		return;
	}
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SDL_BlendMode mode = static_cast<SDL_BlendMode>(info[0]->Int32Value());
	int err = SDL_SetSurfaceBlendMode(self->surface_, mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::SetColorMod) {
	if(info.Length() < 3) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected setColorMod(Number, Number, Number)"));
		return;
	}
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	uint8_t r = static_cast<uint8_t>(info[0]->Int32Value());
	uint8_t g = static_cast<uint8_t>(info[1]->Int32Value());
	uint8_t b = static_cast<uint8_t>(info[2]->Int32Value());
	int err = SDL_SetSurfaceColorMod(self->surface_, r, g, b);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::SetPalette) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected setPalette(Palette)"));
		return;
	}
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SDL_Palette* palette = UnwrapPalette(Handle<Object>::Cast(info[0]));
	int err = SDL_SetSurfacePalette(self->surface_, palette);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::SetRLE) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expected setRLE(Number)"));
		return;
	}
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	int flags = info[0]->Int32Value();
	int err = SDL_SetSurfaceRLE(self->surface_, flags);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::Lock) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	int err = SDL_LockSurface(self->surface_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::SurfaceWrapper::Unlock) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	SDL_UnlockSurface(self->surface_);
}

NAN_METHOD(sdl::SurfaceWrapper::MustLock) {
	SurfaceWrapper* self = Nan::ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info.This()));
	info.GetReturnValue().Set(Nan::New<Boolean>(SDL_MUSTLOCK(self->surface_)));
}
