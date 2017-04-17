#include "controller.h"
#include "joystick.h"
#include "helpers.h"

using namespace v8;
using namespace node;


static Handle<Object> ControllerButtonBindToObject(SDL_GameControllerButtonBind bind) {
	Handle<Object> ret = Nan::New<Object>();
	ret->Set(STRING_NEW("type"), Nan::New<Number>(bind.bindType));
	switch(bind.bindType) {
	case SDL_CONTROLLER_BINDTYPE_NONE:
		// Nothing to do here. Just wanted to shut the compiler up :)
		break;
	case SDL_CONTROLLER_BINDTYPE_BUTTON:
		ret->Set(STRING_NEW("button"), Nan::New<Number>(bind.value.button));
		break;
	case SDL_CONTROLLER_BINDTYPE_AXIS:
		ret->Set(STRING_NEW("axis"), Nan::New<Number>(bind.value.axis));
		break;
	case SDL_CONTROLLER_BINDTYPE_HAT:
		Handle<Object> hat = Nan::New<Object>();
		hat->Set(STRING_NEW("hat"), Nan::New<Number>(bind.value.hat.hat));
		hat->Set(STRING_NEW("hatMask"), Nan::New<Number>(bind.value.hat.hat_mask));
		ret->Set(STRING_NEW("hat"), hat);
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

	Handle<Object> BINDTYPE = Nan::New<Object>();
	exports->Set(STRING_NEW("BINDTYPE"), BINDTYPE);
	BINDTYPE->Set(STRING_NEW("NONE"), Nan::New<Number>(SDL_CONTROLLER_BINDTYPE_NONE));
	BINDTYPE->Set(STRING_NEW("BUTTON"), Nan::New<Number>(SDL_CONTROLLER_BINDTYPE_BUTTON));
	BINDTYPE->Set(STRING_NEW("AXIS"), Nan::New<Number>(SDL_CONTROLLER_BINDTYPE_AXIS));
	BINDTYPE->Set(STRING_NEW("HAT"), Nan::New<Number>(SDL_CONTROLLER_BINDTYPE_HAT));

	Handle<Object> AXIS = Nan::New<Object>();
	exports->Set(STRING_NEW("AXIS"), AXIS);
	AXIS->Set(STRING_NEW("INVALID"), Nan::New<Number>(SDL_CONTROLLER_AXIS_INVALID));
	AXIS->Set(STRING_NEW("LEFTX"), Nan::New<Number>(SDL_CONTROLLER_AXIS_LEFTX));
	AXIS->Set(STRING_NEW("LEFTY"), Nan::New<Number>(SDL_CONTROLLER_AXIS_LEFTY));
	AXIS->Set(STRING_NEW("RIGHTX"), Nan::New<Number>(SDL_CONTROLLER_AXIS_RIGHTX));
	AXIS->Set(STRING_NEW("RIGHTY"), Nan::New<Number>(SDL_CONTROLLER_AXIS_RIGHTY));
	AXIS->Set(STRING_NEW("TRIGGERLEFT"), Nan::New<Number>(SDL_CONTROLLER_AXIS_TRIGGERLEFT));
	AXIS->Set(STRING_NEW("TRIGGERRIGHT"), Nan::New<Number>(SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
	AXIS->Set(STRING_NEW("MAX"), Nan::New<Number>(SDL_CONTROLLER_AXIS_MAX));

	Handle<Object> BUTTON = Nan::New<Object>();
	exports->Set(STRING_NEW("BUTTON"), BUTTON);
	BUTTON->Set(STRING_NEW("INVALID"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_INVALID));
	BUTTON->Set(STRING_NEW("A"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_A));
	BUTTON->Set(STRING_NEW("B"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_B));
	BUTTON->Set(STRING_NEW("X"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_X));
	BUTTON->Set(STRING_NEW("Y"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_Y));
	BUTTON->Set(STRING_NEW("BACK"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_BACK));
	BUTTON->Set(STRING_NEW("GUIDE"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_GUIDE));
	BUTTON->Set(STRING_NEW("START"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_START));
	BUTTON->Set(STRING_NEW("LEFTSTICK"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_LEFTSTICK));
	BUTTON->Set(STRING_NEW("RIGHTSTICK"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_RIGHTSTICK));
	BUTTON->Set(STRING_NEW("LEFTSHOULDER"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_LEFTSHOULDER));
	BUTTON->Set(STRING_NEW("RIGHTSHOULDER"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER));
	BUTTON->Set(STRING_NEW("DPAD_UP"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_DPAD_UP));
	BUTTON->Set(STRING_NEW("DPAD_DOWN"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_DPAD_DOWN));
	BUTTON->Set(STRING_NEW("DPAD_LEFT"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_DPAD_LEFT));
	BUTTON->Set(STRING_NEW("DPAD_RIGHT"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_DPAD_RIGHT));
	BUTTON->Set(STRING_NEW("MAX"), Nan::New<Number>(SDL_CONTROLLER_BUTTON_MAX));
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
	Handle<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(STRING_NEW("GameControllerWrapper"));

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

	constructor.Reset(tpl);
	Nan::Set(target, STRING_NEW("GameController"), tpl->GetFunction());
}

NAN_METHOD(sdl::controller::GameControllerWrapper::New) {
	if(!info.IsConstructCall()) {
		Nan::ThrowTypeError(Nan::New("Must create a GameController with the new operator.").ToLocalChecked());
		return;
	}

	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Exepcted new sdl.GameController(Number)"));
		return;
	}

	int index = info[0]->Int32Value();
	SDL_GameController* controller = SDL_GameControllerOpen(index);
	if(NULL == controller) {
		return ThrowSDLException(__func__);
	}

	GameControllerWrapper* wrap = new GameControllerWrapper();
	wrap->controller_ = controller;
	wrap->Wrap(info.This());

	return info.This();
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetAttached) {
	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(info.This());
	SDL_bool ret = SDL_GameControllerGetAttached(wrap->controller_);

	info.GetReturnValue().Set(Nan::New<Boolean>(ret == SDL_TRUE ? true : false));
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetAxis) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetAxis(Number)"));
		return;
	}

	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(info.This());
	SDL_GameControllerAxis axis = static_cast<SDL_GameControllerAxis>(info[0]->Int32Value());
	int16_t ret = SDL_GameControllerGetAxis(wrap->controller_, axis);

	info.GetReturnValue().Set(Nan::New<Number>(ret));
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetBindForAxis) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetBindForAxis(Number)"));
		return;
	}

	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(info.This());
	SDL_GameControllerAxis axis = static_cast<SDL_GameControllerAxis>(info[0]->Int32Value());
	SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForAxis(wrap->controller_, axis);

	info.GetReturnValue().Set(ControllerButtonBindToObject(bind));
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetBindForButton) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetBindForButton(Number)"));
		return;
	}

	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(info.This());
	SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(info[0]->Int32Value());
	SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForButton(wrap->controller_, button);

	info.GetReturnValue().Set(ControllerButtonBindToObject(bind));
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetButton) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetButton(Number)"));
		return;
	}

	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(info.This());
	SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(info[0]->Int32Value());
	uint8_t ret = SDL_GameControllerGetButton(wrap->controller_, button);

	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1 ? true : false));
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetJoystick) {
	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(info.This());
	SDL_Joystick* joystick = SDL_GameControllerGetJoystick(wrap->controller_);

	Handle<Value> arg = External::New(joystick);
	Handle<Value> argv[] = {arg, Nan::New<Boolean>(false)};
	info.GetReturnValue().Set(JoystickWrapper::tpl->GetFunction()->NewInstance(2, argv));
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetMapping) {
	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(info.This());
	char* mapping = SDL_GameControllerMapping(wrap->controller_);
	if(NULL == mapping) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New(mapping).ToLocalChecked());
}

