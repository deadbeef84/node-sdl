#include "container.h"
#include <iostream>
#include <sstream>
#include "SDL.h"
#include "struct_wrappers.h"

using namespace v8;

Nan::Persistent<v8::FunctionTemplate> sdl::RectWrapper::constructor;

sdl::RectWrapper::~RectWrapper() {
	if(NULL != rect_) {
		delete rect_;
	}
}

NAN_MODULE_INIT(sdl::RectWrapper::Init) {
	Handle<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(STRING_NEW("RectWrapper"));

	Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
	Nan::SetAccessor(proto, STRING_NEW("x"), GetX, SetX);
  Nan::SetAccessor(proto, STRING_NEW("y"), GetY, SetY);
  Nan::SetAccessor(proto, STRING_NEW("h"), GetH, SetH);
  Nan::SetAccessor(proto, STRING_NEW("w"), GetW, SetW);

	constructor.Reset(tpl);
	Nan::Set(target, STRING_NEW("Rect"), tpl->GetFunction());
}

NAN_METHOD(sdl::RectWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(STRING_NEW("Use the new operator to create instance of a Rect."));
		return;
	}

	if(info.Length() < 4) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected new sdl.Rect(Number, Number, Number, Number)"));
		return;
	}

	uint32_t x = static_cast<uint32_t>(info[0]->Int32Value());
	uint32_t y = static_cast<uint32_t>(info[1]->Int32Value());
	uint32_t w = static_cast<uint32_t>(info[2]->Int32Value());
	uint32_t h = static_cast<uint32_t>(info[3]->Int32Value());
	SDL_Rect* rect = new SDL_Rect;
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;

	RectWrapper* obj = new RectWrapper();
	obj->rect_ = rect;
	obj->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

NAN_GETTER(sdl::RectWrapper::GetX) {
	RectWrapper* obj = Nan::ObjectWrap::Unwrap<RectWrapper>(info.This());
	info.GetReturnValue().Set(Nan::New<Number>(obj->rect_->x));
}
NAN_GETTER(sdl::RectWrapper::GetY) {
	RectWrapper* obj = Nan::ObjectWrap::Unwrap<RectWrapper>(info.This());
	info.GetReturnValue().Set(Nan::New<Number>(obj->rect_->y));
}
NAN_GETTER(sdl::RectWrapper::GetW) {
	RectWrapper* obj = Nan::ObjectWrap::Unwrap<RectWrapper>(info.This());
	info.GetReturnValue().Set(Nan::New<Number>(obj->rect_->w));
}
NAN_GETTER(sdl::RectWrapper::GetH) {
	RectWrapper* obj = Nan::ObjectWrap::Unwrap<RectWrapper>(info.This());
	info.GetReturnValue().Set(Nan::New<Number>(obj->rect_->h));
}

NAN_SETTER(sdl::RectWrapper::SetX) {
	RectWrapper* obj = Nan::ObjectWrap::Unwrap<RectWrapper>(info.This());
	obj->rect_->x = value->Int32Value();
}
NAN_SETTER(sdl::RectWrapper::SetY) {
	RectWrapper* obj = Nan::ObjectWrap::Unwrap<RectWrapper>(info.This());
	obj->rect_->y = value->Int32Value();
}
NAN_SETTER(sdl::RectWrapper::SetW) {
	RectWrapper* obj = Nan::ObjectWrap::Unwrap<RectWrapper>(info.This());
	obj->rect_->w = value->Int32Value();
}
NAN_SETTER(sdl::RectWrapper::SetH) {
	RectWrapper* obj = Nan::ObjectWrap::Unwrap<RectWrapper>(info.This());
	obj->rect_->h = value->Int32Value();
}

Nan::Persistent<v8::FunctionTemplate> sdl::ColorWrapper::constructor;

sdl::ColorWrapper::~ColorWrapper() {
	if(NULL != color_) {
		delete color_;
	}
}

NAN_MODULE_INIT(sdl::ColorWrapper::Init) {
	Handle<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(STRING_NEW("ColorWrapper"));

	Nan::SetPrototypeMethod(tpl, "getColor", GetColor);
	Nan::SetPrototypeMethod(tpl, "toString", ToString);

	Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
	Nan::SetAccessor(proto, STRING_NEW("r"), GetRed, SetRed);
  Nan::SetAccessor(proto, STRING_NEW("g"), GetGreen, SetGreen);
  Nan::SetAccessor(proto, STRING_NEW("b"), GetBlue, SetBlue);
  Nan::SetAccessor(proto, STRING_NEW("a"), GetAlpha, SetAlpha);

	constructor.Reset(tpl);
	Nan::Set(target, STRING_NEW("Color"), tpl->GetFunction());
}

NAN_METHOD(sdl::ColorWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(STRING_NEW("Use the new operator to create instance of a Color."));
		return;
	}

	if(info.Length() < 3) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected new sdl.Color(Number, Number, Number[, Number])"));
		return;
	}

	uint8_t r = static_cast<uint8_t>(info[0]->Int32Value());
	uint8_t g = static_cast<uint8_t>(info[1]->Int32Value());
	uint8_t b = static_cast<uint8_t>(info[2]->Int32Value());
	uint8_t a = info[3]->IsUndefined() ? 255 : static_cast<uint8_t>(info[3]->Int32Value());
	SDL_Color* color = new SDL_Color;
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;

	ColorWrapper* obj = new ColorWrapper();
	obj->color_ = color;
	obj->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}

