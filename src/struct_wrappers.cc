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

	static Persistent<ObjectTemplate> wrappedtemplate_;
	static Persistent<ObjectTemplate> point_template_;
	static Persistent<ObjectTemplate> color_template_;
	static Persistent<ObjectTemplate> palette_template_;
	static Persistent<ObjectTemplate> pixelformat_template_;
	static Persistent<ObjectTemplate> rendererinfo_template_;
	static Persistent<ObjectTemplate> displaymode_template_;
	static Persistent<ObjectTemplate> joystick_template_;
	static Persistent<ObjectTemplate> font_template_;

	///////////////////////////////////////////////////////////////////////////////
	// Initialize everything we need to use the wrappers.
	void InitWrappers(Handle<Object> exports) {
		// std::cout << "About to initialize SDL struct wrappers." << std::endl;

		// std::cout << "Created scope for struct wrapper initialization." << std::endl;

		// std::cout << "Putting together information for color wrapper..." << std::endl;
		const int numColor = 4;
		std::string colorSymbols[] = {"r", "g", "b", "a"};
		AccessorGetter colorGetters[] = {GetColorRed, GetColorGreen, GetColorBlue, GetColorAlpha};
		AccessorSetter colorSetters[] = {SetColorRed, SetColorGreen, SetColorBlue, SetColorAlpha};

		// std::cout << "Putting together information for palette wrapper..." << std::endl;
		const int numberPalette = 2;
		std::string paletteSymbols[] = {"ncolors", "colors"};
		AccessorGetter paletteGetters[] = {GetNcolors, GetColors};
		AccessorSetter paletteSetters[] = {0, 0};

		// std::cout << "Putting together information for display mode wrapper..." << std::endl;
		const int numberDisplayMode = 4;
		std::string displayModeSymbols[] = {"format", "w", "h", "refreshRate"};
		AccessorGetter displayModeGetters[] = {GetDisplayModeFormat, GetDisplayModeWidth,
											   GetDisplayModeHeight, GetDisplayModeRefreshRate};
		AccessorSetter displayModeSetters[] = {0, 0, 0, 0};

		// std::cout << "Putting together information for pixel format wrapper..." << std::endl;
		const int numberPixelFormat = 8;
		std::string pixelFormatSymbols[] = {"format", "palette", "bitsPerPixel", "bytesPerPixel",
											"rmask", "gmask", "bmask", "amask"};
		AccessorGetter pixelFormatGetters[] = {GetFormatFormat, GetFormatPalette, GetFormatBits,
											   GetFormatBytes, GetFormatRmask, GetFormatGmask,
											   GetFormatBmask, GetFormatAmask};
		AccessorSetter pixelFormatSetters[] = {0, 0, 0, 0, 0, 0, 0, 0};

		const int numberRendererInfo = 6;
		std::string rendererInfoSymbols[] = {"name", "flags", "numTextureFormats", "textureFormats",
											 "maxTextureWidth", "maxTextureHeight"};
		AccessorGetter rendererInfoGetters[] = {GetRendererInfoName, GetRendererInfoFlags,
												GetRendererInfoNumTextureFormats,
												GetRendererInfoTextureFormats,
												GetRendererInfoMaxTextureWidth,
												GetRendererInfoMaxTextureHeight};
		AccessorSetter rendererInfoSetters[] = {0, 0, 0, 0, 0, 0};

		// std::cout << "Putting together meta information for creating wrapping bindings..." << std::endl;
		const int numberTemplates = 5;
		Handle<ObjectTemplate> *templates[] = {&color_template_,
											   &palette_template_, &displaymode_template_,
											   &pixelformat_template_, &rendererinfo_template_};
		int numberSymbols[] = {numColor, numberPalette, numberDisplayMode,
							   numberPixelFormat, numberRendererInfo};
		std::string *allSymbols[] = {colorSymbols, paletteSymbols,
									 displayModeSymbols, pixelFormatSymbols, rendererInfoSymbols};
		AccessorGetter *allGetters[] = {colorGetters, paletteGetters,
										displayModeGetters, pixelFormatGetters, rendererInfoGetters};
		AccessorSetter *allSetters[] = {colorSetters, paletteSetters,
										displayModeSetters, pixelFormatSetters, rendererInfoSetters};
		InvocationCallback allConstructors[] = {ConstructColor,
											    ConstructPalette, 0, 0, 0};
		std::string constructorNames[] = {"Color", "Palette",
										  "DisplayMode", "PixelFormat", "RendererInfo"};

		// std::cout << std::endl << "About to begin loop to create wrapping bindings..." << std::endl;
		for(int i = 0; i < numberTemplates; i++) {
			// std::cout << "Creating new ObjectTemplate." << std::endl;
			Handle<ObjectTemplate> raw_template = ObjectTemplate::New();
			// std::cout << "Setting internal field count for ObjectTemplate to 1." << std::endl;
			raw_template->SetInternalFieldCount(1);

			const int symbols = numberSymbols[i];
			// std::cout << "There are " << symbols << " symbols to create." << std::endl;
			std::string *symbolNames = allSymbols[i];
			AccessorGetter *getters = allGetters[i];
			AccessorSetter *setters = allSetters[i];
			for(int j = 0; j < symbols; j++) {
				// std::cout << "Creating symbol: " << symbolNames[j] << std::endl;
				// std::cout << "This symbol " << (setters[j] != 0 ? "has" : "does not have") << " a setter." << std::endl;
				raw_template->SetAccessor(STRING_NEW(symbolNames[j].c_str()), getters[j], setters[j] == 0 ? 0 : setters[j]);
			}

			// std::cout << "Directly setting the ObjectTemplate with the template that has the accessors." << std::endl;
			*(templates[i]) = Persistent<ObjectTemplate>::New(raw_template);

			if(allConstructors[i] != 0) {
				// std::cout << "Creating constructor with name: " << constructorNames[i] << "." << std::endl;
				Nan::SetPrototypeMethod(exports, constructorNames[i].c_str(), allConstructors[i]);
			}
			// std::cout << std::endl;
		}

		PointWrapper::Init(exports);
		// std::cout << "Finished initializing wrappers." << std::endl;
		// TODO: Joystick and Font.
	}

	///////////////////////////////////////////////////////////////////////////////
	// SDL_Point Wrapper/Unwrapper.
    Persistent<FunctionTemplate> sdl::PointWrapper::constructor;

	sdl::PointWrapper::PointWrapper() {
	}
	sdl::PointWrapper::~PointWrapper() {
		if(NULL != point_) {
			delete point_;
		}
	}

	NAN_MODULE_INIT(sdl::PointWrapper::Init) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
		tpl->InstanceTemplate()->SetInternalFieldCount(1);
		tpl->SetClassName(STRING_NEW("PointWrapper"));

		Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
		proto->SetAccessor(STRING_NEW("x"), GetX, SetX);
		proto->SetAccessor(STRING_NEW("y"), GetY, SetY);
		Nan::SetPrototypeMethod(tpl, "toString", ToString);

		constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
		exports->Set(STRING_NEW("Point"), constructor);
	}

	NAN_METHOD(sdl::PointWrapper::New) {
		if(!info.IsConstructCall()) {
			Nan::ThrowTypeError(Nan::New("Use the new operator to create instances of a Point.").ToLocalChecked());
			return;
		}

		int x = info[0]->IsUndefined() ? 0 : info[0]->Int32Value();
		int y = info[0]->IsUndefined() ? 0 : info[1]->Int32Value();
		PointWrapper* obj = new PointWrapper();
		obj->point_ = new SDL_Point;
		obj->point_->x = x;
		obj->point_->y = y;
		obj->Wrap(info.This());
		return info.This();
	}

	NAN_GETTER(GetX) {
		PointWrapper* obj = ObjectWrap::Unwrap<PointWrapper>(info.This());
		info.GetReturnValue().Set(Nan::New<Number>(obj->point_->x));
	}

	NAN_GETTER(GetY) {
		PointWrapper* obj = ObjectWrap::Unwrap<PointWrapper>(info.This());
		info.GetReturnValue().Set(Nan::New<Number>(obj->point_->y));
	}

	NAN_SETTER(SetX) {
		PointWrapper* obj = ObjectWrap::Unwrap<PointWrapper>(info.This());
		int x = value->Int32Value();
		obj->point_->x = x;
	}

	NAN_SETTER(SetY) {
		PointWrapper* obj = ObjectWrap::Unwrap<PointWrapper>(info.This());
		int y = value->Int32Value();
		obj->point_->y = y;
	}

	NAN_METHOD(sdl::PointWrapper::ToString) {
		// PointWrapper* obj = ObjectWrap::Unwrap<PointWrapper>(info.This());
		int x = info.This()->Get(Nan::New("x").ToLocalChecked())->Int32Value();
		int y = info.This()->Get(Nan::New("y").ToLocalChecked())->Int32Value();
		std::stringstream ss;
		ss << "{x: " << x << ", y:" << y << "}";
		info.GetReturnValue().Set(STRING_NEW(ss.str().c_str()));
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
  		// Handle scope for temporary handles.
		HandleScope handle_scope;

		Handle<ObjectTemplate> templ = color_template_;

  		// Create an empty http request wrapper.
		Handle<Object> result = templ->NewInstance();

  		// Wrap the raw C++ pointer in an External so it can be referenced
  		// from within JavaScript.
		Handle<External> request_ptr = External::New(color);

  		// Store the request pointer in the JavaScript wrapper.
		result->SetInternalField(0, request_ptr);

  		// Return the result through the current handle scope.  Since each
  		// of these handles will go away when the handle scope is deleted
  		// we need to call Close to let one, the result, escape into the
  		// outer handle scope.
		return handle_scope.Close(result);
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
  		// Handle scope for temporary handles.
		HandleScope handle_scope;

		Handle<ObjectTemplate> templ = palette_template_;

  		// Create an empty http request wrapper.
		Handle<Object> result = templ->NewInstance();

  		// Wrap the raw C++ pointer in an External so it can be referenced
  		// from within JavaScript.
		Handle<External> request_ptr = External::New(palette);

  		// Store the request pointer in the JavaScript wrapper.
		result->SetInternalField(0, request_ptr);

  		// Return the result through the current handle scope.  Since each
  		// of these handles will go away when the handle scope is deleted
  		// we need to call Close to let one, the result, escape into the
  		// outer handle scope.
		return handle_scope.Close(result);
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
		Handle<Array> ret = Array::New(palette->ncolors);
		for(int i = 0; i < palette->ncolors; i++) {
			ret->Set(i, WrapColor(palette->colors + i));
		}
		return ret;
	}
	// Property setters.

	///////////////////////////////////////////////////////////////////////////////
	// SDL_DisplayMode Wrapper/Unwrapper.
	Handle<ObjectTemplate> MakeDisplayModeTemplate() {
		Handle<ObjectTemplate> result = ObjectTemplate::New();
		result->SetInternalFieldCount(1);

		result->SetAccessor(STRING_NEW("format"), GetDisplayModeFormat);
		result->SetAccessor(STRING_NEW("w"), GetDisplayModeWidth);
		result->SetAccessor(STRING_NEW("h"), GetDisplayModeHeight);
		result->SetAccessor(STRING_NEW("refreshRate"), GetDisplayModeRefreshRate);

		info.GetReturnValue().Set(result);
	}

	Handle<Object> WrapDisplayMode(SDL_DisplayMode* mode) {
		Handle<ObjectTemplate> templ = displaymode_template_;
		Handle<Object> result = templ->NewInstance();
		Handle<External> request_ptr = External::New(mode);
		result->SetInternalField(0, request_ptr);
		info.GetReturnValue().Set(result);
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
  		// Handle scope for temporary handles.
		HandleScope handle_scope;

		Handle<ObjectTemplate> templ = pixelformat_template_;

  		// Create an empty http request wrapper.
		Handle<Object> result = templ->NewInstance();

  		// Wrap the raw C++ pointer in an External so it can be referenced
  		// from within JavaScript.
		Handle<External> request_ptr = External::New(pixelformat);

  		// Store the request pointer in the JavaScript wrapper.
		result->SetInternalField(0, request_ptr);

  		// Return the result through the current handle scope.  Since each
  		// of these handles will go away when the handle scope is deleted
  		// we need to call Close to let one, the result, escape into the
  		// outer handle scope.
		return handle_scope.Close(result);
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
		return WrapPalette(format->palette);
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
  		// Handle scope for temporary handles.
		HandleScope handle_scope;

		Handle<ObjectTemplate> templ = rendererinfo_template_;

  		// Create an empty http request wrapper.
		Handle<Object> result = templ->NewInstance();

  		// Wrap the raw C++ pointer in an External so it can be referenced
  		// from within JavaScript.
		Handle<External> request_ptr = External::New(info);

  		// Store the request pointer in the JavaScript wrapper.
		result->SetInternalField(0, request_ptr);

  		// Return the result through the current handle scope.  Since each
  		// of these handles will go away when the handle scope is deleted
  		// we need to call Close to let one, the result, escape into the
  		// outer handle scope.
		return handle_scope.Close(result);
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
		Handle<Array> ret = Array::New(rinfo->num_texture_formats);
		for(unsigned int i = 0; i < rinfo->num_texture_formats; i++) {
			ret->Set(i, Nan::New<Number>(rinfo->texture_formats[i]));
		}
		return ret;
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
  		// Handle scope for temporary handles.
		HandleScope handle_scope;

  		// Fetch the template for creating JavaScript http request wrappers.
  		// It only has to be created once, which we do on demand.
		Handle<ObjectTemplate> templ = joystick_template_;

  		// Create an empty http request wrapper.
		Handle<Object> result = templ->NewInstance();

  		// Wrap the raw C++ pointer in an External so it can be referenced
  		// from within JavaScript.
		Handle<External> request_ptr = External::New(joystick);

  		// Store the request pointer in the JavaScript wrapper.
		result->SetInternalField(0, request_ptr);

  		// Return the result through the current handle scope.  Since each
  		// of these handles will go away when the handle scope is deleted
  		// we need to call Close to let one, the result, escape into the
  		// outer handle scope.
		return handle_scope.Close(result);
	}

	SDL_Joystick* UnwrapJoystick(Handle<Object> obj) {
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<SDL_Joystick*>(ptr);
	}

	///////////////////////////////////////////////////////////////////////////////
	// TTF_Font Wrapper/Unwrapper.
	Handle<Object> WrapFont(TTF_Font* font) {
  		// Handle scope for temporary handles.
		HandleScope handle_scope;

  		// Fetch the template for creating JavaScript http request wrappers.
  		// It only has to be created once, which we do on demand.
		Handle<ObjectTemplate> templ = font_template_;

  		// Create an empty http request wrapper.
		Handle<Object> result = templ->NewInstance();

  		// Wrap the raw C++ pointer in an External so it can be referenced
  		// from within JavaScript.
		Handle<External> request_ptr = External::New(font);

  		// Store the request pointer in the JavaScript wrapper.
		result->SetInternalField(0, request_ptr);

  		// Return the result through the current handle scope.  Since each
  		// of these handles will go away when the handle scope is deleted
  		// we need to call Close to let one, the result, escape into the
  		// outer handle scope.
		return handle_scope.Close(result);
	}

	TTF_Font* UnwrapFont(Handle<Object> obj) {
		Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
		void* ptr = field->Value();
		return static_cast<TTF_Font*>(ptr);
	}
}