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
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected EventState(Number, Number)"));
		return;
	}

	int type = info[0]->Int32Value();
	int state = info[1]->Int32Value();
	int8_t ret = SDL_EventState(type, state);

	info.GetReturnValue().Set(Nan::New<Number>(ret));
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
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected FlushEvent(Number)"));
		return;
	}

	int type = info[0]->Int32Value();
	SDL_FlushEvent(type);
}

NAN_METHOD(sdl::FlushEvents) {
	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected FlushEvent(Number, Number)"));
		return;
	}

	int typeMin = info[0]->Int32Value();
	int typeMax = info[1]->Int32Value();
	SDL_FlushEvents(typeMin, typeMax);
}

NAN_METHOD(sdl::GetNumTouchDevices) {
	int ret = SDL_GetNumTouchDevices();

	info.GetReturnValue().Set(Nan::New<Number>(ret));
}

NAN_METHOD(sdl::GetNumTouchFingers) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetNumTouchFingers(Number)"));
		return;
	}

	SDL_TouchID id = static_cast<SDL_TouchID>(info[0]->IntegerValue());
	int ret = SDL_GetNumTouchFingers(id);
	if(0 == ret) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(ret));
}

NAN_METHOD(sdl::GetTouchDevice) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetTouchDevice(Number)"));
		return;
	}

	int index = info[0]->Int32Value();
	SDL_TouchID device = SDL_GetTouchDevice(index);
	if(0 == device) {
		return ThrowSDLException(__func__);
	}

	info.GetReturnValue().Set(Nan::New<Number>(device));
}

NAN_METHOD(sdl::GetTouchFinger) {
	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetTouchFinger(Number, Number)"));
		return;
	}

	SDL_TouchID id = static_cast<SDL_TouchID>(info[0]->IntegerValue());
	int index = info[1]->Int32Value();
	SDL_Finger* finger = SDL_GetTouchFinger(id, index);
	if(NULL == finger) {
		return ThrowSDLException(__func__);
	}

	Local<Object> toWrap = Nan::New<Object>();
	FingerWrapper* ret = new FingerWrapper(toWrap);
	ret->finger_ = finger;

	info.GetReturnValue().Set(toWrap);
}

NAN_METHOD(sdl::RecordGesture) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected RecordGesture(Number)"));
		return;
	}

	SDL_TouchID id = static_cast<SDL_TouchID>(info[0]->IntegerValue());
	int err = SDL_RecordGesture(id);
	if(0 == err) {
		return ThrowSDLException(__func__);
	}
}

NAN_METHOD(sdl::HasEvent) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected HasEvent(Number)"));
		return;
	}

	int type = info[0]->Int32Value();
	SDL_bool ret = SDL_HasEvent(type);

	info.GetReturnValue().Set(Nan::New<Boolean>(ret ? true : false));
}
NAN_METHOD(sdl::HasEvents) {
	if(info.Length() < 2) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected HasEvents(Number, Number)"));
		return;
	}

	int typeMin = info[0]->Int32Value();
	int typeMax = info[1]->Int32Value();
	SDL_bool ret = SDL_HasEvents(typeMin, typeMax);

	info.GetReturnValue().Set(Nan::New<Boolean>(ret ? true : false));
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
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected WaitEvent(Function)"));
		return;
	}

	SDL_Event e;
	int err = SDL_WaitEvent(&e);
	if(0 == err) {
		std::string err = "WaitEvent failed: ";
		err += SDL_GetError();
		ThrowSDLException(err.c_str());
		return
	}
	Handle<Value> argv[1];
	argv[0] = sdl::SDLEventToJavascriptObject(e);
	Handle<Function>::Cast(info[0])->Call(Context::GetCurrent()->Global(), 1, argv);
}

NAN_METHOD(sdl::WaitEventTimeout) {
	if(!(info.Length() == 2 && info[0]->IsFunction() && info[1]->IsNumber())) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected WaitEventTimeout(Function, Number)"));
		return;
	}

	SDL_Event e;
	int timeout = info[1]->Int32Value();
	int err = SDL_WaitEventTimeout(&e, timeout);
	if(0 == err) {
		std::string err = "WaitEventTimeout failed: ";
		err += SDL_GetError();
		Nan::ThrowException(MakeSDLException(err.c_str()));
		return
	}
	Handle<Value> argv[1];
	argv[0] = sdl::SDLEventToJavascriptObject(e);
	Handle<Function>::Cast(info[0])->Call(Context::GetCurrent()->Global(), 1, argv);
}

