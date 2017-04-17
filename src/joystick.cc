#include "joystick.h"
#include "helpers.h"
#include "struct_wrappers.h"


using namespace v8;
using namespace node;


NAN_MODULE_INIT(sdl::joystick::Init) {
	JoystickWrapper::Init(target);

	Nan::Export(target, "numJoysticks", NumJoysticks);

	Nan::Export(target, "joystickNameForIndex", JoystickNameForIndex);
	Nan::Export(target, "joystickGetDeviceGUID", JoystickGetDeviceGUID);
	Nan::Export(target, "joystickGetGUIDFromString", JoystickGetGUIDFromString);
	Nan::Export(target, "joystickGetGUIDString", JoystickGetGUIDString);

	Nan::Export(target, "joystickUpdate", JoystickUpdate);
	Nan::Export(target, "joystickEventState", JoystickEventState);
}

Nan::Persistent<FunctionTemplate> sdl::JoystickWrapper::constructor;

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
	Handle<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(STRING_NEW("JoystickWrapper"));

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

	constructor.Reset(tpl);
	Nan::Set(target, STRING_NEW("Joystick"), tpl->GetFunction());
}

NAN_METHOD(sdl::JoystickWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("Must create an sdl.Joystick with the new operator.").ToLocalChecked());
		return;
	}

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected new sdl.Joystick(Number)"));
		return;
	}

	if(info[0]->IsExternal()) {
		JoystickWrapper* wrap;
		if(info.Length() > 1) {
			wrap = new JoystickWrapper(info[1]->BooleanValue());
		}
		else {
			wrap = new JoystickWrapper();
		}
		wrap->joystick_ = static_cast<SDL_Joystick*>(Handle<External>::Cast(info[0])->Value());
		wrap->Wrap(info.This());
	}
	else {
		int index = info[0]->Int32Value();
		SDL_Joystick* joystick = SDL_JoystickOpen(index);
		if(NULL == joystick) {
			return ThrowSDLException(__func__);
		}

		JoystickWrapper* wrap = new JoystickWrapper();
		wrap->joystick_ = joystick;
		wrap->Wrap(info.This());
	}

	info.GetReturnValue().Set(info.This());
}

NAN_METHOD(sdl::JoystickWrapper::GetAttached) {
	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	SDL_bool attached = SDL_JoystickGetAttached(wrap->joystick_);

	info.GetReturnValue().Set(Nan::New<Boolean>(attached ? true : false));
}

NAN_METHOD(sdl::JoystickWrapper::GetAxis) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetAxis(Number)"));
		return;
	}

	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	int axis = info[0]->Int32Value();
	int16_t position = SDL_JoystickGetAxis(wrap->joystick_, axis);
	if(0 == position) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(position));
}

NAN_METHOD(sdl::JoystickWrapper::GetBall) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetBall(Number)"));
		return;
	}

	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	int ball = info[0]->Int32Value();
	int dx, dy;
	int err = SDL_JoystickGetBall(wrap->joystick_, ball, &dx, &dy);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> ret = Nan::New<Object>();
	ret->Set(STRING_NEW("dx"), Nan::New<Number>(dx));
	ret->Set(STRING_NEW("dy"), Nan::New<Number>(dy));

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::JoystickWrapper::GetButton) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetButton(Number)"));
		return;
	}

	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	int button = info[0]->Int32Value();
	uint8_t ret = SDL_JoystickGetButton(wrap->joystick_, button);

	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1 ? true : false));
}

NAN_METHOD(sdl::JoystickWrapper::GetGUID) {
	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	SDL_JoystickGUID guid = SDL_JoystickGetGUID(wrap->joystick_);

	// SDL_JoystickGUID is defined as a struct holding a single array of 16 elements.
	Handle<Array> ret = Nan::New<Array>(16);
	for(int i = 0; i < 16; i++) {
		ret->Set(i, Nan::New<Number>(guid.data[i]));
	}

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::JoystickWrapper::GetHat) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetHat(Number)"));
		return;
	}

	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	int hat = info[0]->Int32Value();
	uint8_t ret = SDL_JoystickGetHat(wrap->joystick_, hat);

	info.GetReturnValue().Set(Nan::New<Number>(ret));
}