NAN_GETTER(sdl::ColorWrapper::GetRed) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	info.GetReturnValue().Set(Nan::New<Number>(obj->color_->r));
}

NAN_GETTER(sdl::ColorWrapper::GetGreen) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	info.GetReturnValue().Set(Nan::New<Number>(obj->color_->g));
}

NAN_GETTER(sdl::ColorWrapper::GetBlue) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	info.GetReturnValue().Set(Nan::New<Number>(obj->color_->b));
}

NAN_GETTER(sdl::ColorWrapper::GetAlpha) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	info.GetReturnValue().Set(Nan::New<Number>(obj->color_->a));
}

NAN_METHOD(sdl::ColorWrapper::GetColor) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid argument: Expected GetColor(PixelFormat)"));
		return;
	}

	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	SDL_PixelFormat* format = UnwrapPixelFormat(Handle<Object>::Cast(info[0]));
	SDL_Color* c = obj->color_;
	uint32_t color = SDL_MapRGBA(format, c->r, c->g, c->b, c->a);
	info.GetReturnValue().Set(Nan::New<Number>(color));
}

NAN_SETTER(sdl::ColorWrapper::SetRed) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	uint8_t r = static_cast<uint8_t>(value->Int32Value());
	obj->color_->r = r;
}

NAN_SETTER(sdl::ColorWrapper::SetGreen) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	uint8_t g = static_cast<uint8_t>(value->Int32Value());
	obj->color_->g = g;
}

NAN_SETTER(sdl::ColorWrapper::SetBlue) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	uint8_t b = static_cast<uint8_t>(value->Int32Value());
	obj->color_->b = b;
}

NAN_SETTER(sdl::ColorWrapper::SetAlpha) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	uint8_t a = static_cast<uint8_t>(value->Int32Value());
	obj->color_->a = a;
}

NAN_METHOD(sdl::ColorWrapper::ToString) {
	ColorWrapper* obj = Nan::ObjectWrap::Unwrap<ColorWrapper>(info.This());
	SDL_Color* c = obj->color_;
	std::stringstream ss;
	ss << "{r:" << (int)c->r << ", g:" << (int)c->g << ", b:" << (int)c->b << ", a:" << (int)c->a << "}";
	info.GetReturnValue().Set(STRING_NEW(ss.str()));
}

////////////////////////////////////////////////////////////////////////////////
// FingerWrapper Class Definition.
Nan::Persistent<v8::FunctionTemplate> sdl::FingerWrapper::constructor;

sdl::FingerWrapper::FingerWrapper() {
}
sdl::FingerWrapper::FingerWrapper(Handle<Object> toWrap) {
	Wrap(toWrap);
}
sdl::FingerWrapper::~FingerWrapper() {
	std::cout << "FingerWrapper destructor running." << std::endl;
	if(NULL != finger_) {
		delete finger_;
	}
}

NAN_MODULE_INIT(sdl::FingerWrapper::Init) {
	Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(STRING_NEW("FingerWrapper"));

	Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
	Nan::SetAccessor(proto, STRING_NEW("fingerID"), GetFingerID);
	Nan::SetAccessor(proto, STRING_NEW("x"), GetX);
	Nan::SetAccessor(proto, STRING_NEW("y"), GetY);
	Nan::SetAccessor(proto, STRING_NEW("pressure"), GetPressure);

	constructor.Reset(tpl);
	Nan::Set(target, STRING_NEW("Finger"), tpl->GetFunction());
}

NAN_METHOD(sdl::FingerWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(STRING_NEW("Can only construct a FingerWrapper with the new operator."));
		return;
	}

	if(info.Length() < 4) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected new sdl.Finger(Number, Number, Number, Number)"));
		return;
	}

	SDL_FingerID id = static_cast<SDL_FingerID>(info[0]->IntegerValue());
	float x = static_cast<float>(info[1]->NumberValue());
	float y = static_cast<float>(info[2]->NumberValue());
	float pressure = static_cast<float>(info[3]->NumberValue());

	SDL_Finger* finger = new SDL_Finger;
	finger->id = id;
	finger->x = x;
	finger->y = y;
	finger->pressure = pressure;

	FingerWrapper* obj = new FingerWrapper();
	obj->finger_ = finger;
	obj->Wrap(info.This());

	info.GetReturnValue().Set(info.This());
}

NAN_GETTER(sdl::FingerWrapper::GetFingerID) {
	FingerWrapper* obj = Nan::ObjectWrap::Unwrap<FingerWrapper>(info.This());

	info.GetReturnValue().Set(Nan::New<Number>(obj->finger_->id));
}

NAN_GETTER(sdl::FingerWrapper::GetX) {
	FingerWrapper* obj = Nan::ObjectWrap::Unwrap<FingerWrapper>(info.This());

	info.GetReturnValue().Set(Nan::New<Number>(obj->finger_->x));
}

NAN_GETTER(sdl::FingerWrapper::GetY) {
	FingerWrapper* obj = Nan::ObjectWrap::Unwrap<FingerWrapper>(info.This());

	info.GetReturnValue().Set(Nan::New<Number>(obj->finger_->y));
}

NAN_GETTER(sdl::FingerWrapper::GetPressure) {
	FingerWrapper* obj = Nan::ObjectWrap::Unwrap<FingerWrapper>(info.This());

	info.GetReturnValue().Set(Nan::New<Number>(obj->finger_->pressure));
}
