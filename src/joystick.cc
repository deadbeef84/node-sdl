#include "joystick.h"
#include "helpers.h"
#include "struct_wrappers.h"


using namespace v8;
using namespace node;


NAN_MODULE_INIT(sdl::joystick::Init) {
	JoystickWrapper::Init(exports);

	Nan::SetPrototypeMethod(exports, "numJoysticks", NumJoysticks);

	Nan::SetPrototypeMethod(exports, "joystickNameForIndex", JoystickNameForIndex);
	Nan::SetPrototypeMethod(exports, "joystickGetDeviceGUID", JoystickGetDeviceGUID);
	Nan::SetPrototypeMethod(exports, "joystickGetGUIDFromString", JoystickGetGUIDFromString);
	Nan::SetPrototypeMethod(exports, "joystickGetGUIDString", JoystickGetGUIDString);

	Nan::SetPrototypeMethod(exports, "joystickUpdate", JoystickUpdate);
	Nan::SetPrototypeMethod(exports, "joystickEventState", JoystickEventState);
}

Persistent<FunctionTemplate> sdl::JoystickWrapper::constructor;

sdl::JoystickWrapper::JoystickWrapper() {
}
sdl::JoystickWrapper::JoystickWrapper(bool owned) {
	owned_ = owned;
}
sdl::JoystickWrapper::~JoystickWrapper() {
	if(NULL != joystick_ && !owned_) {
		SDL_JoystickClose(joystick_);
	}
}

NAN_MODULE_INIT(sdl::JoystickWrapper::Init) {
	Handle<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("JoystickWrapper"));

	Nan::SetPrototypeMethod(tpl, "getAttached", GetAttached);
	Nan::SetPrototypeMethod(tpl, "getAxis", GetAxis);
	Nan::SetPrototypeMethod(tpl, "getBall", GetBall);
	Nan::SetPrototypeMethod(tpl, "getButton", GetButton);
	Nan::SetPrototypeMethod(tpl, "getGUID", GetGUID);
	Nan::SetPrototypeMethod(tpl, "getHat", GetHat);
	Nan::SetPrototypeMethod(tpl, "getName", GetName);
	Nan::SetPrototypeMethod(tpl, "getNumAxes", GetNumAxes);
	Nan::SetPrototypeMethod(tpl, "getNumButtons", GetNumButtons);
	Nan::SetPrototypeMethod(tpl, "getNumBalls", GetNumBalls);
	Nan::SetPrototypeMethod(tpl, "getNumHats", GetNumHats);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Joystick"), constructor);
}
NAN_METHOD(sdl::JoystickWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Must create an sdl.Joystick with the new operator.")));
	}



	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected new sdl.Joystick(Number)")));
	}

	if(args[0]->IsExternal()) {
		JoystickWrapper* wrap;
		if(args.Length() > 1) {
			wrap = new JoystickWrapper(args[1]->BooleanValue());
		}
		else {
			wrap = new JoystickWrapper();
		}
		wrap->joystick_ = static_cast<SDL_Joystick*>(Handle<External>::Cast(args[0])->Value());
		wrap->Wrap(args.This());
	}
	else {
		int index = args[0]->Int32Value();
		SDL_Joystick* joystick = SDL_JoystickOpen(index);
		if(NULL == joystick) {
			return ThrowSDLException(__func__);
		}

		JoystickWrapper* wrap = new JoystickWrapper();
		wrap->joystick_ = joystick;
		wrap->Wrap(args.This());
	}

	return args.This();
}

NAN_METHOD(sdl::JoystickWrapper::GetAttached) {


	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	SDL_bool attached = SDL_JoystickGetAttached(wrap->joystick_);

	info.GetReturnValue().Set(Boolean::New(attached ? true : false));
}
NAN_METHOD(sdl::JoystickWrapper::GetAxis) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetAxis(Number)")));
	}

	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	int axis = args[0]->Int32Value();
	int16_t position = SDL_JoystickGetAxis(wrap->joystick_, axis);
	if(0 == position) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(position));
}
NAN_METHOD(sdl::JoystickWrapper::GetBall) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetBall(Number)")));
	}

	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	int ball = args[0]->Int32Value();
	int dx, dy;
	int err = SDL_JoystickGetBall(wrap->joystick_, ball, &dx, &dy);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> ret = Object::New();
	ret->Set(String::NewSymbol("dx"), Number::New(dx));
	ret->Set(String::NewSymbol("dy"), Number::New(dy));

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::JoystickWrapper::GetButton) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetButton(Number)")));
	}

	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	int button = args[0]->Int32Value();
	uint8_t ret = SDL_JoystickGetButton(wrap->joystick_, button);

	info.GetReturnValue().Set(Boolean::New(ret == 1 ? true : false));
}
NAN_METHOD(sdl::JoystickWrapper::GetGUID) {


	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	SDL_JoystickGUID guid = SDL_JoystickGetGUID(wrap->joystick_);

	// SDL_JoystickGUID is defined as a struct holding a single array of 16 elements.
	Handle<Array> ret = Array::New(16);
	for(int i = 0; i < 16; i++) {
		ret->Set(i, Number::New(guid.data[i]));
	}

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::JoystickWrapper::GetHat) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetHat(Number)")));
	}

	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	int hat = args[0]->Int32Value();
	uint8_t ret = SDL_JoystickGetHat(wrap->joystick_, hat);

	info.GetReturnValue().Set(Number::New(ret));
}

