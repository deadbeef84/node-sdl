#include "key.h"
#include "window.h"
#include "struct_wrappers.h"
#include "container.h"

using namespace v8;
using namespace node;


NAN_MODULE_INIT(sdl::key::Init) {


	Handle<Object> KEY = Nan::New<Object>();
	Nan::Set(target, STRING_NEW("KEY"), KEY);
	// Keys are set in the order that they are listed on this page:
	//  http://wiki.libsdl.org/SDLKeycodeLookup
	KEY->Set(STRING_NEW("BACKSPACE"), Nan::New<Number>(SDLK_BACKSPACE));
	KEY->Set(STRING_NEW("TAB"), Nan::New<Number>(SDLK_BACKSPACE));
	KEY->Set(STRING_NEW("RETURN"), Nan::New<Number>(SDLK_RETURN));
	KEY->Set(STRING_NEW("ESCAPE"), Nan::New<Number>(SDLK_ESCAPE));
	KEY->Set(STRING_NEW("SPACE"), Nan::New<Number>(SDLK_SPACE));
	KEY->Set(STRING_NEW("EXCLAIM"), Nan::New<Number>(SDLK_EXCLAIM));
	KEY->Set(STRING_NEW("QUOTEDBL"), Nan::New<Number>(SDLK_QUOTEDBL));
	KEY->Set(STRING_NEW("HASH"), Nan::New<Number>(SDLK_HASH));
	KEY->Set(STRING_NEW("DOLLAR"), Nan::New<Number>(SDLK_DOLLAR));
	KEY->Set(STRING_NEW("PERCENT"), Nan::New<Number>(SDLK_PERCENT));
	KEY->Set(STRING_NEW("APERSAND"), Nan::New<Number>(SDLK_AMPERSAND));
	KEY->Set(STRING_NEW("QUOTE"), Nan::New<Number>(SDLK_QUOTE));
	KEY->Set(STRING_NEW("LEFTPAREN"), Nan::New<Number>(SDLK_LEFTPAREN));
	KEY->Set(STRING_NEW("RIGHTPAREN"), Nan::New<Number>(SDLK_RIGHTPAREN));
	KEY->Set(STRING_NEW("ASTERISK"), Nan::New<Number>(SDLK_ASTERISK));
	KEY->Set(STRING_NEW("PLUS"), Nan::New<Number>(SDLK_PLUS));
	KEY->Set(STRING_NEW("COMMA"), Nan::New<Number>(SDLK_COMMA));
	KEY->Set(STRING_NEW("MINUS"), Nan::New<Number>(SDLK_MINUS));
	KEY->Set(STRING_NEW("PERIOD"), Nan::New<Number>(SDLK_PERIOD));
	KEY->Set(STRING_NEW("SLASH"), Nan::New<Number>(SDLK_SLASH));
	// Number keys. Numbers are written out due to being unable to write:
	//   foo.0 = "bar";
	// (even if you can do: foo[0] = "bar", it just isn't as friendly)
	KEY->Set(STRING_NEW("ZERO"), Nan::New<Number>(SDLK_0));
	KEY->Set(STRING_NEW("ONE"), Nan::New<Number>(SDLK_1));
	KEY->Set(STRING_NEW("TWO"), Nan::New<Number>(SDLK_2));
	KEY->Set(STRING_NEW("THREE"), Nan::New<Number>(SDLK_3));
	KEY->Set(STRING_NEW("FOUR"), Nan::New<Number>(SDLK_4));
	KEY->Set(STRING_NEW("FIVE"), Nan::New<Number>(SDLK_5));
	KEY->Set(STRING_NEW("SIX"), Nan::New<Number>(SDLK_6));
	KEY->Set(STRING_NEW("SEVEN"), Nan::New<Number>(SDLK_7));
	KEY->Set(STRING_NEW("EIGHT"), Nan::New<Number>(SDLK_8));
	KEY->Set(STRING_NEW("NINE"), Nan::New<Number>(SDLK_9));
	KEY->Set(STRING_NEW("COLON"), Nan::New<Number>(SDLK_COLON));
	KEY->Set(STRING_NEW("SEMICOLON"), Nan::New<Number>(SDLK_SEMICOLON));
	KEY->Set(STRING_NEW("LESS"), Nan::New<Number>(SDLK_LESS));
	KEY->Set(STRING_NEW("EQUALS"), Nan::New<Number>(SDLK_EQUALS));
	KEY->Set(STRING_NEW("GREATER"), Nan::New<Number>(SDLK_GREATER));
	KEY->Set(STRING_NEW("QUESTION"), Nan::New<Number>(SDLK_QUESTION));
	KEY->Set(STRING_NEW("AT"), Nan::New<Number>(SDLK_AT));
	KEY->Set(STRING_NEW("LEFTBRACKET"), Nan::New<Number>(SDLK_LEFTBRACKET));
	KEY->Set(STRING_NEW("BACKSLASH"), Nan::New<Number>(SDLK_BACKSLASH));
	KEY->Set(STRING_NEW("RIGHTBRACKET"), Nan::New<Number>(SDLK_RIGHTBRACKET));
	KEY->Set(STRING_NEW("CARET"), Nan::New<Number>(SDLK_CARET));
	KEY->Set(STRING_NEW("UNDERSCORE"), Nan::New<Number>(SDLK_UNDERSCORE));
	KEY->Set(STRING_NEW("BACKQUOTE"), Nan::New<Number>(SDLK_BACKQUOTE));
	KEY->Set(STRING_NEW("A"), Nan::New<Number>(SDLK_a));
	KEY->Set(STRING_NEW("B"), Nan::New<Number>(SDLK_b));
	KEY->Set(STRING_NEW("C"), Nan::New<Number>(SDLK_c));
	KEY->Set(STRING_NEW("D"), Nan::New<Number>(SDLK_d));
	KEY->Set(STRING_NEW("E"), Nan::New<Number>(SDLK_e));
	KEY->Set(STRING_NEW("F"), Nan::New<Number>(SDLK_f));
	KEY->Set(STRING_NEW("G"), Nan::New<Number>(SDLK_g));
	KEY->Set(STRING_NEW("H"), Nan::New<Number>(SDLK_h));
	KEY->Set(STRING_NEW("I"), Nan::New<Number>(SDLK_i));
	KEY->Set(STRING_NEW("J"), Nan::New<Number>(SDLK_j));
	KEY->Set(STRING_NEW("K"), Nan::New<Number>(SDLK_k));
	KEY->Set(STRING_NEW("L"), Nan::New<Number>(SDLK_l));
	KEY->Set(STRING_NEW("M"), Nan::New<Number>(SDLK_m));
	KEY->Set(STRING_NEW("N"), Nan::New<Number>(SDLK_n));
	KEY->Set(STRING_NEW("O"), Nan::New<Number>(SDLK_o));
	KEY->Set(STRING_NEW("P"), Nan::New<Number>(SDLK_p));
	KEY->Set(STRING_NEW("Q"), Nan::New<Number>(SDLK_q));
	KEY->Set(STRING_NEW("R"), Nan::New<Number>(SDLK_r));
	KEY->Set(STRING_NEW("S"), Nan::New<Number>(SDLK_s));
	KEY->Set(STRING_NEW("T"), Nan::New<Number>(SDLK_t));
	KEY->Set(STRING_NEW("U"), Nan::New<Number>(SDLK_u));
	KEY->Set(STRING_NEW("V"), Nan::New<Number>(SDLK_v));
	KEY->Set(STRING_NEW("W"), Nan::New<Number>(SDLK_w));
	KEY->Set(STRING_NEW("X"), Nan::New<Number>(SDLK_x));
	KEY->Set(STRING_NEW("Y"), Nan::New<Number>(SDLK_y));
	KEY->Set(STRING_NEW("Z"), Nan::New<Number>(SDLK_z));
	KEY->Set(STRING_NEW("DELETE"), Nan::New<Number>(SDLK_DELETE));
	KEY->Set(STRING_NEW("CAPSLOCK"), Nan::New<Number>(SDLK_CAPSLOCK));
	KEY->Set(STRING_NEW("F1"), Nan::New<Number>(SDLK_F1));
	KEY->Set(STRING_NEW("F2"), Nan::New<Number>(SDLK_F2));
	KEY->Set(STRING_NEW("F3"), Nan::New<Number>(SDLK_F3));
	KEY->Set(STRING_NEW("F4"), Nan::New<Number>(SDLK_F4));
	KEY->Set(STRING_NEW("F5"), Nan::New<Number>(SDLK_F5));
	KEY->Set(STRING_NEW("F6"), Nan::New<Number>(SDLK_F6));
	KEY->Set(STRING_NEW("F7"), Nan::New<Number>(SDLK_F7));
	KEY->Set(STRING_NEW("F8"), Nan::New<Number>(SDLK_F8));
	KEY->Set(STRING_NEW("F9"), Nan::New<Number>(SDLK_F9));
	KEY->Set(STRING_NEW("F10"), Nan::New<Number>(SDLK_F10));
	KEY->Set(STRING_NEW("F11"), Nan::New<Number>(SDLK_F11));
	KEY->Set(STRING_NEW("F12"), Nan::New<Number>(SDLK_F12));
	KEY->Set(STRING_NEW("PRINTSCREEN"), Nan::New<Number>(SDLK_PRINTSCREEN));
	KEY->Set(STRING_NEW("SCROLLLOCK"), Nan::New<Number>(SDLK_SCROLLLOCK));
	KEY->Set(STRING_NEW("PAUSE"), Nan::New<Number>(SDLK_PAUSE));
	KEY->Set(STRING_NEW("INSERT"), Nan::New<Number>(SDLK_INSERT));
	KEY->Set(STRING_NEW("HOME"), Nan::New<Number>(SDLK_HOME));
	KEY->Set(STRING_NEW("PAGEUP"), Nan::New<Number>(SDLK_PAGEUP));
	KEY->Set(STRING_NEW("END"), Nan::New<Number>(SDLK_END));
	KEY->Set(STRING_NEW("PAGEDOWN"), Nan::New<Number>(SDLK_PAGEDOWN));
	KEY->Set(STRING_NEW("RIGHT"), Nan::New<Number>(SDLK_RIGHT));
	KEY->Set(STRING_NEW("LEFT"), Nan::New<Number>(SDLK_LEFT));
	KEY->Set(STRING_NEW("DOWN"), Nan::New<Number>(SDLK_DOWN));
	KEY->Set(STRING_NEW("UP"), Nan::New<Number>(SDLK_UP));
	KEY->Set(STRING_NEW("HOME"), Nan::New<Number>(SDLK_HOME));
	KEY->Set(STRING_NEW("NUMLOCKCLEAR"), Nan::New<Number>(SDLK_NUMLOCKCLEAR));
	KEY->Set(STRING_NEW("KP_DIVIDE"), Nan::New<Number>(SDLK_KP_DIVIDE));
	KEY->Set(STRING_NEW("KP_MULTIPLY"), Nan::New<Number>(SDLK_KP_MULTIPLY));
	KEY->Set(STRING_NEW("KP_MINUS"), Nan::New<Number>(SDLK_KP_MINUS));
	KEY->Set(STRING_NEW("KP_PLUS"), Nan::New<Number>(SDLK_KP_PLUS));
	KEY->Set(STRING_NEW("KP_ENTER"), Nan::New<Number>(SDLK_KP_ENTER));
	KEY->Set(STRING_NEW("KP_ONE"), Nan::New<Number>(SDLK_KP_1));
	KEY->Set(STRING_NEW("KP_TWO"), Nan::New<Number>(SDLK_KP_2));
	KEY->Set(STRING_NEW("KP_THREE"), Nan::New<Number>(SDLK_KP_3));
	KEY->Set(STRING_NEW("KP_FOUR"), Nan::New<Number>(SDLK_KP_4));
	KEY->Set(STRING_NEW("KP_FIVE"), Nan::New<Number>(SDLK_KP_5));
	KEY->Set(STRING_NEW("KP_SIX"), Nan::New<Number>(SDLK_KP_6));
	KEY->Set(STRING_NEW("KP_SEVEN"), Nan::New<Number>(SDLK_KP_7));
	KEY->Set(STRING_NEW("KP_EIGHT"), Nan::New<Number>(SDLK_KP_8));
	KEY->Set(STRING_NEW("KP_NINE"), Nan::New<Number>(SDLK_KP_9));
	KEY->Set(STRING_NEW("KP_ZERO"), Nan::New<Number>(SDLK_KP_0));
	KEY->Set(STRING_NEW("KP_PERIOD"), Nan::New<Number>(SDLK_KP_PERIOD));
	KEY->Set(STRING_NEW("APPLICATION"), Nan::New<Number>(SDLK_APPLICATION));
	KEY->Set(STRING_NEW("POWER"), Nan::New<Number>(SDLK_POWER));
	KEY->Set(STRING_NEW("KP_EQUALS"), Nan::New<Number>(SDLK_KP_EQUALS));
	KEY->Set(STRING_NEW("F13"), Nan::New<Number>(SDLK_F13));
	KEY->Set(STRING_NEW("F14"), Nan::New<Number>(SDLK_F14));
	KEY->Set(STRING_NEW("F15"), Nan::New<Number>(SDLK_F15));
	KEY->Set(STRING_NEW("F16"), Nan::New<Number>(SDLK_F16));
	KEY->Set(STRING_NEW("F17"), Nan::New<Number>(SDLK_F17));
	KEY->Set(STRING_NEW("F18"), Nan::New<Number>(SDLK_F18));
	KEY->Set(STRING_NEW("F19"), Nan::New<Number>(SDLK_F19));
	KEY->Set(STRING_NEW("F20"), Nan::New<Number>(SDLK_F20));
	KEY->Set(STRING_NEW("F21"), Nan::New<Number>(SDLK_F21));
	KEY->Set(STRING_NEW("F22"), Nan::New<Number>(SDLK_F22));
	KEY->Set(STRING_NEW("F23"), Nan::New<Number>(SDLK_F23));
	KEY->Set(STRING_NEW("F24"), Nan::New<Number>(SDLK_F24));
	KEY->Set(STRING_NEW("EXECUTE"), Nan::New<Number>(SDLK_EXECUTE));
	KEY->Set(STRING_NEW("HELP"), Nan::New<Number>(SDLK_HELP));
	KEY->Set(STRING_NEW("MENU"), Nan::New<Number>(SDLK_MENU));
	KEY->Set(STRING_NEW("SELECT"), Nan::New<Number>(SDLK_SELECT));
	KEY->Set(STRING_NEW("STOP"), Nan::New<Number>(SDLK_STOP));
	KEY->Set(STRING_NEW("AGAIN"), Nan::New<Number>(SDLK_AGAIN));
	KEY->Set(STRING_NEW("UNDO"), Nan::New<Number>(SDLK_UNDO));
	KEY->Set(STRING_NEW("CUT"), Nan::New<Number>(SDLK_CUT));
	KEY->Set(STRING_NEW("COPY"), Nan::New<Number>(SDLK_COPY));
	KEY->Set(STRING_NEW("PASTE"), Nan::New<Number>(SDLK_PASTE));
	KEY->Set(STRING_NEW("FIND"), Nan::New<Number>(SDLK_FIND));
	KEY->Set(STRING_NEW("MUTE"), Nan::New<Number>(SDLK_MUTE));
	KEY->Set(STRING_NEW("VOLUMEUP"), Nan::New<Number>(SDLK_VOLUMEUP));
	KEY->Set(STRING_NEW("VOLUMEDOWN"), Nan::New<Number>(SDLK_VOLUMEDOWN));
	KEY->Set(STRING_NEW("KP_COMMA"), Nan::New<Number>(SDLK_KP_COMMA));
	KEY->Set(STRING_NEW("KP_EQUALSAS400"), Nan::New<Number>(SDLK_KP_EQUALSAS400));
	KEY->Set(STRING_NEW("ALTERASE"), Nan::New<Number>(SDLK_ALTERASE));
	KEY->Set(STRING_NEW("SYSREQ"), Nan::New<Number>(SDLK_SYSREQ));
	KEY->Set(STRING_NEW("CANCEL"), Nan::New<Number>(SDLK_CANCEL));
	KEY->Set(STRING_NEW("CLEAR"), Nan::New<Number>(SDLK_CLEAR));
	KEY->Set(STRING_NEW("PRIOR"), Nan::New<Number>(SDLK_PRIOR));
	KEY->Set(STRING_NEW("RETURN2"), Nan::New<Number>(SDLK_RETURN2));
	KEY->Set(STRING_NEW("SEPARATOR"), Nan::New<Number>(SDLK_SEPARATOR));
	KEY->Set(STRING_NEW("OUT"), Nan::New<Number>(SDLK_OUT));
	KEY->Set(STRING_NEW("OPER"), Nan::New<Number>(SDLK_OPER));
	KEY->Set(STRING_NEW("CLEARAGAIN"), Nan::New<Number>(SDLK_CLEARAGAIN));
	KEY->Set(STRING_NEW("CRSEL"), Nan::New<Number>(SDLK_CRSEL));
	KEY->Set(STRING_NEW("EXSEL"), Nan::New<Number>(SDLK_EXSEL));
	KEY->Set(STRING_NEW("KP_ZEROZERO"), Nan::New<Number>(SDLK_KP_00));
	KEY->Set(STRING_NEW("KP_ZEROZEROZERO"), Nan::New<Number>(SDLK_KP_000));
	KEY->Set(STRING_NEW("THOUSANDSSEPARATOR"), Nan::New<Number>(SDLK_THOUSANDSSEPARATOR));
	KEY->Set(STRING_NEW("DECIMALSEPARATOR"), Nan::New<Number>(SDLK_DECIMALSEPARATOR));
	KEY->Set(STRING_NEW("CURRENCYUNIT"), Nan::New<Number>(SDLK_CURRENCYUNIT));
	KEY->Set(STRING_NEW("CURRENCYSUBUNIT"), Nan::New<Number>(SDLK_CURRENCYSUBUNIT));
	KEY->Set(STRING_NEW("KP_LEFTPAREN"), Nan::New<Number>(SDLK_KP_LEFTPAREN));
	KEY->Set(STRING_NEW("KP_RIGHTPAREN"), Nan::New<Number>(SDLK_KP_RIGHTPAREN));
	KEY->Set(STRING_NEW("KP_LEFTBRACE"), Nan::New<Number>(SDLK_KP_LEFTBRACE));
	KEY->Set(STRING_NEW("KP_RIGHTBRACE"), Nan::New<Number>(SDLK_KP_RIGHTBRACE));
	KEY->Set(STRING_NEW("KP_TAB"), Nan::New<Number>(SDLK_KP_TAB));
	KEY->Set(STRING_NEW("KP_BACKSPACE"), Nan::New<Number>(SDLK_KP_BACKSPACE));
	KEY->Set(STRING_NEW("KP_A"), Nan::New<Number>(SDLK_KP_A));
	KEY->Set(STRING_NEW("KP_B"), Nan::New<Number>(SDLK_KP_B));
	KEY->Set(STRING_NEW("KP_C"), Nan::New<Number>(SDLK_KP_C));
	KEY->Set(STRING_NEW("KP_D"), Nan::New<Number>(SDLK_KP_D));
	KEY->Set(STRING_NEW("KP_E"), Nan::New<Number>(SDLK_KP_E));
	KEY->Set(STRING_NEW("KP_F"), Nan::New<Number>(SDLK_KP_F));
	KEY->Set(STRING_NEW("KP_XOR"), Nan::New<Number>(SDLK_KP_XOR));
	KEY->Set(STRING_NEW("KP_POWER"), Nan::New<Number>(SDLK_KP_POWER));
	KEY->Set(STRING_NEW("KP_PERCENT"), Nan::New<Number>(SDLK_KP_PERCENT));
	KEY->Set(STRING_NEW("KP_LESS"), Nan::New<Number>(SDLK_KP_LESS));
	KEY->Set(STRING_NEW("KP_GREATER"), Nan::New<Number>(SDLK_KP_GREATER));
	KEY->Set(STRING_NEW("KP_AMPERSAND"), Nan::New<Number>(SDLK_KP_AMPERSAND));
	KEY->Set(STRING_NEW("KP_DBLAMPERSAND"), Nan::New<Number>(SDLK_KP_DBLAMPERSAND));
	KEY->Set(STRING_NEW("KP_VERTICALBAR"), Nan::New<Number>(SDLK_KP_VERTICALBAR));
	KEY->Set(STRING_NEW("KP_DBLVERTICALBAR"), Nan::New<Number>(SDLK_KP_DBLVERTICALBAR));
	KEY->Set(STRING_NEW("KP_COLON"), Nan::New<Number>(SDLK_KP_COLON));
	KEY->Set(STRING_NEW("KP_HASH"), Nan::New<Number>(SDLK_KP_HASH));
	KEY->Set(STRING_NEW("KP_SPACE"), Nan::New<Number>(SDLK_KP_SPACE));
	KEY->Set(STRING_NEW("KP_AT"), Nan::New<Number>(SDLK_KP_AT));
	KEY->Set(STRING_NEW("KP_EXCLAM"), Nan::New<Number>(SDLK_KP_EXCLAM));
	KEY->Set(STRING_NEW("KP_MEMSTORE"), Nan::New<Number>(SDLK_KP_MEMSTORE));
	KEY->Set(STRING_NEW("KP_MEMRECALL"), Nan::New<Number>(SDLK_KP_MEMRECALL));
	KEY->Set(STRING_NEW("KP_MEMCLEAR"), Nan::New<Number>(SDLK_KP_MEMCLEAR));
	KEY->Set(STRING_NEW("KP_MEMADD"), Nan::New<Number>(SDLK_KP_MEMADD));
	KEY->Set(STRING_NEW("KP_MEMSUBTRACT"), Nan::New<Number>(SDLK_KP_MEMSUBTRACT));
	KEY->Set(STRING_NEW("KP_MEMMULTIPLY"), Nan::New<Number>(SDLK_KP_MEMMULTIPLY));
	KEY->Set(STRING_NEW("KP_MEMDIVIDE"), Nan::New<Number>(SDLK_KP_MEMDIVIDE));
	KEY->Set(STRING_NEW("KP_PLUSMINUS"), Nan::New<Number>(SDLK_KP_PLUSMINUS));
	KEY->Set(STRING_NEW("KP_CLEAR"), Nan::New<Number>(SDLK_KP_CLEAR));
	KEY->Set(STRING_NEW("KP_CLEARENTRY"), Nan::New<Number>(SDLK_KP_CLEARENTRY));
	KEY->Set(STRING_NEW("KP_BINARY"), Nan::New<Number>(SDLK_KP_BINARY));
	KEY->Set(STRING_NEW("KP_OCTAL"), Nan::New<Number>(SDLK_KP_OCTAL));
	KEY->Set(STRING_NEW("KP_DECIMAL"), Nan::New<Number>(SDLK_KP_DECIMAL));
	KEY->Set(STRING_NEW("KP_HEXADECIMAL"), Nan::New<Number>(SDLK_KP_HEXADECIMAL));
	KEY->Set(STRING_NEW("LCTRL"), Nan::New<Number>(SDLK_LCTRL));
	KEY->Set(STRING_NEW("LSHIFT"), Nan::New<Number>(SDLK_LSHIFT));
	KEY->Set(STRING_NEW("LALT"), Nan::New<Number>(SDLK_LALT));
	KEY->Set(STRING_NEW("LGUI"), Nan::New<Number>(SDLK_LGUI));
	KEY->Set(STRING_NEW("RCTRL"), Nan::New<Number>(SDLK_RCTRL));
	KEY->Set(STRING_NEW("RSHIFT"), Nan::New<Number>(SDLK_RSHIFT));
	KEY->Set(STRING_NEW("RALT"), Nan::New<Number>(SDLK_RALT));
	KEY->Set(STRING_NEW("RGUI"), Nan::New<Number>(SDLK_RGUI));
	KEY->Set(STRING_NEW("MODE"), Nan::New<Number>(SDLK_MODE));
	KEY->Set(STRING_NEW("AUDIONEXT"), Nan::New<Number>(SDLK_AUDIONEXT));
	KEY->Set(STRING_NEW("AUDIOPREV"), Nan::New<Number>(SDLK_AUDIOPREV));
	KEY->Set(STRING_NEW("AUDIOSTOP"), Nan::New<Number>(SDLK_AUDIOSTOP));
	KEY->Set(STRING_NEW("AUDIOPLAY"), Nan::New<Number>(SDLK_AUDIOPLAY));
	KEY->Set(STRING_NEW("AUDIOMUTE"), Nan::New<Number>(SDLK_AUDIOMUTE));
	KEY->Set(STRING_NEW("MEDIASELECT"), Nan::New<Number>(SDLK_MEDIASELECT));
	KEY->Set(STRING_NEW("WWW"), Nan::New<Number>(SDLK_WWW));
	KEY->Set(STRING_NEW("MAIL"), Nan::New<Number>(SDLK_MAIL));
	KEY->Set(STRING_NEW("CALCULATOR"), Nan::New<Number>(SDLK_CALCULATOR));
	KEY->Set(STRING_NEW("COMPUTER"), Nan::New<Number>(SDLK_COMPUTER));
	KEY->Set(STRING_NEW("AC_SEARCH"), Nan::New<Number>(SDLK_AC_SEARCH));
	KEY->Set(STRING_NEW("AC_HOME"), Nan::New<Number>(SDLK_AC_HOME));
	KEY->Set(STRING_NEW("AC_BACK"), Nan::New<Number>(SDLK_AC_BACK));
	KEY->Set(STRING_NEW("AC_FORWARD"), Nan::New<Number>(SDLK_AC_FORWARD));
	KEY->Set(STRING_NEW("AC_STOP"), Nan::New<Number>(SDLK_AC_STOP));
	KEY->Set(STRING_NEW("AC_REFRESH"), Nan::New<Number>(SDLK_AC_REFRESH));
	KEY->Set(STRING_NEW("AC_BOOKMARKS"), Nan::New<Number>(SDLK_AC_BOOKMARKS));
	KEY->Set(STRING_NEW("BRIGHTNESSDOWN"), Nan::New<Number>(SDLK_BRIGHTNESSDOWN));
	KEY->Set(STRING_NEW("BRIGHTNESSUP"), Nan::New<Number>(SDLK_BRIGHTNESSUP));
	KEY->Set(STRING_NEW("DISPLAYSWITCH"), Nan::New<Number>(SDLK_DISPLAYSWITCH));
	KEY->Set(STRING_NEW("KBDILLUMTOGGLE"), Nan::New<Number>(SDLK_KBDILLUMTOGGLE));
	KEY->Set(STRING_NEW("KBDILLUMDOWN"), Nan::New<Number>(SDLK_KBDILLUMDOWN));
	KEY->Set(STRING_NEW("KBDILLUMUP"), Nan::New<Number>(SDLK_KBDILLUMUP));
	KEY->Set(STRING_NEW("EJECT"), Nan::New<Number>(SDLK_EJECT));
	KEY->Set(STRING_NEW("SLEEP"), Nan::New<Number>(SDLK_SLEEP));

	Handle<Object> SCANCODE = Nan::New<Object>();
	Nan::Set(target, STRING_NEW("SCANCODE"), SCANCODE);
	// Keys are set in the order that they are listed on this page:
	//  http://wiki.libsdl.org/SDLScancodeLookup
	SCANCODE->Set(STRING_NEW("UNKNOWN"), Nan::New<Number>(SDL_SCANCODE_UNKNOWN));
	SCANCODE->Set(STRING_NEW("A"), Nan::New<Number>(SDL_SCANCODE_A));
	SCANCODE->Set(STRING_NEW("B"), Nan::New<Number>(SDL_SCANCODE_B));
	SCANCODE->Set(STRING_NEW("C"), Nan::New<Number>(SDL_SCANCODE_C));
	SCANCODE->Set(STRING_NEW("D"), Nan::New<Number>(SDL_SCANCODE_D));
	SCANCODE->Set(STRING_NEW("E"), Nan::New<Number>(SDL_SCANCODE_E));
	SCANCODE->Set(STRING_NEW("F"), Nan::New<Number>(SDL_SCANCODE_F));
	SCANCODE->Set(STRING_NEW("G"), Nan::New<Number>(SDL_SCANCODE_G));
	SCANCODE->Set(STRING_NEW("H"), Nan::New<Number>(SDL_SCANCODE_H));
	SCANCODE->Set(STRING_NEW("I"), Nan::New<Number>(SDL_SCANCODE_I));
	SCANCODE->Set(STRING_NEW("J"), Nan::New<Number>(SDL_SCANCODE_J));
	SCANCODE->Set(STRING_NEW("K"), Nan::New<Number>(SDL_SCANCODE_K));
	SCANCODE->Set(STRING_NEW("L"), Nan::New<Number>(SDL_SCANCODE_L));
	SCANCODE->Set(STRING_NEW("M"), Nan::New<Number>(SDL_SCANCODE_M));
	SCANCODE->Set(STRING_NEW("N"), Nan::New<Number>(SDL_SCANCODE_N));
	SCANCODE->Set(STRING_NEW("O"), Nan::New<Number>(SDL_SCANCODE_O));
	SCANCODE->Set(STRING_NEW("P"), Nan::New<Number>(SDL_SCANCODE_P));
	SCANCODE->Set(STRING_NEW("Q"), Nan::New<Number>(SDL_SCANCODE_Q));
	SCANCODE->Set(STRING_NEW("R"), Nan::New<Number>(SDL_SCANCODE_R));
	SCANCODE->Set(STRING_NEW("S"), Nan::New<Number>(SDL_SCANCODE_S));
	SCANCODE->Set(STRING_NEW("T"), Nan::New<Number>(SDL_SCANCODE_T));
	SCANCODE->Set(STRING_NEW("U"), Nan::New<Number>(SDL_SCANCODE_U));
	SCANCODE->Set(STRING_NEW("V"), Nan::New<Number>(SDL_SCANCODE_V));
	SCANCODE->Set(STRING_NEW("W"), Nan::New<Number>(SDL_SCANCODE_W));
	SCANCODE->Set(STRING_NEW("X"), Nan::New<Number>(SDL_SCANCODE_X));
	SCANCODE->Set(STRING_NEW("Y"), Nan::New<Number>(SDL_SCANCODE_Y));
	SCANCODE->Set(STRING_NEW("ONE"), Nan::New<Number>(SDL_SCANCODE_1));
	SCANCODE->Set(STRING_NEW("TWO"), Nan::New<Number>(SDL_SCANCODE_2));
	SCANCODE->Set(STRING_NEW("THREE"), Nan::New<Number>(SDL_SCANCODE_3));
	SCANCODE->Set(STRING_NEW("FOUR"), Nan::New<Number>(SDL_SCANCODE_4));
	SCANCODE->Set(STRING_NEW("FIVE"), Nan::New<Number>(SDL_SCANCODE_5));
	SCANCODE->Set(STRING_NEW("SIX"), Nan::New<Number>(SDL_SCANCODE_6));
	SCANCODE->Set(STRING_NEW("SEVEN"), Nan::New<Number>(SDL_SCANCODE_7));
	SCANCODE->Set(STRING_NEW("EIGHT"), Nan::New<Number>(SDL_SCANCODE_8));
	SCANCODE->Set(STRING_NEW("NINE"), Nan::New<Number>(SDL_SCANCODE_9));
	SCANCODE->Set(STRING_NEW("ZERO"), Nan::New<Number>(SDL_SCANCODE_0));
	SCANCODE->Set(STRING_NEW("RETURN"), Nan::New<Number>(SDL_SCANCODE_RETURN));
	SCANCODE->Set(STRING_NEW("BACKSPACE"), Nan::New<Number>(SDL_SCANCODE_BACKSPACE));
	SCANCODE->Set(STRING_NEW("TAB"), Nan::New<Number>(SDL_SCANCODE_TAB));
	SCANCODE->Set(STRING_NEW("SPACE"), Nan::New<Number>(SDL_SCANCODE_SPACE));
	SCANCODE->Set(STRING_NEW("MINUS"), Nan::New<Number>(SDL_SCANCODE_MINUS));
	SCANCODE->Set(STRING_NEW("EQUALS"), Nan::New<Number>(SDL_SCANCODE_EQUALS));
	SCANCODE->Set(STRING_NEW("LEFTBRACKET"), Nan::New<Number>(SDL_SCANCODE_LEFTBRACKET));
	SCANCODE->Set(STRING_NEW("RIGHTBRACKET"), Nan::New<Number>(SDL_SCANCODE_RIGHTBRACKET));
	SCANCODE->Set(STRING_NEW("BACKSLASH"), Nan::New<Number>(SDL_SCANCODE_BACKSLASH));
	SCANCODE->Set(STRING_NEW("NONUSHASH"), Nan::New<Number>(SDL_SCANCODE_NONUSHASH));
	SCANCODE->Set(STRING_NEW("SEMICOLON"), Nan::New<Number>(SDL_SCANCODE_SEMICOLON));
	SCANCODE->Set(STRING_NEW("APOSTROPHE"), Nan::New<Number>(SDL_SCANCODE_APOSTROPHE));
	SCANCODE->Set(STRING_NEW("GRAVE"), Nan::New<Number>(SDL_SCANCODE_GRAVE));
	SCANCODE->Set(STRING_NEW("COMMA"), Nan::New<Number>(SDL_SCANCODE_COMMA));
	SCANCODE->Set(STRING_NEW("PERIOD"), Nan::New<Number>(SDL_SCANCODE_PERIOD));
	SCANCODE->Set(STRING_NEW("SLASH"), Nan::New<Number>(SDL_SCANCODE_SLASH));
	SCANCODE->Set(STRING_NEW("CAPSLOCK"), Nan::New<Number>(SDL_SCANCODE_CAPSLOCK));
	SCANCODE->Set(STRING_NEW("F1"), Nan::New<Number>(SDL_SCANCODE_F1));
	SCANCODE->Set(STRING_NEW("F2"), Nan::New<Number>(SDL_SCANCODE_F2));
	SCANCODE->Set(STRING_NEW("F3"), Nan::New<Number>(SDL_SCANCODE_F3));
	SCANCODE->Set(STRING_NEW("F4"), Nan::New<Number>(SDL_SCANCODE_F4));
	SCANCODE->Set(STRING_NEW("F5"), Nan::New<Number>(SDL_SCANCODE_F5));
	SCANCODE->Set(STRING_NEW("F6"), Nan::New<Number>(SDL_SCANCODE_F6));
	SCANCODE->Set(STRING_NEW("F7"), Nan::New<Number>(SDL_SCANCODE_F7));
	SCANCODE->Set(STRING_NEW("F8"), Nan::New<Number>(SDL_SCANCODE_F8));
	SCANCODE->Set(STRING_NEW("F9"), Nan::New<Number>(SDL_SCANCODE_F9));
	SCANCODE->Set(STRING_NEW("F10"), Nan::New<Number>(SDL_SCANCODE_F10));
	SCANCODE->Set(STRING_NEW("F11"), Nan::New<Number>(SDL_SCANCODE_F11));
	SCANCODE->Set(STRING_NEW("F12"), Nan::New<Number>(SDL_SCANCODE_F12));
	SCANCODE->Set(STRING_NEW("PRINTSCREEN"), Nan::New<Number>(SDL_SCANCODE_PRINTSCREEN));
	SCANCODE->Set(STRING_NEW("SCROLLLOCK"), Nan::New<Number>(SDL_SCANCODE_SCROLLLOCK));
	SCANCODE->Set(STRING_NEW("PAUSE"), Nan::New<Number>(SDL_SCANCODE_PAUSE));
	SCANCODE->Set(STRING_NEW("INSERT"), Nan::New<Number>(SDL_SCANCODE_INSERT));
	SCANCODE->Set(STRING_NEW("HOME"), Nan::New<Number>(SDL_SCANCODE_HOME));
	SCANCODE->Set(STRING_NEW("PAGEUP"), Nan::New<Number>(SDL_SCANCODE_PAGEUP));
	SCANCODE->Set(STRING_NEW("DELETE"), Nan::New<Number>(SDL_SCANCODE_DELETE));
	SCANCODE->Set(STRING_NEW("END"), Nan::New<Number>(SDL_SCANCODE_END));
	SCANCODE->Set(STRING_NEW("PAGEDOWN"), Nan::New<Number>(SDL_SCANCODE_PAGEDOWN));
	SCANCODE->Set(STRING_NEW("RIGHT"), Nan::New<Number>(SDL_SCANCODE_RIGHT));
	SCANCODE->Set(STRING_NEW("LEFT"), Nan::New<Number>(SDL_SCANCODE_LEFT));
	SCANCODE->Set(STRING_NEW("DOWN"), Nan::New<Number>(SDL_SCANCODE_DOWN));
	SCANCODE->Set(STRING_NEW("UP"), Nan::New<Number>(SDL_SCANCODE_UP));
	SCANCODE->Set(STRING_NEW("NUMLOCKCLEAR"), Nan::New<Number>(SDL_SCANCODE_NUMLOCKCLEAR));
	SCANCODE->Set(STRING_NEW("KP_DIVIDE"), Nan::New<Number>(SDL_SCANCODE_KP_DIVIDE));
	SCANCODE->Set(STRING_NEW("KP_MULTIPLY"), Nan::New<Number>(SDL_SCANCODE_KP_MULTIPLY));
	SCANCODE->Set(STRING_NEW("KP_MINUS"), Nan::New<Number>(SDL_SCANCODE_KP_MINUS));
	SCANCODE->Set(STRING_NEW("KP_PLUS"), Nan::New<Number>(SDL_SCANCODE_KP_ENTER));
	SCANCODE->Set(STRING_NEW("KP_ONE"), Nan::New<Number>(SDL_SCANCODE_KP_1));
	SCANCODE->Set(STRING_NEW("KP_TWO"), Nan::New<Number>(SDL_SCANCODE_KP_2));
	SCANCODE->Set(STRING_NEW("KP_THREE"), Nan::New<Number>(SDL_SCANCODE_KP_3));
	SCANCODE->Set(STRING_NEW("KP_FOUR"), Nan::New<Number>(SDL_SCANCODE_KP_4));
	SCANCODE->Set(STRING_NEW("KP_FIVE"), Nan::New<Number>(SDL_SCANCODE_KP_5));
	SCANCODE->Set(STRING_NEW("KP_SIX"), Nan::New<Number>(SDL_SCANCODE_KP_6));
	SCANCODE->Set(STRING_NEW("KP_SEVEN"), Nan::New<Number>(SDL_SCANCODE_KP_7));
	SCANCODE->Set(STRING_NEW("KP_EIGHT"), Nan::New<Number>(SDL_SCANCODE_KP_8));
	SCANCODE->Set(STRING_NEW("KP_NINE"), Nan::New<Number>(SDL_SCANCODE_KP_9));
	SCANCODE->Set(STRING_NEW("KP_ZERO"), Nan::New<Number>(SDL_SCANCODE_KP_0));
	SCANCODE->Set(STRING_NEW("KP_PERIOD"), Nan::New<Number>(SDL_SCANCODE_KP_PERIOD));
	SCANCODE->Set(STRING_NEW("NONUSHBACKSLASH"), Nan::New<Number>(SDL_SCANCODE_NONUSBACKSLASH));
	SCANCODE->Set(STRING_NEW("APPLICATION"), Nan::New<Number>(SDL_SCANCODE_APPLICATION));
	SCANCODE->Set(STRING_NEW("POWER"), Nan::New<Number>(SDL_SCANCODE_POWER));
	SCANCODE->Set(STRING_NEW("KP_EQUALS"), Nan::New<Number>(SDL_SCANCODE_KP_EQUALS));
	SCANCODE->Set(STRING_NEW("F13"), Nan::New<Number>(SDL_SCANCODE_F13));
	SCANCODE->Set(STRING_NEW("F14"), Nan::New<Number>(SDL_SCANCODE_F14));
	SCANCODE->Set(STRING_NEW("F15"), Nan::New<Number>(SDL_SCANCODE_F15));
	SCANCODE->Set(STRING_NEW("F16"), Nan::New<Number>(SDL_SCANCODE_F16));
	SCANCODE->Set(STRING_NEW("F17"), Nan::New<Number>(SDL_SCANCODE_F17));
	SCANCODE->Set(STRING_NEW("F18"), Nan::New<Number>(SDL_SCANCODE_F18));
	SCANCODE->Set(STRING_NEW("F19"), Nan::New<Number>(SDL_SCANCODE_F19));
	SCANCODE->Set(STRING_NEW("F20"), Nan::New<Number>(SDL_SCANCODE_F20));
	SCANCODE->Set(STRING_NEW("F21"), Nan::New<Number>(SDL_SCANCODE_F21));
	SCANCODE->Set(STRING_NEW("F22"), Nan::New<Number>(SDL_SCANCODE_F22));
	SCANCODE->Set(STRING_NEW("F23"), Nan::New<Number>(SDL_SCANCODE_F23));
	SCANCODE->Set(STRING_NEW("F24"), Nan::New<Number>(SDL_SCANCODE_F24));
	SCANCODE->Set(STRING_NEW("EXECUTE"), Nan::New<Number>(SDL_SCANCODE_EXECUTE));
	SCANCODE->Set(STRING_NEW("HELP"), Nan::New<Number>(SDL_SCANCODE_HELP));
	SCANCODE->Set(STRING_NEW("MENU"), Nan::New<Number>(SDL_SCANCODE_MENU));
	SCANCODE->Set(STRING_NEW("SELECT"), Nan::New<Number>(SDL_SCANCODE_SELECT));
	SCANCODE->Set(STRING_NEW("STOP"), Nan::New<Number>(SDL_SCANCODE_STOP));
	SCANCODE->Set(STRING_NEW("AGAIN"), Nan::New<Number>(SDL_SCANCODE_AGAIN));
	SCANCODE->Set(STRING_NEW("UNDO"), Nan::New<Number>(SDL_SCANCODE_UNDO));
	SCANCODE->Set(STRING_NEW("CUT"), Nan::New<Number>(SDL_SCANCODE_CUT));
	SCANCODE->Set(STRING_NEW("COPY"), Nan::New<Number>(SDL_SCANCODE_COPY));
	SCANCODE->Set(STRING_NEW("PASTE"), Nan::New<Number>(SDL_SCANCODE_PASTE));
	SCANCODE->Set(STRING_NEW("FIND"), Nan::New<Number>(SDL_SCANCODE_FIND));
	SCANCODE->Set(STRING_NEW("MUTE"), Nan::New<Number>(SDL_SCANCODE_MUTE));
	SCANCODE->Set(STRING_NEW("VOLUMEUP"), Nan::New<Number>(SDL_SCANCODE_VOLUMEUP));
	SCANCODE->Set(STRING_NEW("VOLUMEDOWN"), Nan::New<Number>(SDL_SCANCODE_VOLUMEDOWN));
	// For some reason, these are defined in the lookup table but don't exist in a header?
	// SCANCODE->Set(STRING_NEW("LOCKINGCAPSLOCK"), Nan::New<Number>(SDL_SCANCODE_LOCKINGCAPSLOCK));
	// SCANCODE->Set(STRING_NEW("LOCKINGNUMLOCK"), Nan::New<Number>(SDL_SCANCODE_LOCKINGNUMLOCK));
	// SCANCODE->Set(STRING_NEW("LOCKINGSCROLLLOCK"), Nan::New<Number>(SDL_SCANCODE_LOCKINGSCROLLLOCK));
	SCANCODE->Set(STRING_NEW("KP_COMMA"), Nan::New<Number>(SDL_SCANCODE_KP_COMMA));
	SCANCODE->Set(STRING_NEW("KP_EQUALSAS400"), Nan::New<Number>(SDL_SCANCODE_KP_EQUALSAS400));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL1"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL1));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL2"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL2));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL3"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL3));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL4"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL4));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL5"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL5));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL6"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL6));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL7"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL7));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL8"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL8));
	SCANCODE->Set(STRING_NEW("INTERNATIONAL9"), Nan::New<Number>(SDL_SCANCODE_INTERNATIONAL9));
	SCANCODE->Set(STRING_NEW("LANG1"), Nan::New<Number>(SDL_SCANCODE_LANG1));
	SCANCODE->Set(STRING_NEW("LANG2"), Nan::New<Number>(SDL_SCANCODE_LANG2));
	SCANCODE->Set(STRING_NEW("LANG3"), Nan::New<Number>(SDL_SCANCODE_LANG3));
	SCANCODE->Set(STRING_NEW("LANG4"), Nan::New<Number>(SDL_SCANCODE_LANG4));
	SCANCODE->Set(STRING_NEW("LANG5"), Nan::New<Number>(SDL_SCANCODE_LANG5));
	SCANCODE->Set(STRING_NEW("LANG6"), Nan::New<Number>(SDL_SCANCODE_LANG6));
	SCANCODE->Set(STRING_NEW("LANG7"), Nan::New<Number>(SDL_SCANCODE_LANG7));
	SCANCODE->Set(STRING_NEW("LANG8"), Nan::New<Number>(SDL_SCANCODE_LANG8));
	SCANCODE->Set(STRING_NEW("LANG9"), Nan::New<Number>(SDL_SCANCODE_LANG9));
	SCANCODE->Set(STRING_NEW("ALTERASE"), Nan::New<Number>(SDL_SCANCODE_ALTERASE));
	SCANCODE->Set(STRING_NEW("SYSREQ"), Nan::New<Number>(SDL_SCANCODE_SYSREQ));
	SCANCODE->Set(STRING_NEW("CANCEL"), Nan::New<Number>(SDL_SCANCODE_CANCEL));
	SCANCODE->Set(STRING_NEW("CLEAR"), Nan::New<Number>(SDL_SCANCODE_CLEAR));
	SCANCODE->Set(STRING_NEW("PRIOR"), Nan::New<Number>(SDL_SCANCODE_PRIOR));
	SCANCODE->Set(STRING_NEW("RETURN2"), Nan::New<Number>(SDL_SCANCODE_RETURN2));
	SCANCODE->Set(STRING_NEW("SEPARATOR"), Nan::New<Number>(SDL_SCANCODE_SEPARATOR));
	SCANCODE->Set(STRING_NEW("OUT"), Nan::New<Number>(SDL_SCANCODE_OUT));
	SCANCODE->Set(STRING_NEW("OPER"), Nan::New<Number>(SDL_SCANCODE_OPER));
	SCANCODE->Set(STRING_NEW("CLEARAGAIN"), Nan::New<Number>(SDL_SCANCODE_CLEARAGAIN));
	SCANCODE->Set(STRING_NEW("CRSEL"), Nan::New<Number>(SDL_SCANCODE_CRSEL));
	SCANCODE->Set(STRING_NEW("EXSEL"), Nan::New<Number>(SDL_SCANCODE_EXSEL));
	SCANCODE->Set(STRING_NEW("KP_ZEROZERO"), Nan::New<Number>(SDL_SCANCODE_KP_00));
	SCANCODE->Set(STRING_NEW("KP_ZEROZEROZERO"), Nan::New<Number>(SDL_SCANCODE_KP_000));
	SCANCODE->Set(STRING_NEW("THOUSANDSSEPARATOR"), Nan::New<Number>(SDL_SCANCODE_THOUSANDSSEPARATOR));
	SCANCODE->Set(STRING_NEW("DECIMALSEPARATOR"), Nan::New<Number>(SDL_SCANCODE_DECIMALSEPARATOR));
	SCANCODE->Set(STRING_NEW("CURRENCYUNIT"), Nan::New<Number>(SDL_SCANCODE_CURRENCYUNIT));
	SCANCODE->Set(STRING_NEW("CURRENCYSUBUNIT"), Nan::New<Number>(SDL_SCANCODE_CURRENCYSUBUNIT));
	SCANCODE->Set(STRING_NEW("KP_LEFTPAREN"), Nan::New<Number>(SDL_SCANCODE_KP_LEFTPAREN));
	SCANCODE->Set(STRING_NEW("KP_RIGHTPAREN"), Nan::New<Number>(SDL_SCANCODE_KP_RIGHTPAREN));
	SCANCODE->Set(STRING_NEW("KP_LEFTBRACE"), Nan::New<Number>(SDL_SCANCODE_KP_LEFTBRACE));
	SCANCODE->Set(STRING_NEW("KP_RIGHTBRACE"), Nan::New<Number>(SDL_SCANCODE_KP_RIGHTBRACE));
	SCANCODE->Set(STRING_NEW("KP_TAB"), Nan::New<Number>(SDL_SCANCODE_KP_TAB));
	SCANCODE->Set(STRING_NEW("KP_BACKSPACE"), Nan::New<Number>(SDL_SCANCODE_KP_BACKSPACE));
	SCANCODE->Set(STRING_NEW("KP_A"), Nan::New<Number>(SDL_SCANCODE_KP_A));
	SCANCODE->Set(STRING_NEW("KP_B"), Nan::New<Number>(SDL_SCANCODE_KP_D));
	SCANCODE->Set(STRING_NEW("KP_C"), Nan::New<Number>(SDL_SCANCODE_KP_C));
	SCANCODE->Set(STRING_NEW("KP_D"), Nan::New<Number>(SDL_SCANCODE_KP_D));
	SCANCODE->Set(STRING_NEW("KP_E"), Nan::New<Number>(SDL_SCANCODE_KP_E));
	SCANCODE->Set(STRING_NEW("KP_F"), Nan::New<Number>(SDL_SCANCODE_KP_F));
	SCANCODE->Set(STRING_NEW("KP_XOR"), Nan::New<Number>(SDL_SCANCODE_KP_XOR));
	SCANCODE->Set(STRING_NEW("KP_POWER"), Nan::New<Number>(SDL_SCANCODE_KP_POWER));
	SCANCODE->Set(STRING_NEW("KP_PERCENT"), Nan::New<Number>(SDL_SCANCODE_KP_PERCENT));
	SCANCODE->Set(STRING_NEW("KP_LESS"), Nan::New<Number>(SDL_SCANCODE_KP_LESS));
	SCANCODE->Set(STRING_NEW("KP_GREATER"), Nan::New<Number>(SDL_SCANCODE_KP_GREATER));
	SCANCODE->Set(STRING_NEW("KP_AMPERSAND"), Nan::New<Number>(SDL_SCANCODE_KP_AMPERSAND));
	SCANCODE->Set(STRING_NEW("KP_DBLAMPERSAND"), Nan::New<Number>(SDL_SCANCODE_KP_DBLAMPERSAND));
	SCANCODE->Set(STRING_NEW("KP_VERTICALBAR"), Nan::New<Number>(SDL_SCANCODE_KP_VERTICALBAR));
	SCANCODE->Set(STRING_NEW("KP_DBLVERTICALBAR"), Nan::New<Number>(SDL_SCANCODE_KP_DBLVERTICALBAR));
	SCANCODE->Set(STRING_NEW("KP_COLON"), Nan::New<Number>(SDL_SCANCODE_KP_COLON));
	SCANCODE->Set(STRING_NEW("KP_HASH"), Nan::New<Number>(SDL_SCANCODE_KP_HASH));
	SCANCODE->Set(STRING_NEW("KP_SPACE"), Nan::New<Number>(SDL_SCANCODE_KP_SPACE));
	SCANCODE->Set(STRING_NEW("KP_AT"), Nan::New<Number>(SDL_SCANCODE_KP_AT));
	SCANCODE->Set(STRING_NEW("KP_EXCLAM"), Nan::New<Number>(SDL_SCANCODE_KP_EXCLAM));
	SCANCODE->Set(STRING_NEW("KP_MEMSTORE"), Nan::New<Number>(SDL_SCANCODE_KP_MEMSTORE));
	SCANCODE->Set(STRING_NEW("KP_MEMRECALL"), Nan::New<Number>(SDL_SCANCODE_KP_MEMRECALL));
	SCANCODE->Set(STRING_NEW("KP_MEMCLEAR"), Nan::New<Number>(SDL_SCANCODE_KP_MEMCLEAR));
	SCANCODE->Set(STRING_NEW("KP_MEMADD"), Nan::New<Number>(SDL_SCANCODE_KP_MEMADD));
	SCANCODE->Set(STRING_NEW("KP_MEMSUBTRACT"), Nan::New<Number>(SDL_SCANCODE_KP_MEMSUBTRACT));
	SCANCODE->Set(STRING_NEW("KP_MEMMULTIPLY"), Nan::New<Number>(SDL_SCANCODE_KP_MEMMULTIPLY));
	SCANCODE->Set(STRING_NEW("KP_MEMDIVIDE"), Nan::New<Number>(SDL_SCANCODE_KP_MEMDIVIDE));
	SCANCODE->Set(STRING_NEW("KP_PLUSMINUS"), Nan::New<Number>(SDL_SCANCODE_KP_PLUSMINUS));
	SCANCODE->Set(STRING_NEW("KP_CLEAR"), Nan::New<Number>(SDL_SCANCODE_KP_CLEAR));
	SCANCODE->Set(STRING_NEW("KP_CLEARENTRY"), Nan::New<Number>(SDL_SCANCODE_KP_CLEARENTRY));
	SCANCODE->Set(STRING_NEW("KP_BINARY"), Nan::New<Number>(SDL_SCANCODE_KP_BINARY));
	SCANCODE->Set(STRING_NEW("KP_OCTAL"), Nan::New<Number>(SDL_SCANCODE_KP_OCTAL));
	SCANCODE->Set(STRING_NEW("KP_DECIMAL"), Nan::New<Number>(SDL_SCANCODE_KP_DECIMAL));
	SCANCODE->Set(STRING_NEW("KP_HEXADECIMAL"), Nan::New<Number>(SDL_SCANCODE_KP_HEXADECIMAL));
	SCANCODE->Set(STRING_NEW("LCTRL"), Nan::New<Number>(SDL_SCANCODE_LCTRL));
	SCANCODE->Set(STRING_NEW("LSHIFT"), Nan::New<Number>(SDL_SCANCODE_LSHIFT));
	SCANCODE->Set(STRING_NEW("LALT"), Nan::New<Number>(SDL_SCANCODE_LALT));
	SCANCODE->Set(STRING_NEW("LGUI"), Nan::New<Number>(SDL_SCANCODE_LGUI));
	SCANCODE->Set(STRING_NEW("RCTRL"), Nan::New<Number>(SDL_SCANCODE_RCTRL));
	SCANCODE->Set(STRING_NEW("RSHIFT"), Nan::New<Number>(SDL_SCANCODE_RSHIFT));
	SCANCODE->Set(STRING_NEW("RALT"), Nan::New<Number>(SDL_SCANCODE_RALT));
	SCANCODE->Set(STRING_NEW("RGUI"), Nan::New<Number>(SDL_SCANCODE_RGUI));
	SCANCODE->Set(STRING_NEW("MODE"), Nan::New<Number>(SDL_SCANCODE_MODE));
	SCANCODE->Set(STRING_NEW("AUDIONEXT"), Nan::New<Number>(SDL_SCANCODE_AUDIONEXT));
	SCANCODE->Set(STRING_NEW("AUDIOPREV"), Nan::New<Number>(SDL_SCANCODE_AUDIOPREV));
	SCANCODE->Set(STRING_NEW("AUDIOSTOP"), Nan::New<Number>(SDL_SCANCODE_AUDIOSTOP));
	SCANCODE->Set(STRING_NEW("AUDIOPLAY"), Nan::New<Number>(SDL_SCANCODE_AUDIOPLAY));
	SCANCODE->Set(STRING_NEW("AUDIOMUTE"), Nan::New<Number>(SDL_SCANCODE_AUDIOMUTE));
	SCANCODE->Set(STRING_NEW("MEDIASELECT"), Nan::New<Number>(SDL_SCANCODE_MEDIASELECT));
	SCANCODE->Set(STRING_NEW("WWW"), Nan::New<Number>(SDL_SCANCODE_WWW));
	SCANCODE->Set(STRING_NEW("MAIL"), Nan::New<Number>(SDL_SCANCODE_MAIL));
	SCANCODE->Set(STRING_NEW("CALCULATOR"), Nan::New<Number>(SDL_SCANCODE_CALCULATOR));
	SCANCODE->Set(STRING_NEW("COMPUTER"), Nan::New<Number>(SDL_SCANCODE_COMPUTER));
	SCANCODE->Set(STRING_NEW("AC_SEARCH"), Nan::New<Number>(SDL_SCANCODE_AC_SEARCH));
	SCANCODE->Set(STRING_NEW("AC_HOME"), Nan::New<Number>(SDL_SCANCODE_AC_HOME));
	SCANCODE->Set(STRING_NEW("AC_BACK"), Nan::New<Number>(SDL_SCANCODE_AC_BACK));
	SCANCODE->Set(STRING_NEW("AC_FORWARD"), Nan::New<Number>(SDL_SCANCODE_AC_FORWARD));
	SCANCODE->Set(STRING_NEW("AC_STOP"), Nan::New<Number>(SDL_SCANCODE_AC_STOP));
	SCANCODE->Set(STRING_NEW("AC_REFRESH"), Nan::New<Number>(SDL_SCANCODE_AC_REFRESH));
	SCANCODE->Set(STRING_NEW("AC_BOOKMARKS"), Nan::New<Number>(SDL_SCANCODE_AC_BOOKMARKS));
	SCANCODE->Set(STRING_NEW("BRIGHTNESSDOWN"), Nan::New<Number>(SDL_SCANCODE_BRIGHTNESSDOWN));
	SCANCODE->Set(STRING_NEW("BRIGHTNESSUP"), Nan::New<Number>(SDL_SCANCODE_BRIGHTNESSUP));
	SCANCODE->Set(STRING_NEW("DISPLAYSWITCH"), Nan::New<Number>(SDL_SCANCODE_DISPLAYSWITCH));
	SCANCODE->Set(STRING_NEW("KBDILLUMTOGGLE"), Nan::New<Number>(SDL_SCANCODE_KBDILLUMTOGGLE));
	SCANCODE->Set(STRING_NEW("KBDILLUMDOWN"), Nan::New<Number>(SDL_SCANCODE_KBDILLUMDOWN));
	SCANCODE->Set(STRING_NEW("KBDILLUMUP"), Nan::New<Number>(SDL_SCANCODE_KBDILLUMUP));
	SCANCODE->Set(STRING_NEW("EJECT"), Nan::New<Number>(SDL_SCANCODE_EJECT));
	SCANCODE->Set(STRING_NEW("SLEEP"), Nan::New<Number>(SDL_SCANCODE_SLEEP));

	Handle<Object> KMOD = Nan::New<Object>();
	Nan::Set(target, STRING_NEW("KMOD"), KMOD);
	KMOD->Set(STRING_NEW("NONE"), Nan::New<Number>(KMOD_NONE));
	KMOD->Set(STRING_NEW("LSHIFT"), Nan::New<Number>(KMOD_LSHIFT));
	KMOD->Set(STRING_NEW("RSHIFT"), Nan::New<Number>(KMOD_RSHIFT));
	KMOD->Set(STRING_NEW("LCTRL"), Nan::New<Number>(KMOD_LCTRL));
	KMOD->Set(STRING_NEW("RCTRL"), Nan::New<Number>(KMOD_RCTRL));
	KMOD->Set(STRING_NEW("LALT"), Nan::New<Number>(KMOD_LALT));
	KMOD->Set(STRING_NEW("RALT"), Nan::New<Number>(KMOD_RALT));
	KMOD->Set(STRING_NEW("LGUI"), Nan::New<Number>(KMOD_LGUI));
	KMOD->Set(STRING_NEW("RGUI"), Nan::New<Number>(KMOD_RGUI));
	KMOD->Set(STRING_NEW("NUM"), Nan::New<Number>(KMOD_NUM));
	KMOD->Set(STRING_NEW("CAPS"), Nan::New<Number>(KMOD_CAPS));
	KMOD->Set(STRING_NEW("MODE"), Nan::New<Number>(KMOD_MODE));
	KMOD->Set(STRING_NEW("CTRL"), Nan::New<Number>(KMOD_CTRL));
	KMOD->Set(STRING_NEW("SHIFT"), Nan::New<Number>(KMOD_SHIFT));
	KMOD->Set(STRING_NEW("ALT"), Nan::New<Number>(KMOD_ALT));
	KMOD->Set(STRING_NEW("GUI"), Nan::New<Number>(KMOD_GUI));

	Nan::Export(target, "getKeyFromName", GetKeyFromName);
	Nan::Export(target, "getKeyFromScancode", GetKeyFromScancode);
	Nan::Export(target, "getKeyName", GetKeyName);

	Nan::Export(target, "getScancodeFromKey", GetScancodeFromKey);
	Nan::Export(target, "getScancodeFromName", GetScancodeFromName);
	Nan::Export(target, "getScancodeName", GetScancodeName);

	Nan::Export(target, "hasScreenKeyboardSupport", HasScreenKeyboardSupport);
	Nan::Export(target, "isScreenKeyboardShown", IsScreenKeyboardShown);

	Nan::Export(target, "getKeyboardFocus", GetKeyboardFocus);
	Nan::Export(target, "getKeyboardState", GetKeyboardState);
	Nan::Export(target, "getModState", GetModState);
	Nan::Export(target, "setModState", SetModState);

	Nan::Export(target, "isTextInputActive", IsTextInputActive);
	Nan::Export(target, "setTextInputRect", SetTextInputRect);
	Nan::Export(target, "startTextInput", StartTextInput);
	Nan::Export(target, "stopTextInput", StopTextInput);
}

