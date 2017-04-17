#include <iostream>

#include "texture.h"
#include "surface.h"
#include "helpers.h"
#include "struct_wrappers.h"
#include "render.h"
#include "container.h"

#include "SDL.h"

using namespace v8;

////////////////////////////////////////////////////////////////////////////////
// TextureWrapper Class Definition.
Nan::Persistent<FunctionTemplate> sdl::TextureWrapper::constructor;

sdl::TextureWrapper::TextureWrapper() {
}

sdl::TextureWrapper::TextureWrapper(Handle<Object> toWrap) {
	Wrap(toWrap);
}

sdl::TextureWrapper::~TextureWrapper() {
	if(NULL != texture_) {
		SDL_DestroyTexture(texture_);
	}
}

NAN_MODULE_INIT(sdl::TextureWrapper::Init) {
  // Setup hardware renderer construction.
	Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(STRING_NEW("TextureWrapper"));

	Nan::SetPrototypeMethod(tpl, "getAlphaMod", GetAlphaMod);
	Nan::SetPrototypeMethod(tpl, "getBlendMode", GetBlendMode);
	Nan::SetPrototypeMethod(tpl, "getColorMod", GetColorMod);
	Nan::SetPrototypeMethod(tpl, "getFormat", GetFormat);
	Nan::SetPrototypeMethod(tpl, "getSize", GetSize);
	Nan::SetPrototypeMethod(tpl, "getWidth", GetWidth);
	Nan::SetPrototypeMethod(tpl, "getHeight", GetHeight);

	Nan::SetPrototypeMethod(tpl, "setAlphaMod", SetAlphaMod);
	Nan::SetPrototypeMethod(tpl, "setBlendMode", SetBlendMode);
	Nan::SetPrototypeMethod(tpl, "setColorMod", SetColorMod);

	// Nan::SetPrototypeMethod(tpl, "lock", Lock);
	// Nan::SetPrototypeMethod(tpl, "unlock", Unlock);

	Nan::SetPrototypeMethod(tpl, "update", Update);

	constructor.Reset(tpl);
	Nan::Set(target, STRING_NEW("Texture"), tpl->GetFunction());
}

NAN_METHOD(sdl::TextureWrapper::New) {
	// std::cout << "Texture::New - Checking for constructor call." << std::endl;
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("Use the new operator to create instances of a Texture.").ToLocalChecked());
		return;
	}

	SDL_Texture* tex;
	// std::cout << "Texture::New - Unwrapping RendererWrapper from first argument." << std::endl;
	RendererWrapper* r = ObjectWrap::Unwrap<RendererWrapper>(Handle<Object>::Cast(info[0]));
	// std::cout << "Texture::New - Done. Checking arguments length." << std::endl;
	if(info.Length() > 2) {
		// std::cout << "Texture::New - Found more than 2 arguments. Pulling format, access, w, h." << std::endl;
		int format = info[1]->IsUndefined() ? SDL_PIXELFORMAT_UNKNOWN : info[1]->Int32Value();
		int access = info[2]->IsUndefined() ? SDL_TEXTUREACCESS_STREAMING : info[2]->Int32Value();
		int w = info[3]->IsUndefined() ? 1 : info[3]->Int32Value();
		int h = info[4]->IsUndefined() ? 1 : info[4]->Int32Value();
		// std::cout << "Texture::New - Done. Calling SDL_CreateTexture." << std::endl;
		tex = SDL_CreateTexture(r->renderer_, format, access, w, h);
		// std::cout << "Texture::New - Done." << std::endl;
	}
	else if(info.Length() == 2) {
		// std::cout << "Texture::New - Found 2 arguments. Pulling SurfaceWrapper from second arg." << std::endl;
		SurfaceWrapper* wrap = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[1]));
		// std::cout << "Texture::New - Done. Calling SDL_CreateTextureFromSurface." << std::endl;
		tex = SDL_CreateTextureFromSurface(r->renderer_, wrap->surface_);
		// std::cout << "Texture::New - Done." << std::endl;
	}
	else {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: expecting new sdl.Texture(Renderer, Surface) or new sdl.Texture(Renderer, Number, Number, Number, Number)"));
		return;
	}
	if(NULL == tex) {
		return ThrowSDLException(__func__);
	}

	// std::cout << "Texture::New - Creating new TextureWrapper." << std::endl;
	TextureWrapper* obj = new TextureWrapper();
	// std::cout << "Texture::New - Setting texture_ to created tex." << std::endl;
	obj->texture_ = tex;
	// std::cout << "Texture::New - Wrapping info.This()." << std::endl;
	obj->Wrap(info.This());

	// std::cout << "Texture::New - Returning info.This()." << std::endl;
	info.GetReturnValue().Set(info.This());
}