NAN_METHOD(sdl::JoystickWrapper::GetName) {


	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	const char* name = SDL_JoystickName(wrap->joystick_);
	if(NULL == name) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(String::New(name));
}
NAN_METHOD(sdl::JoystickWrapper::GetNumAxes) {


	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	int axes = SDL_JoystickNumAxes(wrap->joystick_);
	if(axes < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(axes));
}
NAN_METHOD(sdl::JoystickWrapper::GetNumButtons) {


	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	int buttons = SDL_JoystickNumButtons(wrap->joystick_);
	if(buttons < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(buttons));
}
NAN_METHOD(sdl::JoystickWrapper::GetNumBalls) {


	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	int balls = SDL_JoystickNumBalls(wrap->joystick_);
	if(balls < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(balls));
}
NAN_METHOD(sdl::JoystickWrapper::GetNumHats) {


	JoystickWrapper* wrap = ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(args.This()));
	int hats = SDL_JoystickNumHats(wrap->joystick_);
	if(hats < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(hats));
}

NAN_METHOD(sdl::NumJoysticks) {


	info.GetReturnValue().Set(Number::New(SDL_NumJoysticks()));
}

NAN_METHOD(sdl::JoystickNameForIndex) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected JoystickNameForIndex(Number)")));
	}

	int index = args[0]->Int32Value();
	const char* name = SDL_JoystickNameForIndex(index);
	if(NULL == name) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(String::New(name));
}

NAN_METHOD(sdl::JoystickGetDeviceGUID) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected JoystickGetDeviceGUID(Number)")));
	}

	int index = args[0]->Int32Value();
	SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(index);

	// SDL_JoystickGUID is defined as a struct holding a single array of 16 elements.
	Handle<Array> ret = Array::New(16);
	for(int i = 0; i < 16; i++) {
		ret->Set(i, Number::New(guid.data[i]));
	}

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::JoystickGetGUIDFromString) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected JoystickGetGUIDFromString(String)")));
	}

	String::Utf8Value pchGuid(args[0]);
	SDL_JoystickGUID guid = SDL_JoystickGetGUIDFromString(*pchGuid);

	// SDL_JoystickGUID is defined as a struct holding a single array of 16 uint8_t elements.
	Handle<Array> ret = Array::New(16);
	for(int i = 0; i < 16; i++) {
		ret->Set(i, Number::New(guid.data[i]));
	}

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::JoystickGetGUIDString) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected JoystickGetGUIDString(String)")));
	}

	Handle<Array> guidArr = Handle<Array>::Cast(args[0]);
	SDL_JoystickGUID guid;
	for(int i = 0; i < 16; i++) {
		guid.data[i] = static_cast<uint8_t>(guidArr->Get(i)->Uint32Value());
	}
	// Hopefully 200 characters is enough to hold the string. Should this be a higher number?
	char pszGuid[200];
	SDL_JoystickGetGUIDString(guid, pszGuid, 200);

	info.GetReturnValue().Set(String::New(pszGuid));
}

NAN_METHOD(sdl::JoystickUpdate) {


	SDL_JoystickUpdate();

	return Undefined();
}

NAN_METHOD(sdl::JoystickEventState) {


	int state;
	if (args.Length() == 0) {
		state = SDL_QUERY;
	} else {
		if (!(args.Length() == 1 && args[0]->IsBoolean())) {
			return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected JoystickEventState([Boolean])")));
		}
		state = args[0]->BooleanValue() ? SDL_ENABLE : SDL_IGNORE;
	}
	return Boolean::New(SDL_JoystickEventState(state));
}
