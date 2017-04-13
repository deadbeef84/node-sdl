#include "event.h"
#include "helpers.h"
#include "container.h"

#include <string>

using namespace v8;
using namespace node;


NAN_MODULE_INIT(sdl::event::Init) {
	Nan::SetPrototypeMethod(exports, "eventState", EventState);

	Nan::SetPrototypeMethod(exports, "flushEvent", FlushEvent);
	Nan::SetPrototypeMethod(exports, "flushEvents", FlushEvents);

	Nan::SetPrototypeMethod(exports, "getNumtouchDevices", GetNumTouchDevices);
	Nan::SetPrototypeMethod(exports, "getNumTouchFingers", GetNumTouchFingers);
	Nan::SetPrototypeMethod(exports, "getTouchDevice", GetTouchDevice);
	Nan::SetPrototypeMethod(exports, "getTouchFinger", GetTouchFinger);
	Nan::SetPrototypeMethod(exports, "recordGesture", RecordGesture);

	Nan::SetPrototypeMethod(exports, "hasEvent", HasEvent);
	Nan::SetPrototypeMethod(exports, "hasEvents", HasEvents);

	Nan::SetPrototypeMethod(exports, "waitEvent", sdl::WaitEvent);
	Nan::SetPrototypeMethod(exports, "waitEventTimeout", sdl::WaitEventTimeout);
	Nan::SetPrototypeMethod(exports, "pollEvent", sdl::PollEvent);

	Nan::SetPrototypeMethod(exports, "quitRequested", QuitRequested);
}

// TODO: Implement these in a way that will be able to call Javascript functions on the
//       main thread. (possibly create a custom implementation?) The callback to SDL_AddEventWatch,
//       per the SDL documentation, is not guaranteed to be on the same thread.
// NAN_METHOD(sdl::AddEventWatch) {
//
// 	return Undefined();
// }
// NAN_METHOD(sdl::DelEventWatch) {
//
// 	return Undefined();
// }
NAN_METHOD(sdl::EventState) {


	if(info.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected EventState(Number, Number)")));
	}

	int type = info[0]->Int32Value();
	int state = info[1]->Int32Value();
	int8_t ret = SDL_EventState(type, state);

	info.GetReturnValue().Set(Number::New(ret));
}

// TODO: Implement these in a way that will be able to call Javascript functions on the
//       main thread. (possibly create a custom implementation?) The callback to SDL_SetEventFilter,
//       per the SDL documentation, is not guaranteed to be on the same thread.
// NAN_METHOD(sdl::FilterEvents) {
//
// 	return Undefined();
// }
// NAN_METHOD(sdl::GetEventFilter) {
//
// 	return Undefined();
// }
// NAN_METHOD(sdl::SetEventFilter) {
//
// 	return Undefined();
// }

NAN_METHOD(sdl::FlushEvent) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected FlushEvent(Number)")));
	}

	int type = info[0]->Int32Value();
	SDL_FlushEvent(type);

	return Undefined();
}
NAN_METHOD(sdl::FlushEvents) {


	if(info.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected FlushEvent(Number, Number)")));
	}

	int typeMin = info[0]->Int32Value();
	int typeMax = info[1]->Int32Value();
	SDL_FlushEvents(typeMin, typeMax);

	return Undefined();
}

NAN_METHOD(sdl::GetNumTouchDevices) {


	int ret = SDL_GetNumTouchDevices();

	info.GetReturnValue().Set(Number::New(ret));
}
NAN_METHOD(sdl::GetNumTouchFingers) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetNumTouchFingers(Number)")));
	}

	SDL_TouchID id = static_cast<SDL_TouchID>(info[0]->IntegerValue());
	int ret = SDL_GetNumTouchFingers(id);
	if(0 == ret) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(ret));
}
NAN_METHOD(sdl::GetTouchDevice) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetTouchDevice(Number)")));
	}

	int index = info[0]->Int32Value();
	SDL_TouchID device = SDL_GetTouchDevice(index);
	if(0 == device) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Number::New(device));
}
NAN_METHOD(sdl::GetTouchFinger) {


	if(info.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetTouchFinger(Number, Number)")));
	}

	SDL_TouchID id = static_cast<SDL_TouchID>(info[0]->IntegerValue());
	int index = info[1]->Int32Value();
	SDL_Finger* finger = SDL_GetTouchFinger(id, index);
	if(NULL == finger) {
		return ThrowSDLException(__func__);
	}

	Local<Object> toWrap = Object::New();
	FingerWrapper* ret = new FingerWrapper(toWrap);
	ret->finger_ = finger;

	info.GetReturnValue().Set(toWrap);
}
NAN_METHOD(sdl::RecordGesture) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected RecordGesture(Number)")));
	}

	SDL_TouchID id = static_cast<SDL_TouchID>(info[0]->IntegerValue());
	int err = SDL_RecordGesture(id);
	if(0 == err) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}

