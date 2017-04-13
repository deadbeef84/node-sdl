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
Persistent<FunctionTemplate> sdl::TextureWrapper::constructor;

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
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("TextureWrapper"));

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

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Texture"), constructor);
}

NAN_METHOD(sdl::TextureWrapper::New) {
	// std::cout << "Texture::New - Checking for constructor call." << std::endl;
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Use the new operator to create instances of a Texture.")));
	}



	SDL_Texture* tex;
	// std::cout << "Texture::New - Unwrapping RendererWrapper from first argument." << std::endl;
	RendererWrapper* r = ObjectWrap::Unwrap<RendererWrapper>(Handle<Object>::Cast(args[0]));
	// std::cout << "Texture::New - Done. Checking arguments length." << std::endl;
	if(args.Length() > 2) {
		// std::cout << "Texture::New - Found more than 2 arguments. Pulling format, access, w, h." << std::endl;
		int format = args[1]->IsUndefined() ? SDL_PIXELFORMAT_UNKNOWN : args[1]->Int32Value();
		int access = args[2]->IsUndefined() ? SDL_TEXTUREACCESS_STREAMING : args[2]->Int32Value();
		int w = args[3]->IsUndefined() ? 1 : args[3]->Int32Value();
		int h = args[4]->IsUndefined() ? 1 : args[4]->Int32Value();
		// std::cout << "Texture::New - Done. Calling SDL_CreateTexture." << std::endl;
		tex = SDL_CreateTexture(r->renderer_, format, access, w, h);
		// std::cout << "Texture::New - Done." << std::endl;
	}
	else if(args.Length() == 2) {
		// std::cout << "Texture::New - Found 2 arguments. Pulling SurfaceWrapper from second arg." << std::endl;
		SurfaceWrapper* wrap = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[1]));
		// std::cout << "Texture::New - Done. Calling SDL_CreateTextureFromSurface." << std::endl;
		tex = SDL_CreateTextureFromSurface(r->renderer_, wrap->surface_);
		// std::cout << "Texture::New - Done." << std::endl;
	}
	else {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: expecting new sdl.Texture(Renderer, Surface) or new sdl.Texture(Renderer, Number, Number, Number, Number)")));
	}
	if(NULL == tex) {
		return ThrowSDLException(__func__);
	}

	// std::cout << "Texture::New - Creating new TextureWrapper." << std::endl;
	TextureWrapper* obj = new TextureWrapper();
	// std::cout << "Texture::New - Setting texture_ to created tex." << std::endl;
	obj->texture_ = tex;
	// std::cout << "Texture::New - Wrapping args.This()." << std::endl;
	obj->Wrap(args.This());

	// std::cout << "Texture::New - Returning args.This()." << std::endl;
	return args.This();
}

NAN_METHOD(sdl::TextureWrapper::GetAlphaMod) {


	uint8_t alpha;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_GetTextureAlphaMod(tex->texture_, &alpha);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(alpha));
}
NAN_METHOD(sdl::TextureWrapper::GetBlendMode) {


	SDL_BlendMode mode;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_GetTextureBlendMode(tex->texture_, &mode);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(mode));
}
NAN_METHOD(sdl::TextureWrapper::GetColorMod) {


	uint8_t r, g, b;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_GetTextureColorMod(tex->texture_, &r, &g, &b);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> ret = Object::New();
	ret->Set(String::NewSymbol("r"), Number::New(r));
	ret->Set(String::NewSymbol("g"), Number::New(g));
	ret->Set(String::NewSymbol("b"), Number::New(b));

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::TextureWrapper::GetFormat) {


	uint32_t format;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_QueryTexture(tex->texture_, &format, NULL, NULL, NULL);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(format));
}
NAN_METHOD(sdl::TextureWrapper::GetSize) {


	int access;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_QueryTexture(tex->texture_, NULL, &access, NULL, NULL);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(access));
}
NAN_METHOD(sdl::TextureWrapper::GetWidth) {


	int width;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_QueryTexture(tex->texture_, NULL, NULL, &width, NULL);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(width));
}
NAN_METHOD(sdl::TextureWrapper::GetHeight) {


	int height;
	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_QueryTexture(tex->texture_, NULL, NULL, NULL, &height);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(height));
}

NAN_METHOD(sdl::TextureWrapper::SetAlphaMod) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected texture.setAlphaMod(Number)")));
	}

	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_SetTextureAlphaMod(tex->texture_, static_cast<uint8_t>(args[0]->Uint32Value()));
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::TextureWrapper::SetBlendMode) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected texture.setBlendMode(Number)")));
	}

	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int err = SDL_SetTextureBlendMode(tex->texture_, static_cast<SDL_BlendMode>(args[0]->Int32Value()));
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::TextureWrapper::SetColorMod) {


	if(args.Length() < 3) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected texture.setColorMod(Number, Number, Number)")));
	}

	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
	int r = args[0]->Int32Value();
	int g = args[1]->Int32Value();
	int b = args[2]->Int32Value();
	int err = SDL_SetTextureColorMod(tex->texture_, r, g, b);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}

// NAN_METHOD(sdl::TextureWrapper::Lock) {
//

// 	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
// 	int err = SDL_LockTexture(tex->texture_);
// 	if(err < 0) {
// 		return ThrowSDLException(__func__);
// 	}

// 	return Undefined();
// }
// NAN_METHOD(sdl::TextureWrapper::Unlock) {
//

// 	TextureWrapper* tex = ObjectWrap::Unwrap<TextureWrapper>(args.This());
// 	int err = SDL_UnlockTexture(tex->texture_);
// 	if(err < 0) {
// 		return ThrowSDLException(__func__);
// 	}

// 	return Undefined();
// }

NAN_METHOD(sdl::TextureWrapper::Update) {


	if(!args[0]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to texture.update must be an Object.")));
	}

	TextureWrapper* texture = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(args.This()));
	if(NULL == texture) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Failed to unwrap this argument to a SurfaceWrapper. (is this not an sdl.Texture?)")));
	}
	SurfaceWrapper* surface = ObjectWrap::Unwrap<SurfaceWrapper>(Handle<Object>::Cast(args[0]));
	if(NULL == surface) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Failed to unwrap first argument to a SurfaceWrapper. (did you not pass in an sdl.Surface?)")));
	}
	RectWrapper* rect = args[1]->IsUndefined() ? NULL : ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(args[1]));
	int err = SDL_UpdateTexture(texture->texture_, rect == NULL ? NULL : rect->wrapped, surface->surface_->pixels, surface->surface_->pitch);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
