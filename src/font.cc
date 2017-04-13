#include "font.h"
#include "helpers.h"
#include "container.h"
#include "surface.h"

#include <iostream>

using namespace v8;
using namespace node;


Persistent<FunctionTemplate> sdl::TTF::FontWrapper::constructor;

sdl::TTF::FontWrapper::FontWrapper() {
}
sdl::TTF::FontWrapper::~FontWrapper() {
	if(NULL != font_) {
		TTF_CloseFont(font_);
	}
}

NAN_MODULE_INIT(sdl::TTF::FontWrapper::Init) {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("FontWrapper"));

	Nan::SetPrototypeMethod(tpl, "renderTextSolid", RenderTextSolid);
	Nan::SetPrototypeMethod(tpl, "renderUtf8Solid", RenderUTF8Solid);
	Nan::SetPrototypeMethod(tpl, "renderUnicodeSolid", RenderUnicodeSolid);
	Nan::SetPrototypeMethod(tpl, "renderGlyphSolid", RenderGlyphSolid);

	Nan::SetPrototypeMethod(tpl, "renderTextShaded", RenderTextShaded);
	Nan::SetPrototypeMethod(tpl, "renderUtf8Shaded", RenderUTF8Shaded);
	Nan::SetPrototypeMethod(tpl, "renderUnicodeShaded", RenderUnicodeShaded);
	Nan::SetPrototypeMethod(tpl, "renderGlyphShaded", RenderGlyphShaded);

	Nan::SetPrototypeMethod(tpl, "renderTextBlended", RenderTextBlended);
	Nan::SetPrototypeMethod(tpl, "renderUtf8Blended", RenderUTF8Blended);
	Nan::SetPrototypeMethod(tpl, "renderUnicodeBlended", RenderUnicodeBlended);
	Nan::SetPrototypeMethod(tpl, "renderGlyphBlended", RenderGlyphBlended);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::New("Font"), constructor);
}
NAN_METHOD(sdl::TTF::FontWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("A Font must be created with the new operator.")));
	}



	if(args[0]->IsExternal()) {
		FontWrapper* obj = new FontWrapper();
		obj->font_ = static_cast<TTF_Font*>(Handle<External>::Cast(args[0])->Value());
		obj->Wrap(args.This());
		return args.This();
	}
	else {
		if(!args[0]->IsString()) {
			return ThrowException(Exception::TypeError(
				String::New("Invalid arguments: First argument to new sdl.Font must be a String.")));
		}
		if(!args[1]->IsNumber()) {
			return ThrowException(Exception::TypeError(
				String::New("Invalid arguments: Second argument to new sdl.Font must be a Number.")));
		}

		String::Utf8Value file(args[0]);
		int ptsize = args[1]->Int32Value();
		TTF_Font* font = TTF_OpenFont(*file, ptsize);
		if(NULL == font) {
			return ThrowSDLException(__func__);
		}

		FontWrapper* obj = new FontWrapper();
		obj->font_ = font;
		obj->Wrap(args.This());
		return args.This();
	}
}