NAN_METHOD(sdl::GetKeyFromName) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetKeyFromName(String)"));
		return;
	}

	String::Utf8Value name(info[0]);
	SDL_Keycode code = SDL_GetKeyFromName(*name);

	info.GetReturnValue().Set(Nan::New<Number>(code));
}

NAN_METHOD(sdl::GetKeyFromScancode) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetKeyFromScancode(Number)"));
		return;
	}

	SDL_Scancode scan = static_cast<SDL_Scancode>(info[0]->Int32Value());
	SDL_Keycode key = SDL_GetKeyFromScancode(scan);

	info.GetReturnValue().Set(Nan::New<Number>(key));
}

NAN_METHOD(sdl::GetKeyName) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetKeyName(Number)"));
		return;
	}

	SDL_Keycode key = static_cast<SDL_Keycode>(info[0]->Int32Value());
	const char *name = SDL_GetKeyName(key);

	info.GetReturnValue().Set(Nan::New(name).ToLocalChecked());
}

NAN_METHOD(sdl::GetScancodeFromKey) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetScancodeFromKey(Number)"));
		return;
	}

	SDL_Keycode key = static_cast<SDL_Keycode>(info[0]->Int32Value());
	SDL_Scancode scan = SDL_GetScancodeFromKey(key);

	info.GetReturnValue().Set(Nan::New<Number>(scan));
}

