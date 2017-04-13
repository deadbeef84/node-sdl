#include "container.h"
#include <iostream>
#include <sstream>
#include "SDL.h"
#include "struct_wrappers.h"

using namespace v8;

sdl::RectWrapper::~RectWrapper() {
	if(NULL != wrapped) {
		delete wrapped;
	}
}

START_INIT(sdl, RectWrapper)
  GETTER_SETTER(tpl, "x", GetX, SetX)
  GETTER_SETTER(tpl, "y", GetY, SetY)
  GETTER_SETTER(tpl, "w", GetW, SetW)
  GETTER_SETTER(tpl, "h", GetH, SetH)
END_INIT("Rect")

START_NEW(sdl, RectWrapper, 4)
  if(args[0]->IsExternal()) {
    UNWRAP_EXTERNAL(SDL_Rect, rect, 0);
    RectWrapper* wrap = new RectWrapper();
    wrap->wrapped = rect;
    wrap->Wrap(args.This());
  }
  else {
    EXTRACT_INT32(x, 0);
    EXTRACT_INT32(y, 1);
    EXTRACT_INT32(w, 2);
    EXTRACT_INT32(h, 3);
    SDL_Rect* rect = new SDL_Rect;
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    RectWrapper* wrap = new RectWrapper();
    wrap->wrapped = rect;
    wrap->Wrap(args.This());
  }
END_NEW

GETTER_BEGIN(sdl::RectWrapper, GetX)
	UNWRAP_THIS(RectWrapper, info, wrap)
GETTER_END(Number::New(wrap->wrapped->x))

GETTER_BEGIN(sdl::RectWrapper, GetY)
	UNWRAP_THIS(RectWrapper, info, wrap)
GETTER_END(Number::New(wrap->wrapped->y))

GETTER_BEGIN(sdl::RectWrapper, GetW)
	UNWRAP_THIS(RectWrapper, info, wrap)
GETTER_END(Number::New(wrap->wrapped->w));

GETTER_BEGIN(sdl::RectWrapper, GetH)
	UNWRAP_THIS(RectWrapper, info, wrap)
GETTER_END(Number::New(wrap->wrapped->h))

SETTER_BEGIN(sdl::RectWrapper, SetX)
	UNWRAP_THIS_SETTER(RectWrapper, info, wrap)
		VALUE_INT32(x);
			wrap->wrapped->x = x;
		END_VALUE
	UNWRAP_END
SETTER_END

SETTER_BEGIN(sdl::RectWrapper, SetY)
	UNWRAP_THIS_SETTER(RectWrapper, info, wrap)
		VALUE_INT32(y);
			wrap->wrapped->y = y;
		END_VALUE
	UNWRAP_END
SETTER_END

SETTER_BEGIN(sdl::RectWrapper, SetW)
	UNWRAP_THIS_SETTER(RectWrapper, info, wrap)
		VALUE_INT32(w);
			wrap->wrapped->w = w;
		END_VALUE
	UNWRAP_END
SETTER_END

SETTER_BEGIN(sdl::RectWrapper, SetH)
	UNWRAP_THIS_SETTER(RectWrapper, info, wrap)
		VALUE_INT32(h);
			wrap->wrapped->h = h;
		END_VALUE
	UNWRAP_END
SETTER_END

sdl::ColorWrapper::~ColorWrapper() {
	if(NULL != color_) {
		delete color_;
	}
}

START_INIT(sdl, ColorWrapper)
	GETTER_SETTER(tpl, "r", GetRed, SetRed);
	GETTER_SETTER(tpl, "g", GetGreen, SetGreen);
	GETTER_SETTER(tpl, "b", GetBlue, SetBlue);
	GETTER_SETTER(tpl, "a", GetAlpha, SetAlpha);

  PROTO_METHOD(tpl, getColor, GetColor);
  PROTO_METHOD(tpl, toString, ToString);
END_INIT("Color")

NAN_METHOD(sdl::ColorWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Use the new operator to create instance of a Color.")));
	}

	if(args.Length() < 3) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected new sdl.Color(Number, Number, Number[, Number])")));
	}

	uint8_t r = static_cast<uint8_t>(args[0]->Int32Value());
	uint8_t g = static_cast<uint8_t>(args[1]->Int32Value());
	uint8_t b = static_cast<uint8_t>(args[2]->Int32Value());
	uint8_t a = args[3]->IsUndefined() ? 255 : static_cast<uint8_t>(args[3]->Int32Value());
	SDL_Color* color = new SDL_Color;
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;

	ColorWrapper* obj = new ColorWrapper();
	obj->color_ = color;
	obj->Wrap(args.This());
	return args.This();
}

