#include "sdl_gl.h"
#include "window.h"
#include "helpers.h"
#include "texture.h"

using namespace v8;
using namespace node;


NAN_MODULE_INIT(sdl::gl::Init) {
	Local<Object> GL = Object::New();
	exports->Set(String::New("GL"), GL);
	ContextWrapper::Init(GL);

	Nan::SetPrototypeMethod(GL, "bindTexture", BindTexture);
	Nan::SetPrototypeMethod(GL, "unbindTexture", UnbindTexture);

	Nan::SetPrototypeMethod(GL, "extensionSupported", ExtensionSupported);

	Nan::SetPrototypeMethod(GL, "loadLibrary", LoadLibrary);
	Nan::SetPrototypeMethod(GL, "unloadLibrary", UnloadLibrary);

	Nan::SetPrototypeMethod(GL, "setAttribute", SetAttribute);
	Nan::SetPrototypeMethod(GL, "makeCurrent", MakeCurrent);
	Nan::SetPrototypeMethod(GL, "setSwapInterval", SetSwapInterval);

	Nan::SetPrototypeMethod(GL, "getAttribute", GetAttribute);
	Nan::SetPrototypeMethod(GL, "getCurrentContext", GetCurrentContext);
	Nan::SetPrototypeMethod(GL, "getCurrentWindow", GetCurrentWindow);
	Nan::SetPrototypeMethod(GL, "getDrawableSize", GetDrawableSize);
	Nan::SetPrototypeMethod(GL, "getSwapInterval", GetSwapInterval);

	// SDL_GLattr enum.
	GL->Set(String::New("RED_SIZE"), Number::New(SDL_GL_RED_SIZE));
	GL->Set(String::New("GREEN_SIZE"), Number::New(SDL_GL_GREEN_SIZE));
	GL->Set(String::New("BLUE_SIZE"), Number::New(SDL_GL_BLUE_SIZE));
	GL->Set(String::New("ALPHA_SIZE"), Number::New(SDL_GL_ALPHA_SIZE));
	GL->Set(String::New("BUFFER_SIZE"), Number::New(SDL_GL_BUFFER_SIZE));
	GL->Set(String::New("DOUBLEBUFFER"), Number::New(SDL_GL_DOUBLEBUFFER));
	GL->Set(String::New("DEPTH_SIZE"), Number::New(SDL_GL_DEPTH_SIZE));
	GL->Set(String::New("STENCIL_SIZE"), Number::New(SDL_GL_STENCIL_SIZE));
	GL->Set(String::New("ACCUM_RED_SIZE"), Number::New(SDL_GL_ACCUM_RED_SIZE));
	GL->Set(String::New("ACCUM_GREEN_SIZE"), Number::New(SDL_GL_ACCUM_GREEN_SIZE));
	GL->Set(String::New("ACCUM_BLUE_SIZE"), Number::New(SDL_GL_ACCUM_BLUE_SIZE));
	GL->Set(String::New("ACCUM_ALPHA_SIZE"), Number::New(SDL_GL_ACCUM_ALPHA_SIZE));
	GL->Set(String::New("STEREO"), Number::New(SDL_GL_STEREO));
	GL->Set(String::New("MULTISAMPLEBUFFERS"), Number::New(SDL_GL_MULTISAMPLEBUFFERS));
	GL->Set(String::New("MULTISAMPLESAMPLES"), Number::New(SDL_GL_MULTISAMPLESAMPLES));
	GL->Set(String::New("ACCELERATED_VISUAL"), Number::New(SDL_GL_ACCELERATED_VISUAL));
	GL->Set(String::New("RETAINED_BACKING"), Number::New(SDL_GL_RETAINED_BACKING));
	GL->Set(String::New("CONTEXT_MAJOR_VERSION"), Number::New(SDL_GL_CONTEXT_MAJOR_VERSION));
	GL->Set(String::New("CONTEXT_MINOR_VERSION"), Number::New(SDL_GL_CONTEXT_MINOR_VERSION));
	GL->Set(String::New("CONTEXT_EGL"), Number::New(SDL_GL_CONTEXT_EGL));
	GL->Set(String::New("CONTEXT_FLAGS"), Number::New(SDL_GL_CONTEXT_FLAGS));
	GL->Set(String::New("CONTEXT_PROFILE_MASK"), Number::New(SDL_GL_CONTEXT_PROFILE_MASK));
	GL->Set(String::New("SHARE_WITH_CURRENT_CONTEXT"), Number::New(SDL_GL_SHARE_WITH_CURRENT_CONTEXT));
	GL->Set(String::New("FRAMEBUFFER_SRGB_CAPABLE"), Number::New(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE));
	// SDL_GLprofile enum.
	GL->Set(String::New("CONTEXT_PROFILE_CORE"), Number::New(SDL_GL_CONTEXT_PROFILE_CORE));
	GL->Set(String::New("CONTEXT_PROFILE_COMPATIBILITY"), Number::New(SDL_GL_CONTEXT_PROFILE_COMPATIBILITY));
	GL->Set(String::New("PROFILE_ES"), Number::New(SDL_GL_CONTEXT_PROFILE_ES));
	// SDL_GLcontextFlag enum.
	GL->Set(String::New("CONTEXT_DEBUG_FLAG"), Number::New(SDL_GL_CONTEXT_DEBUG_FLAG));
	GL->Set(String::New("CONTEXT_FORWARD_COMPATIBLE_FLAG"), Number::New(SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG));
	GL->Set(String::New("CONTEXT_ROBUST_ACCESS_FLAG"), Number::New(SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG));
	GL->Set(String::New("CONTEXT_RESET_ISOLATION_FLAG"), Number::New(SDL_GL_CONTEXT_RESET_ISOLATION_FLAG));
}