NAN_METHOD(sdl::TTF::FontWrapper::RenderTextSolid) {

	Context::Scope context_scope(Context::GetCurrent());

	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderTextSolid must be a String.")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderTextSolid must be an sdl.Color.")));
	}

	String::Utf8Value text(args[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == color) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderTextSolid for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font->font_, *text, *color->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
Handle<Value> sdl::TTF::FontWrapper::RenderUTF8Solid(const Arguments& args) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderUtf8Solid must be a String.")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderUtf8Solid must be an sdl.Color.")));
	}

	String::Utf8Value text(args[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == color) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderUtf8Solid for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderUTF8_Solid(font->font_, *text, *color->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::TTF::FontWrapper::RenderUnicodeSolid) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderUnicodeSolid must be an sdl.Color.")));
	}

	String::Value text(args[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == color) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderUnicodeSolid for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderUNICODE_Solid(font->font_, *text, *color->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::TTF::FontWrapper::RenderGlyphSolid) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderGlyphSolid must be an sdl.Color.")));
	}

	String::Value text(args[0]);
	if(0 == text.length()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderGlyphSolid must be able to convert to a string of at least length 1.")));
	}
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == color) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderGlyphSolid for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderGlyph_Solid(font->font_, (*text)[0], *color->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::TTF::FontWrapper::RenderTextShaded) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderTextShaded must be a String.")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderTextShaded must be an sdl.Color.")));
	}
	if(!args[2]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Third argument to renderTextShaded must be an sdl.Color.")));
	}

	String::Utf8Value text(args[0]);
	ColorWrapper* fg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == fg) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderTextShaded for some reason. (is it not an sdl.Color?)")));
	}
	ColorWrapper* bg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[2]));
	if(NULL == bg) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap third argument to renderTextShaded for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderText_Shaded(font->font_, *text, *fg->color_, *bg->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
Handle<Value> sdl::TTF::FontWrapper::RenderUTF8Shaded(const Arguments& args) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderUtf8Shaded must be a String.")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderUtf8Shaded must be an sdl.Color.")));
	}
	if(!args[2]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Third argument to renderUtf8Shaded must be an sdl.Color.")));
	}

	String::Utf8Value text(args[0]);
	ColorWrapper* fg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == fg) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderUtf8Shaded for some reason. (is it not an sdl.Color?)")));
	}
	ColorWrapper* bg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[2]));
	if(NULL == bg) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap third argument to renderUtf8Shaded for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderUTF8_Shaded(font->font_, *text, *fg->color_, *bg->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::TTF::FontWrapper::RenderUnicodeShaded) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderUnicodeShaded must be a String.")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderUnicodeShaded must be an sdl.Color.")));
	}
	if(!args[2]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Third argument to renderUnicodeShaded must be an sdl.Color.")));
	}

	String::Value text(args[0]);
	ColorWrapper* fg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == fg) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderUnicodeShaded for some reason. (is it not an sdl.Color?)")));
	}
	ColorWrapper* bg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[2]));
	if(NULL == bg) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap third argument to renderUnicodeShaded for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderUNICODE_Shaded(font->font_, *text, *fg->color_, *bg->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::TTF::FontWrapper::RenderGlyphShaded) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderUnicodeShaded must be a String.")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderUnicodeShaded must be an sdl.Color.")));
	}
	if(!args[2]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Third argument to renderUnicodeShaded must be an sdl.Color.")));
	}

	String::Value text(args[0]);
	if(0 == text.length()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderGlyphShaded must be able to convert to a string of at least length 1.")));
	}
	ColorWrapper* fg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == fg) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderUnicodeShaded for some reason. (is it not an sdl.Color?)")));
	}
	ColorWrapper* bg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[2]));
	if(NULL == bg) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap third argument to renderUnicodeShaded for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderGlyph_Shaded(font->font_, (*text)[0], *fg->color_, *bg->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::TTF::FontWrapper::RenderTextBlended) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderTextBlended must be a String.")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderTextBlended must be an sdl.Color.")));
	}

	String::Utf8Value text(args[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == color) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderTextBlended for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderText_Blended(font->font_, *text, *color->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
Handle<Value> sdl::TTF::FontWrapper::RenderUTF8Blended(const Arguments& args) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[0]->IsString()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderUtf8Blended must be a String.")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderUtf8Blended must be an sdl.Color.")));
	}

	String::Utf8Value text(args[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == color) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderUtf8Blended for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderUTF8_Blended(font->font_, *text, *color->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::TTF::FontWrapper::RenderUnicodeBlended) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderUnicodeBlended must be an sdl.Color.")));
	}

	String::Value text(args[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == color) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderUnicodeBlended for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderUNICODE_Blended(font->font_, *text, *color->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::TTF::FontWrapper::RenderGlyphBlended) {


	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(args.This());
	if(NULL == font) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap 'this' for some reason. (did you not use a Font object?)")));
	}
	if(!args[1]->IsObject()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Second argument to renderGlyphBlended must be an sdl.Color.")));
	}

	String::Value text(args[0]);
	if(0 == text.length()) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: First argument to renderGlyphBlended must be able to convert to a string of at least length 1.")));
	}
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(args[1]));
	if(NULL == color) {
		return ThrowException(Exception::TypeError(
			String::New("Could not unwrap second argument to renderGlyphBlended for some reason. (is it not an sdl.Color?)")));
	}

	SDL_Surface* surface = TTF_RenderGlyph_Blended(font->font_, (*text)[0], *color->color_);
	if(NULL == surface) {
		return ThrowSDLException(__func__);
	}

	Handle<Value> arg = External::New(surface);
	Handle<Value> argv[] = {arg};
	Handle<Object> ret = SurfaceWrapper::tpl->GetFunction()->NewInstance(1, argv);
	info.GetReturnValue().Set(ret);
}

