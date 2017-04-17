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
	Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(STRING_NEW("FontWrapper"));

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

	constructor.Reset(tpl);
	exports->Set(Nan::New("Font").ToLocalChecked(), constructor);
}

NAN_METHOD(sdl::TTF::FontWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("A Font must be created with the new operator.").ToLocalChecked());
		return;
	}

	if(info[0]->IsExternal()) {
		FontWrapper* obj = new FontWrapper();
		obj->font_ = static_cast<TTF_Font*>(Handle<External>::Cast(info[0])->Value());
		obj->Wrap(info.This());
		return info.This();
	}
	else {
		if(!info[0]->IsString()) {
			Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to new sdl.Font must be a String.").ToLocalChecked());
		return;
		}
		if(!info[1]->IsNumber()) {
			Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to new sdl.Font must be a Number.").ToLocalChecked());
		return;
		}

		String::Utf8Value file(info[0]);
		int ptsize = info[1]->Int32Value();
		TTF_Font* font = TTF_OpenFont(*file, ptsize);
		if(NULL == font) {
			return ThrowSDLException(__func__);
		}

		FontWrapper* obj = new FontWrapper();
		obj->font_ = font;
		obj->Wrap(info.This());
		return info.This();
	}
}

NAN_METHOD(sdl::TTF::FontWrapper::RenderTextSolid) {

	Context::Scope context_scope(Context::GetCurrent());

	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[0]->IsString()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderTextSolid must be a String.").ToLocalChecked());
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderTextSolid must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Utf8Value text(info[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == color) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderTextSolid for some reason. (is it not an sdl.Color?)"));
		return;
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

NAN_METHOD(sdl::TTF::FontWrapper::RenderUTF8Solid) {
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[0]->IsString()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderUtf8Solid must be a String.").ToLocalChecked());
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderUtf8Solid must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Utf8Value text(info[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == color) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderUtf8Solid for some reason. (is it not an sdl.Color?)"));
		return;
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
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderUnicodeSolid must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Value text(info[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == color) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderUnicodeSolid for some reason. (is it not an sdl.Color?)"));
		return;
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
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderGlyphSolid must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Value text(info[0]);
	if(0 == text.length()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderGlyphSolid must be able to convert to a string of at least length 1.").ToLocalChecked());
		return;
	}
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == color) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderGlyphSolid for some reason. (is it not an sdl.Color?)"));
		return;
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
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[0]->IsString()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderTextShaded must be a String.").ToLocalChecked());
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderTextShaded must be an sdl.Color.").ToLocalChecked());
		return;
	}
	if(!info[2]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Third argument to renderTextShaded must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Utf8Value text(info[0]);
	ColorWrapper* fg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == fg) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderTextShaded for some reason. (is it not an sdl.Color?)"));
		return;
	}
	ColorWrapper* bg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[2]));
	if(NULL == bg) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap third argument to renderTextShaded for some reason. (is it not an sdl.Color?)"));
		return;
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