Persistent<FunctionTemplate> sdl::gl::ContextWrapper::constructor;

sdl::gl::ContextWrapper::ContextWrapper() {
}
sdl::gl::ContextWrapper::ContextWrapper(Handle<Object> obj) {
	Wrap(obj);
}
sdl::gl::ContextWrapper::~ContextWrapper() {
	if(NULL != context_) {
		SDL_GL_DeleteContext(context_);
	}
}

NAN_MODULE_INIT(sdl::gl::ContextWrapper::Init) {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->SetClassName(String::NewSymbol("ContextWrapper"));

	constructor = Persistent<FunctionTemplate>::New(tpl->GetFunction());
	exports.Set(String::NewSymbol("Context"), constructor)
}

NAN_METHOD(sdl::gl::ContextWrapper::New) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected new sdl.ContextWrapper(Window)")));
	}

	WindowWrapper* window = ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[0]));
	SDL_GLContext context = SDL_GL_CreateContext(window->window_);
	if(NULL == context) {
		return ThrowSDLException(__func__);
	}

	ContextWrapper* obj = new ContextWrapper();
	obj->context_ = context;
	obj->Wrap(info.This());
	return info.This();
}

NAN_METHOD(sdl::gl::BindTexture) {
	if(!info.IsConstructCall()) {
		return ThrowException(Exception::TypeError(
			String::New("Must create a Context with the new operator.")));
	}



	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected BindTexture(Texture)")));
	}

	TextureWrapper* obj = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(info[0]));
	float texw, texh;
	int err = SDL_GL_BindTexture(obj->texture_, &texw, &texh);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	Handle<Array> ret = Array::New(2);
	ret->Set(0, Number::New(texw));
	ret->Set(1, Number::New(texh));
	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::gl::UnbindTexture) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected BindTexture(Texture)")));
	}

	TextureWrapper* obj = ObjectWrap::Unwrap<TextureWrapper>(Handle<Object>::Cast(info[0]));
	int err = SDL_GL_UnbindTexture(obj->texture_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}