void sdl::TTF::Initialize(Handle<Object> exports) {
	Handle<Object> TTF = Object::New();
	exports->Set(String::New("TTF"), TTF);
	Nan::SetPrototypeMethod(TTF, "init", Init);
	Nan::SetPrototypeMethod(TTF, "wasInit", WasInit);
	Nan::SetPrototypeMethod(TTF, "quit", Quit);
	Nan::SetPrototypeMethod(TTF, "getError", GetError);

	FontWrapper::Init(TTF);
}

NAN_METHOD(sdl::TTF::Init) {


	if (!(args.Length() == 0)) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::Init()")));
	}

	if (TTF_Init() < 0) {
		return ThrowException(Exception::Error(String::Concat(
			String::New("TTF::Init: "),
			String::New(TTF_GetError())
			)));
	}

	return Undefined();
}

NAN_METHOD(sdl::TTF::WasInit) {


	info.GetReturnValue().Set(Boolean::New(TTF_WasInit() ? true : false));
}

NAN_METHOD(sdl::TTF::Quit) {


	TTF_Quit();

	return Undefined();
}

// NAN_METHOD(sdl::TTF::SetError) {
//

// 	return Undefined();
// }
NAN_METHOD(sdl::TTF::GetError) {


	const char* error = TTF_GetError();
	// Can this happen?!
	if(NULL == error) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(String::New(error));
}

// NAN_METHOD(sdl::TTF::OpenFont) {
//

// 	if (!(args.Length() == 2 && args[0]->IsString() && args[1]->IsNumber())) {
// 		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::OpenFont(String, Number)")));
// 	}

// 	String::Utf8Value file(args[0]);
// 	int ptsize = (args[1]->Int32Value());

// 	TTF_Font* font = TTF_OpenFont(*file, ptsize);
// 	if (font == NULL) {
// 		return ThrowException(Exception::Error(String::Concat(
// 			String::New("TTF::OpenFont: "),
// 			String::New(TTF_GetError())
// 			)));
// 	}
// 	return Undefined();
// 	// info.GetReturnValue().Set(WrapFont(font));
// }

// TODO: Rewrite for SDL2.
// static NAN_METHOD(sdl::TTF::RenderTextBlended) {
//

//   if (!(args.Length() == 3 && args[0]->IsObject() && args[1]->IsString() && args[2]->IsNumber())) {
//     return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TTF::RenderTextBlended(Font, String, Number)")));
//   }

//   SDL_PixelFormat* vfmt = SDL_GetVideoInfo()->vfmt;
//   TTF_Font* font = UnwrapFont(args[0]->ToObject());
//   String::Utf8Value text(args[1]);
//   int colorCode = args[2]->Int32Value();

//   Uint8 r, g, b;
//   SDL_GetRGB(colorCode, vfmt, &r, &g, &b);

//   SDL_Color color;
//   color.r = r;
//   color.g = g;
//   color.b = b;

//   SDL_Surface *resulting_text;
//   resulting_text = TTF_RenderText_Blended(font, *text, color);
//   if (!resulting_text) {
//     return ThrowException(Exception::Error(String::Concat(
//       String::New("TTF::RenderTextBlended: "),
//       String::New(TTF_GetError())
//     )));
//   }
//   info.GetReturnValue().Set(WrapSurface(resulting_text));
// }
