#include "struct_wrappers.h"
#include "helpers.h"
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <sstream>

using namespace v8;

namespace sdl {
	typedef Handle<ObjectTemplate> (*TemplateMaker)();

	static Nan::Persistent<ObjectTemplate> color_template_;
	static Nan::Persistent<ObjectTemplate> palette_template_;
	static Nan::Persistent<ObjectTemplate> pixelformat_template_;
	static Nan::Persistent<ObjectTemplate> rendererinfo_template_;
	static Nan::Persistent<ObjectTemplate> displaymode_template_;
	static Nan::Persistent<ObjectTemplate> joystick_template_;
	static Nan::Persistent<ObjectTemplate> font_template_;

	///////////////////////////////////////////////////////////////////////////////
	// Initialize everything we need to use the wrappers.
	void InitWrappers(Handle<Object> exports) {
		// Color
		Local<ObjectTemplate> color_template = ObjectTemplate::New();
		color_template->SetInternalFieldCount(1);
		Nan::SetAccessor(color_template, STRING_NEW("r"), GetColorRed, SetColorRed);
		Nan::SetAccessor(color_template, STRING_NEW("g"), GetColorGreen, SetColorGreen);
		Nan::SetAccessor(color_template, STRING_NEW("b"), GetColorBlue, SetColorBlue);
		Nan::SetAccessor(color_template, STRING_NEW("a"), GetColorAlpha, SetColorAlpha);
		color_template_.Reset(color_template);

		// Palette
		Local<ObjectTemplate> palette_template = ObjectTemplate::New();
		palette_template->SetInternalFieldCount(1);
		Nan::SetAccessor(palette_template, STRING_NEW("ncolors"), GetNcolors);
		Nan::SetAccessor(palette_template, STRING_NEW("colors"), GetColors);
		palette_template_.Reset(palette_template);

		// DisplayMode
		Local<ObjectTemplate> displaymode_template = ObjectTemplate::New();
		displaymode_template->SetInternalFieldCount(1);
		Nan::SetAccessor(displaymode_template, STRING_NEW("format"), GetDisplayModeFormat);
		Nan::SetAccessor(displaymode_template, STRING_NEW("w"), GetDisplayModeWidth);
		Nan::SetAccessor(displaymode_template, STRING_NEW("h"), GetDisplayModeHeight);
		Nan::SetAccessor(displaymode_template, STRING_NEW("refreshRate"), GetDisplayModeRefreshRate);
		displaymode_template_.Reset(displaymode_template);

		// PixelFormat
		Local<ObjectTemplate> pixelformat_template = ObjectTemplate::New();
		pixelformat_template->SetInternalFieldCount(1);
		Nan::SetAccessor(pixelformat_template, STRING_NEW("format"), GetFormatFormat);
		Nan::SetAccessor(pixelformat_template, STRING_NEW("palette"), GetFormatPalette);
		Nan::SetAccessor(pixelformat_template, STRING_NEW("bitsPerPixel"), GetFormatBits);
		Nan::SetAccessor(pixelformat_template, STRING_NEW("bytesPerPixel"), GetFormatBytes);
		Nan::SetAccessor(pixelformat_template, STRING_NEW("rmask"), GetFormatRmask);
		Nan::SetAccessor(pixelformat_template, STRING_NEW("gmask"), GetFormatGmask);
		Nan::SetAccessor(pixelformat_template, STRING_NEW("bmask"), GetFormatBmask);
		Nan::SetAccessor(pixelformat_template, STRING_NEW("amask"), GetFormatAmask);
		pixelformat_template_.Reset(pixelformat_template);

		// RendererInfo
		Local<ObjectTemplate> rendererinfo_template = ObjectTemplate::New();
		rendererinfo_template->SetInternalFieldCount(1);
		Nan::SetAccessor(rendererinfo_template, STRING_NEW("name"), GetRendererInfoName);
		Nan::SetAccessor(rendererinfo_template, STRING_NEW("flags"), GetRendererInfoFlags);
		Nan::SetAccessor(rendererinfo_template, STRING_NEW("numTextureFormats"), GetRendererInfoNumTextureFormats);
		Nan::SetAccessor(rendererinfo_template, STRING_NEW("textureFormats"), GetRendererInfoTextureFormats);
		Nan::SetAccessor(rendererinfo_template, STRING_NEW("maxTextureWidth"), GetRendererInfoMaxTextureWidth);
		Nan::SetAccessor(rendererinfo_template, STRING_NEW("maxTextureHeight"), GetRendererInfoMaxTextureHeight);
		rendererinfo_template_.Reset(rendererinfo_template);

		Nan::Export(exports, "Color", ConstructColor);
		Nan::Export(exports, "Palette", ConstructPalette);

		// TODO: Joystick and Font.
	}

