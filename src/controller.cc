#include "controller.h"
#include "joystick.h"
#include "helpers.h"

using namespace v8;
using namespace node;


static Handle<Object> ControllerButtonBindToObject(SDL_GameControllerButtonBind bind) {
	Handle<Object> ret = Object::New();
	ret->Set(String::NewSymbol("type"), Number::New(bind.bindType));
	switch(bind.bindType) {
	case SDL_CONTROLLER_BINDTYPE_NONE:
		// Nothing to do here. Just wanted to shut the compiler up :)
		break;
	case SDL_CONTROLLER_BINDTYPE_BUTTON:
		ret->Set(String::NewSymbol("button"), Number::New(bind.value.button));
		break;
	case SDL_CONTROLLER_BINDTYPE_AXIS:
		ret->Set(String::NewSymbol("axis"), Number::New(bind.value.axis));
		break;
	case SDL_CONTROLLER_BINDTYPE_HAT:
		Handle<Object> hat = Object::New();
		hat->Set(String::NewSymbol("hat"), Number::New(bind.value.hat.hat));
		hat->Set(String::NewSymbol("hatMask"), Number::New(bind.value.hat.hat_mask));
		ret->Set(String::NewSymbol("hat"), hat);
		break;
	}
	return ret;
}

NAN_MODULE_INIT(sdl::controller::Init) {
	GameControllerWrapper::Init(exports);

	Nan::SetPrototypeMethod(exports, "addMapping", AddMapping);
	Nan::SetPrototypeMethod(exports, "addMappingsFromFile", AddMappingsFromFile);

	Nan::SetPrototypeMethod(exports, "mappingForGuid", MappingForGUID);
	Nan::SetPrototypeMethod(exports, "nameForIndex", NameForIndex);

	Nan::SetPrototypeMethod(exports, "eventState", EventState);
	Nan::SetPrototypeMethod(exports, "getAxisFromString", GetAxisFromString);
	Nan::SetPrototypeMethod(exports, "getButtonFromString", GetButtonFromString);

	Handle<Object> BINDTYPE = Object::New();
	exports->Set(String::NewSymbol("BINDTYPE"), BINDTYPE);
	BINDTYPE->Set(String::NewSymbol("NONE"), Number::New(SDL_CONTROLLER_BINDTYPE_NONE));
	BINDTYPE->Set(String::NewSymbol("BUTTON"), Number::New(SDL_CONTROLLER_BINDTYPE_BUTTON));
	BINDTYPE->Set(String::NewSymbol("AXIS"), Number::New(SDL_CONTROLLER_BINDTYPE_AXIS));
	BINDTYPE->Set(String::NewSymbol("HAT"), Number::New(SDL_CONTROLLER_BINDTYPE_HAT));

	Handle<Object> AXIS = Object::New();
	exports->Set(String::NewSymbol("AXIS"), AXIS);
	AXIS->Set(String::NewSymbol("INVALID"), Number::New(SDL_CONTROLLER_AXIS_INVALID));
	AXIS->Set(String::NewSymbol("LEFTX"), Number::New(SDL_CONTROLLER_AXIS_LEFTX));
	AXIS->Set(String::NewSymbol("LEFTY"), Number::New(SDL_CONTROLLER_AXIS_LEFTY));
	AXIS->Set(String::NewSymbol("RIGHTX"), Number::New(SDL_CONTROLLER_AXIS_RIGHTX));
	AXIS->Set(String::NewSymbol("RIGHTY"), Number::New(SDL_CONTROLLER_AXIS_RIGHTY));
	AXIS->Set(String::NewSymbol("TRIGGERLEFT"), Number::New(SDL_CONTROLLER_AXIS_TRIGGERLEFT));
	AXIS->Set(String::NewSymbol("TRIGGERRIGHT"), Number::New(SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
	AXIS->Set(String::NewSymbol("MAX"), Number::New(SDL_CONTROLLER_AXIS_MAX));

	Handle<Object> BUTTON = Object::New();
	exports->Set(String::NewSymbol("BUTTON"), BUTTON);
	BUTTON->Set(String::NewSymbol("INVALID"), Number::New(SDL_CONTROLLER_BUTTON_INVALID));
	BUTTON->Set(String::NewSymbol("A"), Number::New(SDL_CONTROLLER_BUTTON_A));
	BUTTON->Set(String::NewSymbol("B"), Number::New(SDL_CONTROLLER_BUTTON_B));
	BUTTON->Set(String::NewSymbol("X"), Number::New(SDL_CONTROLLER_BUTTON_X));
	BUTTON->Set(String::NewSymbol("Y"), Number::New(SDL_CONTROLLER_BUTTON_Y));
	BUTTON->Set(String::NewSymbol("BACK"), Number::New(SDL_CONTROLLER_BUTTON_BACK));
	BUTTON->Set(String::NewSymbol("GUIDE"), Number::New(SDL_CONTROLLER_BUTTON_GUIDE));
	BUTTON->Set(String::NewSymbol("START"), Number::New(SDL_CONTROLLER_BUTTON_START));
	BUTTON->Set(String::NewSymbol("LEFTSTICK"), Number::New(SDL_CONTROLLER_BUTTON_LEFTSTICK));
	BUTTON->Set(String::NewSymbol("RIGHTSTICK"), Number::New(SDL_CONTROLLER_BUTTON_RIGHTSTICK));
	BUTTON->Set(String::NewSymbol("LEFTSHOULDER"), Number::New(SDL_CONTROLLER_BUTTON_LEFTSHOULDER));
	BUTTON->Set(String::NewSymbol("RIGHTSHOULDER"), Number::New(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER));
	BUTTON->Set(String::NewSymbol("DPAD_UP"), Number::New(SDL_CONTROLLER_BUTTON_DPAD_UP));
	BUTTON->Set(String::NewSymbol("DPAD_DOWN"), Number::New(SDL_CONTROLLER_BUTTON_DPAD_DOWN));
	BUTTON->Set(String::NewSymbol("DPAD_LEFT"), Number::New(SDL_CONTROLLER_BUTTON_DPAD_LEFT));
	BUTTON->Set(String::NewSymbol("DPAD_RIGHT"), Number::New(SDL_CONTROLLER_BUTTON_DPAD_RIGHT));
	BUTTON->Set(String::NewSymbol("MAX"), Number::New(SDL_CONTROLLER_BUTTON_MAX));
}

Persistent<FunctionTemplate> sdl::controller::GameControllerWrapper::constructor;

sdl::controller::GameControllerWrapper::GameControllerWrapper() {
}
sdl::controller::GameControllerWrapper::~GameControllerWrapper() {
	if(NULL != controller_) {
		SDL_GameControllerClose(controller_);
	}
}

NAN_MODULE_INIT(sdl::controller::GameControllerWrapper::Init) {
	Handle<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("GameControllerWrapper"));

	Nan::SetPrototypeMethod(tpl, "getAttached", GetAttached);
	Nan::SetPrototypeMethod(tpl, "getAxis", GetAxis);
	Nan::SetPrototypeMethod(tpl, "getBindForAxis", GetBindForAxis);
	Nan::SetPrototypeMethod(tpl, "getBindForButton", GetBindForButton);
	Nan::SetPrototypeMethod(tpl, "getButton", GetButton);
	Nan::SetPrototypeMethod(tpl, "getJoystick", GetJoystick);
	Nan::SetPrototypeMethod(tpl, "getStringForAxis", GetStringForAxis);
	Nan::SetPrototypeMethod(tpl, "getStringForButton", GetStringForButton);
	Nan::SetPrototypeMethod(tpl, "getMapping", GetMapping);
	Nan::SetPrototypeMethod(tpl, "getName", GetName);

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("GameController"), constructor);
}