NAN_METHOD(sdl::HasEvent) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected HasEvent(Number)")));
	}

	int type = info[0]->Int32Value();
	SDL_bool ret = SDL_HasEvent(type);

	info.GetReturnValue().Set(Boolean::New(ret ? true : false));
}
NAN_METHOD(sdl::HasEvents) {


	if(info.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected HasEvents(Number, Number)")));
	}

	int typeMin = info[0]->Int32Value();
	int typeMax = info[1]->Int32Value();
	SDL_bool ret = SDL_HasEvents(typeMin, typeMax);

	info.GetReturnValue().Set(Boolean::New(ret ? true : false));
}

// TODO: Implement these, along with RWOps wrapper.
//       (too lazy to implement RWOps right now)
// NAN_METHOD(sdl::LoadDollarTemplates) {
//

// 	return Undefined();
// }
// NAN_METHOD(sdl::SaveAllDollarTemplates) {
//

// 	return Undefined();
// }
// NAN_METHOD(sdl::SaveDollarTemplate) {
//

// 	return Undefined();
// }

NAN_METHOD(sdl::WaitEvent) {


	if (!(info.Length() == 1 && info[0]->IsFunction())) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected WaitEvent(Function)")));
	}

	SDL_Event e;
	int err = SDL_WaitEvent(&e);
	if(0 == err) {
		std::string err = "WaitEvent failed: ";
		err += SDL_GetError();
		return ThrowException(MakeSDLException(err.c_str()));
	}
	Handle<Value> argv[1];
	argv[0] = sdl::SDLEventToJavascriptObject(e);
	Handle<Function>::Cast(info[0])->Call(Context::GetCurrent()->Global(), 1, argv);
	return Undefined();
}

NAN_METHOD(sdl::WaitEventTimeout) {


	if(!(info.Length() == 2 && info[0]->IsFunction() && info[1]->IsNumber())) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected WaitEventTimeout(Function, Number)")));
	}

	SDL_Event e;
	int timeout = info[1]->Int32Value();
	int err = SDL_WaitEventTimeout(&e, timeout);
	if(0 == err) {
		std::string err = "WaitEventTimeout failed: ";
		err += SDL_GetError();
		return ThrowException(MakeSDLException(err.c_str()));
	}
	Handle<Value> argv[1];
	argv[0] = sdl::SDLEventToJavascriptObject(e);
	Handle<Function>::Cast(info[0])->Call(Context::GetCurrent()->Global(), 1, argv);
	return Undefined();
}

NAN_METHOD(sdl::PollEvent) {


	if (!(info.Length() == 0)) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected PollEvent()")));
	}

	SDL_Event event;
	if (!SDL_PollEvent(&event)) {
		return Undefined();
	}

	Local<Object> evt = SDLEventToJavascriptObject(event);
	info.GetReturnValue().Set(evt);
}
// TODO: Implement this function.
//		 This is a relatively complicated function which uses an array to put/get events into/from
//		 the event queue. The same functionality can be achieved using other functions, so I'll
// 		 deal with this later. (too lazy right now, again)
// NAN_METHOD(sdl::PeepEvents) {
//

// 	return Undefined();
// }
// TODO: Implement this function.
// 		 None of the functions which make pump useful are implemented, so there's no use in
// 		 exposing this function yet. (for example, filtering events of peeping events)
//		 Just use poll for now.
// NAN_METHOD(sdl::PumpEvents) {
//