Handle<Value> sdl::ColorWrapper::GetRed(Local<String> name, const AccessorInfo& info) {
	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(info.This());
	info.GetReturnValue().Set(Number::New(obj->color_->r));
}
Handle<Value> sdl::ColorWrapper::GetGreen(Local<String> name, const AccessorInfo& info) {


	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(info.This());
	info.GetReturnValue().Set(Number::New(obj->color_->g));
}
Handle<Value> sdl::ColorWrapper::GetBlue(Local<String> name, const AccessorInfo& info) {


	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(info.This());
	info.GetReturnValue().Set(Number::New(obj->color_->b));
}
Handle<Value> sdl::ColorWrapper::GetAlpha(Local<String> name, const AccessorInfo& info) {


	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(info.This());
	info.GetReturnValue().Set(Number::New(obj->color_->a));
}
NAN_METHOD(sdl::ColorWrapper::GetColor) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid argument: Expected GetColor(PixelFormat)")));
	}

	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(args.This());
	SDL_PixelFormat* format = UnwrapPixelFormat(Handle<Object>::Cast(args[0]));
	SDL_Color* c = obj->color_;
	uint32_t color = SDL_MapRGBA(format, c->r, c->g, c->b, c->a);
	info.GetReturnValue().Set(Number::New(color));
}

void sdl::ColorWrapper::SetRed(Local<String> name, Local<Value> value, const AccessorInfo& info) {


	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(info.This());
	uint8_t r = static_cast<uint8_t>(value->Int32Value());
	obj->color_->r = r;
}
void sdl::ColorWrapper::SetGreen(Local<String> name, Local<Value> value, const AccessorInfo& info) {


	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(info.This());
	uint8_t g = static_cast<uint8_t>(value->Int32Value());
	obj->color_->g = g;
}
void sdl::ColorWrapper::SetBlue(Local<String> name, Local<Value> value, const AccessorInfo& info) {


	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(info.This());
	uint8_t b = static_cast<uint8_t>(value->Int32Value());
	obj->color_->b = b;
}
void sdl::ColorWrapper::SetAlpha(Local<String> name, Local<Value> value, const AccessorInfo& info) {


	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(info.This());
	uint8_t a = static_cast<uint8_t>(value->Int32Value());
	obj->color_->a = a;
}

NAN_METHOD(sdl::ColorWrapper::ToString) {


	ColorWrapper* obj = ObjectWrap::Unwrap<ColorWrapper>(args.This());
	SDL_Color* c = obj->color_;
	std::stringstream ss;
	ss << "{r:" << (int)c->r << ", g:" << (int)c->g << ", b:" << (int)c->b << ", a:" << (int)c->a << "}";
	info.GetReturnValue().Set(String::New(ss.str().c_str()));
}

////////////////////////////////////////////////////////////////////////////////
// FingerWrapper Class Definition.
v8::Persistent<v8::FunctionTemplate> sdl::FingerWrapper::tpl;

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
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("FingerWrapper"));

	Local<ObjectTemplate> templ = tpl->PrototypeTemplate();
	templ->SetAccessor(String::NewSymbol("fingerID"), GetFingerID);
	templ->SetAccessor(String::NewSymbol("x"), GetX);
	templ->SetAccessor(String::NewSymbol("y"), GetY);
	templ->SetAccessor(String::NewSymbol("pressure"), GetPressure);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Finger"), constructor);
}
NAN_METHOD(sdl::FingerWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Can only construct a FingerWrapper with the new operator.")));
	}



	if(args.Length() < 4) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected new sdl.Finger(Number, Number, Number, Number)")));
	}

	SDL_FingerID id = static_cast<SDL_FingerID>(args[0]->IntegerValue());
	float x = static_cast<float>(args[1]->NumberValue());
	float y = static_cast<float>(args[2]->NumberValue());
	float pressure = static_cast<float>(args[3]->NumberValue());

	SDL_Finger* finger = new SDL_Finger;
	finger->id = id;
	finger->x = x;
	finger->y = y;
	finger->pressure = pressure;

	FingerWrapper* obj = new FingerWrapper();
	obj->finger_ = finger;
	obj->Wrap(args.This());

	return args.This();
}

Handle<Value> sdl::FingerWrapper::GetFingerID(Local<String> name, const AccessorInfo& info) {


	FingerWrapper* obj = ObjectWrap::Unwrap<FingerWrapper>(info.This());

	info.GetReturnValue().Set(Number::New(obj->finger_->id));
}
Handle<Value> sdl::FingerWrapper::GetX(Local<String> name, const AccessorInfo& info) {


	FingerWrapper* obj = ObjectWrap::Unwrap<FingerWrapper>(info.This());

	info.GetReturnValue().Set(Number::New(obj->finger_->x));
}
Handle<Value> sdl::FingerWrapper::GetY(Local<String> name, const AccessorInfo& info) {


	FingerWrapper* obj = ObjectWrap::Unwrap<FingerWrapper>(info.This());

	info.GetReturnValue().Set(Number::New(obj->finger_->y));
}
Handle<Value> sdl::FingerWrapper::GetPressure(Local<String> name, const AccessorInfo& info) {


	FingerWrapper* obj = ObjectWrap::Unwrap<FingerWrapper>(info.This());

	info.GetReturnValue().Set(Number::New(obj->finger_->pressure));
}