NAN_METHOD(sdl::controller::GameControllerWrapper::New) {
	if(!args.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Must create a GameController with the new operator.")));
	}



	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Exepcted new sdl.GameController(Number)")));
	}

	int index = args[0]->Int32Value();
	SDL_GameController* controller = SDL_GameControllerOpen(index);
	if(NULL == controller) {
		return ThrowSDLException(__func__);
	}

	GameControllerWrapper* wrap = new GameControllerWrapper();
	wrap->controller_ = controller;
	wrap->Wrap(args.This());

	return args.This();
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetAttached) {


	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(args.This());
	SDL_bool ret = SDL_GameControllerGetAttached(wrap->controller_);

	info.GetReturnValue().Set(Boolean::New(ret == SDL_TRUE ? true : false));
}
NAN_METHOD(sdl::controller::GameControllerWrapper::GetAxis) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetAxis(Number)")));
	}

	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(args.This());
	SDL_GameControllerAxis axis = static_cast<SDL_GameControllerAxis>(args[0]->Int32Value());
	int16_t ret = SDL_GameControllerGetAxis(wrap->controller_, axis);

	info.GetReturnValue().Set(Number::New(ret));
}
NAN_METHOD(sdl::controller::GameControllerWrapper::GetBindForAxis) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetBindForAxis(Number)")));
	}

	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(args.This());
	SDL_GameControllerAxis axis = static_cast<SDL_GameControllerAxis>(args[0]->Int32Value());
	SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForAxis(wrap->controller_, axis);

	info.GetReturnValue().Set(ControllerButtonBindToObject(bind));
}
NAN_METHOD(sdl::controller::GameControllerWrapper::GetBindForButton) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetBindForButton(Number)")));
	}

	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(args.This());
	SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(args[0]->Int32Value());
	SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForButton(wrap->controller_, button);

	info.GetReturnValue().Set(ControllerButtonBindToObject(bind));
}
NAN_METHOD(sdl::controller::GameControllerWrapper::GetButton) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetButton(Number)")));
	}

	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(args.This());
	SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(args[0]->Int32Value());
	uint8_t ret = SDL_GameControllerGetButton(wrap->controller_, button);

	info.GetReturnValue().Set(Boolean::New(ret == 1 ? true : false));
}
NAN_METHOD(sdl::controller::GameControllerWrapper::GetJoystick) {


	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(args.This());
	SDL_Joystick* joystick = SDL_GameControllerGetJoystick(wrap->controller_);

	Handle<Value> arg = External::New(joystick);
	Handle<Value> argv[] = {arg, Boolean::New(false)};
	info.GetReturnValue().Set(JoystickWrapper::tpl->GetFunction()->NewInstance(2, argv));
}
NAN_METHOD(sdl::controller::GameControllerWrapper::GetMapping) {


	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(args.This());
	char* mapping = SDL_GameControllerMapping(wrap->controller_);
	if(NULL == mapping) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(String::New(mapping));
}
NAN_METHOD(sdl::controller::GameControllerWrapper::GetName) {


	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(args.This());
	const char* name = SDL_GameControllerName(wrap->controller_);
	if(NULL == name) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(String::New(name));
}