NAN_METHOD(sdl::gl::ExtensionSupported) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected ExtensionSupported(String)")));
	}

	String::Utf8Value name(info[0]);
	SDL_bool ret = SDL_GL_ExtensionSupported(*name);
	info.GetReturnValue().Set(Boolean::New(ret ? true : false));
}

NAN_METHOD(sdl::gl::LoadLibrary) {


	int err;
	if(info[0]->IsUndefined()) {
		err = SDL_GL_LoadLibrary(NULL);
	}
	else {
		String::Utf8Value name(info[0]);
		err = SDL_GL_LoadLibrary(*name);
	}
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::gl::UnloadLibrary) {


	SDL_GL_UnloadLibrary();

	return Undefined();
}

NAN_METHOD(sdl::gl::SetAttribute) {


	if (!(info.Length() == 2 && info[0]->IsNumber() && info[1]->IsNumber())) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected SetAttribute(Number, Number)")));
	}

	int attr = info[0]->Int32Value();
	int value = info[1]->Int32Value();

	if (SDL_GL_SetAttribute((SDL_GLattr)attr, value)) return ThrowSDLException(__func__);
	return Undefined();
}
NAN_METHOD(sdl::gl::MakeCurrent) {


	if(info.Length() < 2) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected MakeCurrent(Window, GLContext)")));
	}

	WindowWrapper* window = ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[0]));
	ContextWrapper* context = ObjectWrap::Unwrap<ContextWrapper>(Handle<Object>::Cast(info[1]));
	int err = SDL_GL_MakeCurrent(window->window_, context->context_);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}
NAN_METHOD(sdl::gl::SetSwapInterval) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Exception SetSwapInterval(Number)")));
	}

	int interval = info[0]->Int32Value();
	int err = SDL_GL_SetSwapInterval(interval);
	if(err < 0) {
		return ThrowSDLException(__func__);
	}

	return Undefined();
}

NAN_METHOD(sdl::gl::GetAttribute) {


	if (!(info.Length() == 1 && info[0]->IsNumber())) {
		return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetAttribute(Number)")));
	}

	int attr = info[0]->Int32Value();
	int value;

	if (SDL_GL_GetAttribute((SDL_GLattr)attr, &value)) return ThrowSDLException(__func__);

	return Number::New(value);
}
NAN_METHOD(sdl::gl::GetCurrentContext) {


	SDL_GLContext context = SDL_GL_GetCurrentContext();
	if(NULL == context) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> newObj = Object::New();
	ContextWrapper* wrap = new ContextWrapper(newObj);
	wrap->context_ = context;
	info.GetReturnValue().Set(newObj);
}
NAN_METHOD(sdl::gl::GetCurrentWindow) {


	SDL_Window* window = SDL_GL_GetCurrentWindow();
	if(NULL == window) {
		return ThrowSDLException(__func__);
	}

	Handle<Object> newObj = Object::New();
	WindowWrapper* wrap = new WindowWrapper(newObj);
	wrap->window_ = window;
	info.GetReturnValue().Set(newObj);
}
// TODO: Migrate to WindowWrapper object.
NAN_METHOD(sdl::gl::GetDrawableSize) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetDrawableSize(Window)")));
	}

	WindowWrapper* wrap = ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[0]));
	int w, h;
	SDL_GL_GetDrawableSize(wrap->window_, &w, &h);

	Handle<Array> ret = Array::New(2);
	ret->Set(0, Number::New(w));
	ret->Set(0, Number::New(h));
	info.GetReturnValue().Set(ret);
}
// TODO: Handle this somehow?
// Theoretically handleable with Handle<External>, but I don't see any use in wrapping a function
// pointer for Javascript. Better off loading addresses invisibly when SDL/OpenGl gets initialized
// and providing an API to access the functions.
// NAN_METHOD(sdl::gl::GetProcAddress) {
// }
NAN_METHOD(sdl::gl::GetSwapInterval) {


	int interval = SDL_GL_GetSwapInterval();
	info.GetReturnValue().Set(Number::New(interval));
}