NAN_METHOD(sdl::TTF::FontWrapper::RenderUTF8Shaded) {
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[0]->IsString()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderUtf8Shaded must be a String.").ToLocalChecked());
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderUtf8Shaded must be an sdl.Color.").ToLocalChecked());
		return;
	}
	if(!info[2]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Third argument to renderUtf8Shaded must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Utf8Value text(info[0]);
	ColorWrapper* fg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == fg) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderUtf8Shaded for some reason. (is it not an sdl.Color?)"));
		return;
	}
	ColorWrapper* bg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[2]));
	if(NULL == bg) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap third argument to renderUtf8Shaded for some reason. (is it not an sdl.Color?)"));
		return;
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
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[0]->IsString()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderUnicodeShaded must be a String.").ToLocalChecked());
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderUnicodeShaded must be an sdl.Color.").ToLocalChecked());
		return;
	}
	if(!info[2]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Third argument to renderUnicodeShaded must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Value text(info[0]);
	ColorWrapper* fg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == fg) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderUnicodeShaded for some reason. (is it not an sdl.Color?)"));
		return;
	}
	ColorWrapper* bg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[2]));
	if(NULL == bg) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap third argument to renderUnicodeShaded for some reason. (is it not an sdl.Color?)"));
		return;
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
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[0]->IsString()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderUnicodeShaded must be a String.").ToLocalChecked());
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderUnicodeShaded must be an sdl.Color.").ToLocalChecked());
		return;
	}
	if(!info[2]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Third argument to renderUnicodeShaded must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Value text(info[0]);
	if(0 == text.length()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderGlyphShaded must be able to convert to a string of at least length 1.").ToLocalChecked());
		return;
	}
	ColorWrapper* fg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == fg) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderUnicodeShaded for some reason. (is it not an sdl.Color?)"));
		return;
	}
	ColorWrapper* bg = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[2]));
	if(NULL == bg) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap third argument to renderUnicodeShaded for some reason. (is it not an sdl.Color?)"));
		return;
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
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[0]->IsString()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderTextBlended must be a String.").ToLocalChecked());
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderTextBlended must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Utf8Value text(info[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == color) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderTextBlended for some reason. (is it not an sdl.Color?)"));
		return;
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

NAN_METHOD(sdl::TTF::FontWrapper::RenderUTF8Blended) {
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[0]->IsString()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderUtf8Blended must be a String.").ToLocalChecked());
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderUtf8Blended must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Utf8Value text(info[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == color) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderUtf8Blended for some reason. (is it not an sdl.Color?)"));
		return;
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
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderUnicodeBlended must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Value text(info[0]);
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == color) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderUnicodeBlended for some reason. (is it not an sdl.Color?)"));
		return;
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
	FontWrapper* font = ObjectWrap::Unwrap<FontWrapper>(info.This());
	if(NULL == font) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap 'this' for some reason. (did you not use a Font object?)"));
		return;
	}
	if(!info[1]->IsObject()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: Second argument to renderGlyphBlended must be an sdl.Color.").ToLocalChecked());
		return;
	}

	String::Value text(info[0]);
	if(0 == text.length()) {
		Nan::ThrowTypeError(Nan::New("Invalid arguments: First argument to renderGlyphBlended must be able to convert to a string of at least length 1.").ToLocalChecked());
		return;
	}
	ColorWrapper* color = ObjectWrap::Unwrap<ColorWrapper>(Handle<Object>::Cast(info[1]));
	if(NULL == color) {
		Nan::ThrowTypeError(STRING_NEW("Could not unwrap second argument to renderGlyphBlended for some reason. (is it not an sdl.Color?)"));
		return;
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
	Handle<Object> TTF = Nan::New<Object>();
	exports->Set(Nan::New("TTF").ToLocalChecked(), TTF);
	Nan::SetPrototypeMethod(TTF, "init", Init);
	Nan::SetPrototypeMethod(TTF, "wasInit", WasInit);
	Nan::SetPrototypeMethod(TTF, "quit", Quit);
	Nan::SetPrototypeMethod(TTF, "getError", GetError);

	FontWrapper::Init(TTF);
}

NAN_METHOD(sdl::TTF::Init) {
	if (!(info.Length() == 0)) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected TTF::Init()"));
		return;
	}

	if (TTF_Init() < 0) {
		Nan::ThrowException(Exception::Error(String::Concat(
			Nan::New("TTF::Init: ").ToLocalChecked(),
			STRING_NEW(TTF_GetError())
			)));
		return;
	}
}

NAN_METHOD(sdl::TTF::WasInit) {
	info.GetReturnValue().Set(Nan::New<Boolean>(TTF_WasInit() ? true : false));
}

NAN_METHOD(sdl::TTF::Quit) {
	TTF_Quit();
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

	info.GetReturnValue().Set(Nan::New(error).ToLocalChecked());
}

// NAN_METHOD(sdl::TTF::OpenFont) {
//

// 	if (!(info.Length() == 2 && info[0]->IsString() && info[1]->IsNumber())) {
// 		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected TTF::OpenFont(String, Number)"));
		return;
// 	}

// 	String::Utf8Value file(info[0]);
// 	int ptsize = (info[1]->Int32Value());

// 	TTF_Font* font = TTF_OpenFont(*file, ptsize);
// 	if (font == NULL) {
// 		return ThrowException(Exception::Error(String::Concat(
// 			Nan::New("TTF::OpenFont: ").ToLocalChecked(),
// 			STRING_NEW(TTF_GetError())
// 			)));
// 	}
// 	return Undefined();
// 	// info.GetReturnValue().Set(WrapFont(font));
// }

// TODO: Rewrite for SDL2.
// static NAN_METHOD(sdl::TTF::RenderTextBlended) {
//

//   if (!(info.Length() == 3 && info[0]->IsObject() && info[1]->IsString() && info[2]->IsNumber())) {
//     Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected TTF::RenderTextBlended(Font, String, Number)"));
		return;
//   }

//   SDL_PixelFormat* vfmt = SDL_GetVideoInfo()->vfmt;
//   TTF_Font* font = UnwrapFont(info[0]->ToObject());
//   String::Utf8Value text(info[1]);
//   int colorCode = info[2]->Int32Value();

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
//       Nan::New("TTF::RenderTextBlended: ").ToLocalChecked(),
//       STRING_NEW(TTF_GetError())
//     )));
//   }
//   info.GetReturnValue().Set(WrapSurface(resulting_text));
// }