// 	return Undefined();
// }
// TODO: Implement when events are refactored. Huge pain to convert from object to event right now,
//  	 similar effort to the current event to object conversion. (should just be a wrapper)
// NAN_METHOD(sdl::PushEvent) {
//

// 	if(info.Length() < 1) {
// 		return ThrowException(Exception::TypeError(
// 			String::New("Invalid arguments: Expected PushEvent(Event)")));
// 	}

// 	return Undefined();
// }
// TODO: Implement when push is implemented. Can only be used when you can push a custom
// 		 event.
// NAN_METHOD(sdl::RegisterEvents) {
//

// 	return Undefined();
// }

NAN_METHOD(sdl::QuitRequested) {


	bool ret = SDL_QuitRequested();

	info.GetReturnValue().Set(Boolean::New(ret));
}

// TODO: Improve on how events are created. Gotta be a better way than this...
Local<Object> SDLEventToJavascriptObject(const SDL_Event& event) {
	Local<Object> evt = Object::New();

	switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			evt->Set(String::New("type"), String::New(event.type == SDL_KEYDOWN ? "KEYDOWN" : "KEYUP"));
			evt->Set(String::New("scancode"), Number::New(event.key.keysym.scancode));
			evt->Set(String::New("sym"), Number::New(event.key.keysym.sym));
			evt->Set(String::New("mod"), Number::New(event.key.keysym.mod));
			break;
		case SDL_MOUSEMOTION:
			evt->Set(String::New("type"), String::New("MOUSEMOTION"));
			evt->Set(String::New("state"), Number::New(event.motion.state));
			evt->Set(String::New("which"), Number::New(event.motion.which));
			evt->Set(String::New("x"), Number::New(event.motion.x));
			evt->Set(String::New("y"), Number::New(event.motion.y));
			evt->Set(String::New("xrel"), Number::New(event.motion.xrel));
			evt->Set(String::New("yrel"), Number::New(event.motion.yrel));
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			evt->Set(String::New("type"), String::New(event.type == SDL_MOUSEBUTTONDOWN ? "MOUSEBUTTONDOWN" : "MOUSEBUTTONUP"));
			evt->Set(String::New("button"), Number::New(event.button.button));
			evt->Set(String::New("which"), Number::New(event.button.which));
			evt->Set(String::New("x"), Number::New(event.button.x));
			evt->Set(String::New("y"), Number::New(event.button.y));
			break;
		case SDL_JOYAXISMOTION:
			evt->Set(String::New("type"), String::New("JOYAXISMOTION"));
			evt->Set(String::New("which"), Number::New(event.jaxis.which));
			evt->Set(String::New("axis"), Number::New(event.jaxis.axis));
			evt->Set(String::New("value"), Number::New(event.jaxis.value));
			break;
		case SDL_JOYBALLMOTION:
			evt->Set(String::New("type"), String::New("JOYBALLMOTION"));
			evt->Set(String::New("which"), Number::New(event.jball.which));
			evt->Set(String::New("ball"), Number::New(event.jball.ball));
			evt->Set(String::New("xrel"), Number::New(event.jball.xrel));
			evt->Set(String::New("yrel"), Number::New(event.jball.yrel));
			break;
		case SDL_JOYHATMOTION:
			evt->Set(String::New("type"), String::New("JOYHATMOTION"));
			evt->Set(String::New("which"), Number::New(event.jhat.which));
			evt->Set(String::New("hat"), Number::New(event.jhat.hat));
			evt->Set(String::New("value"), Number::New(event.jhat.value));
			break;
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			evt->Set(String::New("type"), String::New(event.type == SDL_JOYBUTTONDOWN ? "JOYBUTTONDOWN" : "JOYBUTTONUP"));
			evt->Set(String::New("which"), Number::New(event.jbutton.which));
			evt->Set(String::New("button"), Number::New(event.jbutton.button));
			break;
		case SDL_QUIT:
			evt->Set(String::New("type"), String::New("QUIT"));
			break;
		default:
			evt->Set(String::New("type"), String::New("UNKNOWN"));
			evt->Set(String::New("typeCode"), Number::New(event.type));
			break;
	}

	return evt;
}