NAN_METHOD(sdl::PollEvent) {
	if (!(info.Length() == 0)) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected PollEvent()"));
		return;
	}

	SDL_Event event;
	if (!SDL_PollEvent(&event)) {
		return;
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
// 		Nan::ThrowTypeError(// 			STRING_NEW("Invalid arguments: Expected PushEvent(Event)"));
		return;
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

	info.GetReturnValue().Set(Nan::New<Boolean>(ret));
}

// TODO: Improve on how events are created. Gotta be a better way than this...
Local<Object> SDLEventToJavascriptObject(const SDL_Event& event) {
	Local<Object> evt = Nan::New<Object>();

	switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New(event.type == SDL_KEYDOWN ? "KEYDOWN" : "KEYUP").ToLocalChecked());
			evt->Set(Nan::New("scancode").ToLocalChecked(), Nan::New<Number>(event.key.keysym.scancode));
			evt->Set(Nan::New("sym").ToLocalChecked(), Nan::New<Number>(event.key.keysym.sym));
			evt->Set(Nan::New("mod").ToLocalChecked(), Nan::New<Number>(event.key.keysym.mod));
			break;
		case SDL_MOUSEMOTION:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("MOUSEMOTION").ToLocalChecked());
			evt->Set(Nan::New("state").ToLocalChecked(), Nan::New<Number>(event.motion.state));
			evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.motion.which));
			evt->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(event.motion.x));
			evt->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(event.motion.y));
			evt->Set(Nan::New("xrel").ToLocalChecked(), Nan::New<Number>(event.motion.xrel));
			evt->Set(Nan::New("yrel").ToLocalChecked(), Nan::New<Number>(event.motion.yrel));
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New(event.type == SDL_MOUSEBUTTONDOWN ? "MOUSEBUTTONDOWN" : "MOUSEBUTTONUP").ToLocalChecked());
			evt->Set(Nan::New("button").ToLocalChecked(), Nan::New<Number>(event.button.button));
			evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.button.which));
			evt->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(event.button.x));
			evt->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(event.button.y));
			break;
		case SDL_JOYAXISMOTION:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("JOYAXISMOTION").ToLocalChecked());
			evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.jaxis.which));
			evt->Set(Nan::New("axis").ToLocalChecked(), Nan::New<Number>(event.jaxis.axis));
			evt->Set(Nan::New("value").ToLocalChecked(), Nan::New<Number>(event.jaxis.value));
			break;
		case SDL_JOYBALLMOTION:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("JOYBALLMOTION").ToLocalChecked());
			evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.jball.which));
			evt->Set(Nan::New("ball").ToLocalChecked(), Nan::New<Number>(event.jball.ball));
			evt->Set(Nan::New("xrel").ToLocalChecked(), Nan::New<Number>(event.jball.xrel));
			evt->Set(Nan::New("yrel").ToLocalChecked(), Nan::New<Number>(event.jball.yrel));
			break;
		case SDL_JOYHATMOTION:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("JOYHATMOTION").ToLocalChecked());
			evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.jhat.which));
			evt->Set(Nan::New("hat").ToLocalChecked(), Nan::New<Number>(event.jhat.hat));
			evt->Set(Nan::New("value").ToLocalChecked(), Nan::New<Number>(event.jhat.value));
			break;
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New(event.type == SDL_JOYBUTTONDOWN ? "JOYBUTTONDOWN" : "JOYBUTTONUP").ToLocalChecked());
			evt->Set(Nan::New("which").ToLocalChecked(), Nan::New<Number>(event.jbutton.which));
			evt->Set(Nan::New("button").ToLocalChecked(), Nan::New<Number>(event.jbutton.button));
			break;
		case SDL_QUIT:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("QUIT").ToLocalChecked());
			break;
		default:
			evt->Set(Nan::New("type").ToLocalChecked(), Nan::New("UNKNOWN").ToLocalChecked());
			evt->Set(Nan::New("typeCode").ToLocalChecked(), Nan::New<Number>(event.type));
			break;
	}

	return evt;
}