NAN_METHOD(sdl::controller::GameControllerWrapper::GetName) {
	GameControllerWrapper* wrap = ObjectWrap::Unwrap<GameControllerWrapper>(info.This());
	const char* name = SDL_GameControllerName(wrap->controller_);
	if(NULL == name) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New(name).ToLocalChecked());
}

NAN_METHOD(sdl::controller::AddMapping) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected AddMapping(String)"));
		return;
	}

	String::Utf8Value mapping(info[0]);
	int err = SDL_GameControllerAddMapping(*mapping);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(err));
}

NAN_METHOD(sdl::controller::AddMappingsFromFile) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected AddMappingFromFile(String)"));
		return;
	}

	String::Utf8Value file(info[0]);
	int err = SDL_GameControllerAddMappingsFromFile(*file);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(err));
}

NAN_METHOD(sdl::controller::MappingForGUID) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected MappingForGUID(String)"));
		return;
	}

	String::Utf8Value jsGuid(info[0]);
	SDL_JoystickGUID guid;
	for(int i = 0; i < 16; i++) {
		guid.data[i] = static_cast<uint8_t>((*jsGuid)[i]);
	}
	char* mapping = SDL_GameControllerMappingForGUID(guid);
	if(NULL == mapping) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New(mapping).ToLocalChecked());
}

NAN_METHOD(sdl::controller::NameForIndex) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected NameForIndex(Number)"));
		return;
	}

	int index = info[0]->Int32Value();
	const char* name = SDL_GameControllerNameForIndex(index);
	if(NULL == name) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New(name).ToLocalChecked());
}

NAN_METHOD(sdl::controller::EventState) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected EventState(Number)"));
		return;
	}

	int state = info[0]->Int32Value();
	int ret = SDL_GameControllerEventState(state);

	info.GetReturnValue().Set(Nan::New<Number>(ret));
}

NAN_METHOD(sdl::controller::GetAxisFromString) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetAxisFromString(String)"));
		return;
	}

	String::Utf8Value pchString(info[0]);
	SDL_GameControllerAxis axis = SDL_GameControllerGetAxisFromString(*pchString);

	info.GetReturnValue().Set(Nan::New<Number>(axis));
}

NAN_METHOD(sdl::controller::GetButtonFromString) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetButtonFromString(String)"));
		return;
	}

	String::Utf8Value pchString(info[0]);
	SDL_GameControllerButton button = SDL_GameControllerGetButtonFromString(*pchString);

	info.GetReturnValue().Set(Nan::New<Number>(button));
}

NAN_METHOD(sdl::controller::GetStringForAxis) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetStringForAxis(Number)"));
		return;
	}

	SDL_GameControllerAxis axis = static_cast<SDL_GameControllerAxis>(info[0]->Int32Value());
	const char* axisString = SDL_GameControllerGetStringForAxis(axis);

	info.GetReturnValue().Set(Nan::New(axisString).ToLocalChecked());
}
NAN_METHOD(sdl::controller::GetStringForButton) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetStringForButton(Number)"));
		return;
	}

	SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(info[0]->Int32Value());
	const char* buttonString = SDL_GameControllerGetStringForButton(button);

	info.GetReturnValue().Set(Nan::New(buttonString).ToLocalChecked());
}

NAN_METHOD(Update) {
	SDL_GameControllerUpdate();
}

NAN_METHOD(IsController) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected IsController(Number)"));
		return;
	}

	int index = info[0]->Int32Value();
	SDL_bool ret = SDL_IsGameController(index);

	info.GetReturnValue().Set(Nan::New<Boolean>(ret == SDL_TRUE ? true : false));
}