	///////////////////////////////////////////////////////////////////////////////
	// SDL_Color Wrapper/Unwrapper.
	NAN_METHOD(ConstructColor) {
		if(info.Length() < 1) {
			Nan::ThrowTypeError(STRING_NEW("Invalid call. Excpected: ConstructRect(x, y, width, height)"));
			return;
		}

		SDL_Color *color = new SDL_Color;
		color->r = info[0]->Int32Value();
		color->g = info[1]->Int32Value();
		color->b = info[2]->Int32Value();
		color->a = info[3]->Int32Value();

		info.GetReturnValue().Set(WrapColor(color));
	}

	Handle<Object> WrapColor(SDL_Color* color) {
		Nan::EscapableHandleScope scope;
		Local<ObjectTemplate> templ = Nan::New<ObjectTemplate>(color_template_);
		Local<Object> result = templ->NewInstance();
		Local<External> class_ptr = Nan::New<External>(color);
		result->SetInternalField(0, class_ptr);
		return scope.Escape(result);
	}

	SDL_Color* UnwrapColor(Handle<Object> obj) {
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<SDL_Color*>(ptr);
	}

	// Property getters.
	NAN_GETTER(GetColorRed) {
		SDL_Color* color = UnwrapColor(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(color->r));
	}

	NAN_GETTER(GetColorGreen) {
		SDL_Color* color = UnwrapColor(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(color->g));
	}

	NAN_GETTER(GetColorBlue) {
		SDL_Color* color = UnwrapColor(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(color->b));
	}

	NAN_GETTER(GetColorAlpha) {
		SDL_Color* color = UnwrapColor(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(color->a));
	}

	// Property setters.
	NAN_SETTER(SetColorRed) {
		if(!value->IsUndefined()) {
			SDL_Color* color = UnwrapColor(info.Holder());
			color->r = value->Int32Value();
		}
	}

	NAN_SETTER(SetColorGreen) {
		if(!value->IsUndefined()) {
			SDL_Color* color = UnwrapColor(info.Holder());
			color->g = value->Int32Value();
		}
	}

	NAN_SETTER(SetColorBlue) {
		if(!value->IsUndefined()) {
			SDL_Color* color = UnwrapColor(info.Holder());
			color->b = value->Int32Value();
		}
	}