NAN_METHOD(sdl::TextureWrapper::GetAlphaMod) {
	uint8_t alpha;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_GetTextureAlphaMod(tex->texture_, &alpha);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(alpha));
}

NAN_METHOD(sdl::TextureWrapper::GetBlendMode) {
	SDL_BlendMode mode;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_GetTextureBlendMode(tex->texture_, &mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(mode));
}

NAN_METHOD(sdl::TextureWrapper::GetColorMod) {
	uint8_t r, g, b;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_GetTextureColorMod(tex->texture_, &r, &g, &b);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> ret = Nan::New<Object>();
	ret->Set(STRING_NEW("r"), Nan::New<Number>(r));
	ret->Set(STRING_NEW("g"), Nan::New<Number>(g));
	ret->Set(STRING_NEW("b"), Nan::New<Number>(b));

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::TextureWrapper::GetFormat) {
	uint32_t format;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_QueryTexture(tex->texture_, &format, NULL, NULL, NULL);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(format));
}

NAN_METHOD(sdl::TextureWrapper::GetSize) {
	int access;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_QueryTexture(tex->texture_, NULL, &access, NULL, NULL);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(access));
}
NAN_METHOD(sdl::TextureWrapper::GetWidth) {
	int width;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_QueryTexture(tex->texture_, NULL, NULL, &width, NULL);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(width));
}

NAN_METHOD(sdl::TextureWrapper::GetHeight) {
	int height;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_QueryTexture(tex->texture_, NULL, NULL, NULL, &height);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(height));
}

NAN_METHOD(sdl::TextureWrapper::SetAlphaMod) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected texture.setAlphaMod(Number)"));
		return;
	}

	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_SetTextureAlphaMod(tex->texture_, static_cast<uint8_t>(info[0]->Uint32Value()));
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::TextureWrapper::SetBlendMode) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected texture.setBlendMode(Number)"));
		return;
	}

	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int err = SDL_SetTextureBlendMode(tex->texture_, static_cast<SDL_BlendMode>(info[0]->Int32Value()));
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::TextureWrapper::SetColorMod) {
	if(info.Length() < 3) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected texture.setColorMod(Number, Number, Number)"));
		return;
	}

	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
	int r = info[0]->Int32Value();
	int g = info[1]->Int32Value();
	int b = info[2]->Int32Value();
	int err = SDL_SetTextureColorMod(tex->texture_, r, g, b);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}

// NAN_METHOD(sdl::TextureWrapper::Lock) {
//

// 	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
// 	int err = SDL_LockTexture(tex->texture_);
// 	if(err < 0) {
// 		return ThrowSDLException(__func__);
// 	}

// 	return Undefined();
// }
// NAN_METHOD(sdl::TextureWrapper::Unlock) {
//

// 	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(info.This());
// 	int err = SDL_UnlockTexture(tex->texture_);
// 	if(err < 0) {
// 		return ThrowSDLException(__func__);
// 	}

// 	return Undefined();
// }

NAN_METHOD(sdl::TextureWrapper::Update) {
	if(!info[0]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to texture.update must be an Object.").ToLocalChecked());
		return;
	}

	TextureWrapper* texture = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(info.This()));
	if(NULL == texture) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Failed to unwrap this argument to a SurfaceWrapper. (is this not an sdl.Texture?)"));
		return;
	}
	SurfaceWrapper* surface = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(info[0]));
	if(NULL == surface) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Failed to unwrap first argument to a SurfaceWrapper. (did you not pass in an sdl.Surface?)"));
		return;
	}
	RectWrapper* rect = info[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[1]));
	int err = SDL_UpdateTexture(texture->texture_, rect == NULL ? NULL : rect->rect_, surface->surface_->pixels, surface->surface_->pitch);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}
}