NAN_METHOD(sdl::JoystickWrapper::GetName) {
	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	const char* name = SDL_JoystickName(wrap->joystick_);
	if(NULL == name) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New(name).ToLocalChecked());
}

NAN_METHOD(sdl::JoystickWrapper::GetNumAxes) {
	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	int axes = SDL_JoystickNumAxes(wrap->joystick_);
	if(axes < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(axes));
}

NAN_METHOD(sdl::JoystickWrapper::GetNumButtons) {
	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	int buttons = SDL_JoystickNumButtons(wrap->joystick_);
	if(buttons < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(buttons));
}

NAN_METHOD(sdl::JoystickWrapper::GetNumBalls) {
	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	int balls = SDL_JoystickNumBalls(wrap->joystick_);
	if(balls < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(balls));
}

NAN_METHOD(sdl::JoystickWrapper::GetNumHats) {
	JoystickWrapper* wrap = Nan::ObjectWrap::Unwrap<JoystickWrapper>(Handle<Object>::Cast(info.This()));
	int hats = SDL_JoystickNumHats(wrap->joystick_);
	if(hats < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(hats));
}

NAN_METHOD(sdl::NumJoysticks) {
	info.GetReturnValue().Set(Nan::New<Number>(SDL_NumJoysticks()));
}

NAN_METHOD(sdl::JoystickNameForIndex) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected JoystickNameForIndex(Number)"));
		return;
	}

	int index = info[0]->Int32Value();
	const char* name = SDL_JoystickNameForIndex(index);
	if(NULL == name) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New(name).ToLocalChecked());
}

NAN_METHOD(sdl::JoystickGetDeviceGUID) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected JoystickGetDeviceGUID(Number)"));
		return;
	}

	int index = info[0]->Int32Value();
	SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(index);

	// SDL_JoystickGUID is defined as a struct holding a single array of 16 elements.
	Handle<Array> ret = Nan::New<Array>(16);
	for(int i = 0; i < 16; i++) {
		ret->Set(i, Nan::New<Number>(guid.data[i]));
	}

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::JoystickGetGUIDFromString) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected JoystickGetGUIDFromString(String)"));
		return;
	}

	String::Utf8Value pchGuid(info[0]);
	SDL_JoystickGUID guid = SDL_JoystickGetGUIDFromString(*pchGuid);

	// SDL_JoystickGUID is defined as a struct holding a single array of 16 uint8_t elements.
	Handle<Array> ret = Nan::New<Array>(16);
	for(int i = 0; i < 16; i++) {
		ret->Set(i, Nan::New<Number>(guid.data[i]));
	}

	info.GetReturnValue().Set(ret);
}

NAN_METHOD(sdl::JoystickGetGUIDString) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected JoystickGetGUIDString(String)"));
		return;
	}

	Handle<Array> guidArr = Handle<Array>::Cast(info[0]);
	SDL_JoystickGUID guid;
	for(int i = 0; i < 16; i++) {
		guid.data[i] = static_cast<uint8_t>(guidArr->Get(i)->Uint32Value());
	}
	// Hopefully 200 characters is enough to hold the string. Should this be a higher number?
	char pszGuid[200];
	SDL_JoystickGetGUIDString(guid, pszGuid, 200);

	info.GetReturnValue().Set(Nan::New(pszGuid).ToLocalChecked());
}

NAN_METHOD(sdl::JoystickUpdate) {
	SDL_JoystickUpdate();
}

NAN_METHOD(sdl::JoystickEventState) {
	int state;
	if (info.Length() == 0) {
		state = SDL_QUERY;
	} else {
		if (!(info.Length() == 1 && info[0]->IsBoolean())) {
			Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected JoystickEventState([Boolean])"));
		return;
		}
		state = info[0]->BooleanValue() ? SDL_ENABLE : SDL_IGNORE;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(SDL_JoystickEventState(state)));
}