	NAN_SETTER(SetColorAlpha) {
		if(!value->IsUndefined()) {
			SDL_Color* color = UnwrapColor(info.Holder());
			color->a = value->Int32Value();
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// SDL_Palette Wrapper/Unwrapper.
	NAN_METHOD(ConstructPalette) {
		if(info.Length() < 1) {
			Nan::ThrowTypeError(STRING_NEW("Invalid call. Excpected: ConstructPalette(Array)"));
			return;
		}

		Handle<Array> colors = Handle<Array>::Cast(info[0]);
		int length = colors->Length();
		SDL_Palette* palette = new SDL_Palette;
		palette->ncolors = length;
		palette->colors = new SDL_Color[length];
		for(int i = 0; i < length; i++) {
			Handle<Object> element = colors->CloneElementAt(i);
			SDL_Color* color = UnwrapColor(element);
			palette->colors[i] = *color;
		}

		info.GetReturnValue().Set(WrapPalette(palette));
	}

	Handle<Object> WrapPalette(SDL_Palette* palette) {
  		Nan::EscapableHandleScope scope;
		Local<ObjectTemplate> templ = Nan::New<ObjectTemplate>(palette_template_);
		Local<Object> result = templ->NewInstance();
		Local<External> class_ptr = Nan::New<External>(palette);
		result->SetInternalField(0, class_ptr);
		return scope.Escape(result);
	}

	SDL_Palette* UnwrapPalette(Handle<Object> obj) {
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<SDL_Palette*>(ptr);
	}

	// Property getters.
	NAN_GETTER(GetNcolors) {
		SDL_Palette* palette = UnwrapPalette(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(palette->ncolors));
	}

	NAN_GETTER(GetColors) {
		SDL_Palette* palette = UnwrapPalette(info.Holder());
		Handle<Array> ret = Nan::New<Array>(palette->ncolors);
		for(int i = 0; i < palette->ncolors; i++) {
			ret->Set(i, WrapColor(palette->colors + i));
		}
		info.GetReturnValue().Set(ret);
	}
	// Property setters.

	///////////////////////////////////////////////////////////////////////////////
	// SDL_DisplayMode Wrapper/Unwrapper.
	Handle<Object> WrapDisplayMode(SDL_DisplayMode* mode) {
		Nan::EscapableHandleScope scope;
		Local<ObjectTemplate> templ = Nan::New<ObjectTemplate>(displaymode_template_);
		Local<Object> result = templ->NewInstance();
		Local<External> class_ptr = Nan::New<External>(mode);
		result->SetInternalField(0, class_ptr);
		return scope.Escape(result);
	}

	SDL_DisplayMode* UnwrapDisplayMode(Handle<Value> val) {
		Handle<Object> obj = Handle<Object>::Cast(val);
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<SDL_DisplayMode*>(ptr);
	}

	NAN_GETTER(GetDisplayModeFormat) {
		SDL_DisplayMode* mode = UnwrapDisplayMode(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(mode->format));
	}

	NAN_GETTER(GetDisplayModeWidth) {
		SDL_DisplayMode* mode = UnwrapDisplayMode(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(mode->w));
	}

	NAN_GETTER(GetDisplayModeHeight) {
		SDL_DisplayMode* mode = UnwrapDisplayMode(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(mode->h));
	}

	NAN_GETTER(GetDisplayModeRefreshRate) {
		SDL_DisplayMode* mode = UnwrapDisplayMode(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(mode->refresh_rate));
	}


	///////////////////////////////////////////////////////////////////////////////
	// SDL_PixelFormat Wrapper/Unwrapper.
	Handle<Object> WrapPixelFormat(SDL_PixelFormat* pixelformat) {
  	Nan::EscapableHandleScope scope;
		Local<ObjectTemplate> templ = Nan::New<ObjectTemplate>(pixelformat_template_);
		Local<Object> result = templ->NewInstance();
		Local<External> class_ptr = Nan::New<External>(pixelformat);
		result->SetInternalField(0, class_ptr);
		return scope.Escape(result);
	}

	SDL_PixelFormat* UnwrapPixelFormat(Handle<Object> obj) {
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<SDL_PixelFormat*>(ptr);
	}

	// Property getters.
	NAN_GETTER(GetFormatFormat) {
		SDL_PixelFormat* format = UnwrapPixelFormat(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(format->format));
	}

	NAN_GETTER(GetFormatPalette) {
		SDL_PixelFormat* format = UnwrapPixelFormat(info.Holder());
		info.GetReturnValue().Set(WrapPalette(format->palette));
	}

	NAN_GETTER(GetFormatBits) {
		SDL_PixelFormat* format = UnwrapPixelFormat(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(format->BitsPerPixel));
	}

	NAN_GETTER(GetFormatBytes) {
		SDL_PixelFormat* format = UnwrapPixelFormat(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(format->BytesPerPixel));
	}

	NAN_GETTER(GetFormatRmask) {
		SDL_PixelFormat* format = UnwrapPixelFormat(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(format->Rmask));
	}

	NAN_GETTER(GetFormatGmask) {
		SDL_PixelFormat* format = UnwrapPixelFormat(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(format->Gmask));
	}

	NAN_GETTER(GetFormatBmask) {
		SDL_PixelFormat* format = UnwrapPixelFormat(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(format->Bmask));
	}

	NAN_GETTER(GetFormatAmask) {
		SDL_PixelFormat* format = UnwrapPixelFormat(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(format->Amask));
	}

	///////////////////////////////////////////////////////////////////////////////
	// SDL_RendererInfo Wrapper/Unwrapper.
	Handle<Object> WrapRendererInfo(SDL_RendererInfo* info) {
  	Nan::EscapableHandleScope scope;
		Local<ObjectTemplate> templ = Nan::New<ObjectTemplate>(rendererinfo_template_);
		Local<Object> result = templ->NewInstance();
		Local<External> class_ptr = Nan::New<External>(info);
		result->SetInternalField(0, class_ptr);
		return scope.Escape(result);
	}

	SDL_RendererInfo* UnwrapRendererInfo(Handle<Object> obj) {
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<SDL_RendererInfo*>(ptr);
	}

	// Property getters.
	NAN_GETTER(GetRendererInfoName) {
		SDL_RendererInfo* rinfo = UnwrapRendererInfo(info.Holder());
		info.GetReturnValue().Set(Nan::New(rinfo->name).ToLocalChecked());
	}

	NAN_GETTER(GetRendererInfoFlags) {
		SDL_RendererInfo* rinfo = UnwrapRendererInfo(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(rinfo->flags));
	}

	NAN_GETTER(GetRendererInfoNumTextureFormats) {
		SDL_RendererInfo* rinfo = UnwrapRendererInfo(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(rinfo->num_texture_formats));
	}

	NAN_GETTER(GetRendererInfoTextureFormats) {
		SDL_RendererInfo* rinfo = UnwrapRendererInfo(info.Holder());
		Handle<Array> ret = Nan::New<Array>(rinfo->num_texture_formats);
		for(unsigned int i = 0; i < rinfo->num_texture_formats; i++) {
			ret->Set(i, Nan::New<Number>(rinfo->texture_formats[i]));
		}
		info.GetReturnValue().Set(ret);
	}

	NAN_GETTER(GetRendererInfoMaxTextureWidth) {
		SDL_RendererInfo* rinfo = UnwrapRendererInfo(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(rinfo->max_texture_width));
	}

	NAN_GETTER(GetRendererInfoMaxTextureHeight) {
		SDL_RendererInfo* rinfo = UnwrapRendererInfo(info.Holder());
		info.GetReturnValue().Set(Nan::New<Number>(rinfo->max_texture_height));
	}

	///////////////////////////////////////////////////////////////////////////////
	// SDL_Joystick Wrapper/Unwrapper.
	Handle<Object> WrapJoystick(SDL_Joystick* joystick) {
  	Nan::EscapableHandleScope scope;
		Local<ObjectTemplate> templ = Nan::New<ObjectTemplate>(joystick_template_);
		Local<Object> result = templ->NewInstance();
		Local<External> class_ptr = Nan::New<External>(joystick);
		result->SetInternalField(0, class_ptr);
		return scope.Escape(result);
	}

	SDL_Joystick* UnwrapJoystick(Handle<Object> obj) {
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<SDL_Joystick*>(ptr);
	}

	///////////////////////////////////////////////////////////////////////////////
	// TTF_Font Wrapper/Unwrapper.
	Handle<Object> WrapFont(TTF_Font* font) {
  	Nan::EscapableHandleScope scope;
		Local<ObjectTemplate> templ = Nan::New<ObjectTemplate>(font_template_);
		Local<Object> result = templ->NewInstance();
		Local<External> class_ptr = Nan::New<External>(font);
		result->SetInternalField(0, class_ptr);
		return scope.Escape(result);
	}

	TTF_Font* UnwrapFont(Handle<Object> obj) {
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<TTF_Font*>(ptr);
	}
}