NAN_METHOD(sdl::controller::AddMapping) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected AddMapping(String)")));
	}

	String::Utf8Value mapping(args[0]);
	int err = SDL_GameControllerAddMapping(*mapping);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(err));
}
NAN_METHOD(sdl::controller::AddMappingsFromFile) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected AddMappingFromFile(String)")));
	}

	String::Utf8Value file(args[0]);
	int err = SDL_GameControllerAddMappingsFromFile(*file);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(err));
}

NAN_METHOD(sdl::controller::MappingForGUID) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected MappingForGUID(String)")));
	}

	String::Utf8Value jsGuid(args[0]);
	SDL_JoystickGUID guid;
	for(int i = 0; i < 16; i++) {
		guid.data[i] = static_cast<uint8_t>((*jsGuid)[i]);
	}
	char* mapping = SDL_GameControllerMappingForGUID(guid);
	if(NULL == mapping) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(String::New(mapping));
}
NAN_METHOD(sdl::controller::NameForIndex) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected NameForIndex(Number)")));
	}

	int index = args[0]->Int32Value();
	const char* name = SDL_GameControllerNameForIndex(index);
	if(NULL == name) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(String::New(name));
}

NAN_METHOD(sdl::controller::EventState) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected EventState(Number)")));
	}

	int state = args[0]->Int32Value();
	int ret = SDL_GameControllerEventState(state);

	info.GetReturnValue().Set(Number::New(ret));
}
NAN_METHOD(sdl::controller::GetAxisFromString) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetAxisFromString(String)")));
	}

	String::Utf8Value pchString(args[0]);
	SDL_GameControllerAxis axis = SDL_GameControllerGetAxisFromString(*pchString);

	info.GetReturnValue().Set(Number::New(axis));
}
NAN_METHOD(sdl::controller::GetButtonFromString) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetButtonFromString(String)")));
	}

	String::Utf8Value pchString(args[0]);
	SDL_GameControllerButton button = SDL_GameControllerGetButtonFromString(*pchString);

	info.GetReturnValue().Set(Number::New(button));
}
NAN_METHOD(sdl::controller::GetStringForAxis) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetStringForAxis(Number)")));
	}

	SDL_GameControllerAxis axis = static_cast<SDL_GameControllerAxis>(args[0]->Int32Value());
	const char* axisString = SDL_GameControllerGetStringForAxis(axis);

	info.GetReturnValue().Set(String::New(axisString));
}
NAN_METHOD(sdl::controller::GetStringForButton) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetStringForButton(Number)")));
	}

	SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(args[0]->Int32Value());
	const char* buttonString = SDL_GameControllerGetStringForButton(button);

	info.GetReturnValue().Set(String::New(buttonString));
}

NAN_METHOD(Update) {


	SDL_GameControllerUpdate();

	return Undefined();
}
NAN_METHOD(IsController) {


	if(args.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected IsController(Number)")));
	}

	int index = args[0]->Int32Value();
	SDL_bool ret = SDL_IsGameController(index);

	info.GetReturnValue().Set(Boolean::New(ret == SDL_TRUE ? true : false));
}