NAN_METHOD(sdl::GetScancodeFromName) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetScancodeFromName(String)"));
		return;
	}

	String::Utf8Value name(info[0]);
	SDL_Scancode scan = SDL_GetScancodeFromName(*name);

	info.GetReturnValue().Set(Nan::New<Number>(scan));
}

NAN_METHOD(sdl::GetScancodeName) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected GetScancodeName(Number)"));
		return;
	}

	SDL_Scancode scan = static_cast<SDL_Scancode>(info[0]->Int32Value());
	const char *name = SDL_GetScancodeName(scan);

	info.GetReturnValue().Set(Nan::New(name).ToLocalChecked());
}

NAN_METHOD(sdl::HasScreenKeyboardSupport) {
	SDL_bool ret = SDL_HasScreenKeyboardSupport();

	info.GetReturnValue().Set(Nan::New<Boolean>(ret ? true : false));
}

NAN_METHOD(sdl::IsScreenKeyboardShown) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected IsScreenKeyboardShown(Window)"));
		return;
	}

	WindowWrapper* wrap = Nan::ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[0]));
	SDL_bool ret = SDL_IsScreenKeyboardShown(wrap->window_);

	info.GetReturnValue().Set(Nan::New<Boolean>(ret ? true : false));
}

NAN_METHOD(sdl::GetKeyboardFocus) {
	SDL_Window* window = SDL_GetKeyboardFocus();
	Handle<Object> ret = Nan::New<Object>();
	WindowWrapper* wrap = new WindowWrapper(ret);
	wrap->window_ = window;

	info.GetReturnValue().Set(ret);
}
NAN_METHOD(sdl::GetKeyboardState) {
	int size;
	const Uint8 *state = SDL_GetKeyboardState(&size);

	// Copy the state of every key into a native Javascript array. The state returned
	// by SDL is to internal memory, therefore we don't want to manage it at all inside
	// of Javscript due to it possibly being freed at some point.
	//
	// SDL uses the value 1 and 0 to indicate pressed or not. This is translated to true
	// or false Javascript boolean values instead.
	Handle<Array> jsState = Nan::New<Array>(size);
	for(int i = 0; i < size; i++) {
		jsState->Set(i, Nan::New<Boolean>(state[i] == 1 ? true : false));
	}

	info.GetReturnValue().Set(jsState);
}
NAN_METHOD(sdl::GetModState) {
	SDL_Keymod mod = SDL_GetModState();

	info.GetReturnValue().Set(Nan::New<Number>(mod));
}

NAN_METHOD(sdl::SetModState) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected SetModState(Number)"));
		return;
	}

	SDL_Keymod mod = static_cast<SDL_Keymod>(info[0]->Int32Value());
	SDL_SetModState(mod);
}

NAN_METHOD(sdl::IsTextInputActive) {
	SDL_bool ret = SDL_IsTextInputActive();

	info.GetReturnValue().Set(Nan::New<Boolean>(ret));
}

NAN_METHOD(sdl::SetTextInputRect) {
	if(info.Length() < 1) {
		Nan::ThrowTypeError(STRING_NEW("Invalid arguments: Expected SetTextInputRect(Rect)"));
		return;
	}

	RectWrapper* rect = Nan::ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[0]));
	SDL_SetTextInputRect(rect->rect_);
}

NAN_METHOD(sdl::StartTextInput) {
	SDL_StartTextInput();
}

NAN_METHOD(sdl::StopTextInput) {
	SDL_StopTextInput();
}
