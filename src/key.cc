#include "key.h"
#include "window.h"
#include "struct_wrappers.h"
#include "container.h"

using namespace v8;
using namespace node;


NAN_MODULE_INIT(sdl::key::Init) {


	Handle<Object> KEY = Object::New();
	exports->Set(String::NewSymbol("KEY"), KEY);
	// Keys are set in the order that they are listed on this page:
	//  http://wiki.libsdl.org/SDLKeycodeLookup
	KEY->Set(String::NewSymbol("BACKSPACE"), Number::New(SDLK_BACKSPACE));
	KEY->Set(String::NewSymbol("TAB"), Number::New(SDLK_BACKSPACE));
	KEY->Set(String::NewSymbol("RETURN"), Number::New(SDLK_RETURN));
	KEY->Set(String::NewSymbol("ESCAPE"), Number::New(SDLK_ESCAPE));
	KEY->Set(String::NewSymbol("SPACE"), Number::New(SDLK_SPACE));
	KEY->Set(String::NewSymbol("EXCLAIM"), Number::New(SDLK_EXCLAIM));
	KEY->Set(String::NewSymbol("QUOTEDBL"), Number::New(SDLK_QUOTEDBL));
	KEY->Set(String::NewSymbol("HASH"), Number::New(SDLK_HASH));
	KEY->Set(String::NewSymbol("DOLLAR"), Number::New(SDLK_DOLLAR));
	KEY->Set(String::NewSymbol("PERCENT"), Number::New(SDLK_PERCENT));
	KEY->Set(String::NewSymbol("APERSAND"), Number::New(SDLK_AMPERSAND));
	KEY->Set(String::NewSymbol("QUOTE"), Number::New(SDLK_QUOTE));
	KEY->Set(String::NewSymbol("LEFTPAREN"), Number::New(SDLK_LEFTPAREN));
	KEY->Set(String::NewSymbol("RIGHTPAREN"), Number::New(SDLK_RIGHTPAREN));
	KEY->Set(String::NewSymbol("ASTERISK"), Number::New(SDLK_ASTERISK));
	KEY->Set(String::NewSymbol("PLUS"), Number::New(SDLK_PLUS));
	KEY->Set(String::NewSymbol("COMMA"), Number::New(SDLK_COMMA));
	KEY->Set(String::NewSymbol("MINUS"), Number::New(SDLK_MINUS));
	KEY->Set(String::NewSymbol("PERIOD"), Number::New(SDLK_PERIOD));
	KEY->Set(String::NewSymbol("SLASH"), Number::New(SDLK_SLASH));
	// Number keys. Numbers are written out due to being unable to write:
	//   foo.0 = "bar";
	// (even if you can do: foo[0] = "bar", it just isn't as friendly)
	KEY->Set(String::NewSymbol("ZERO"), Number::New(SDLK_0));
	KEY->Set(String::NewSymbol("ONE"), Number::New(SDLK_1));
	KEY->Set(String::NewSymbol("TWO"), Number::New(SDLK_2));
	KEY->Set(String::NewSymbol("THREE"), Number::New(SDLK_3));
	KEY->Set(String::NewSymbol("FOUR"), Number::New(SDLK_4));
	KEY->Set(String::NewSymbol("FIVE"), Number::New(SDLK_5));
	KEY->Set(String::NewSymbol("SIX"), Number::New(SDLK_6));
	KEY->Set(String::NewSymbol("SEVEN"), Number::New(SDLK_7));
	KEY->Set(String::NewSymbol("EIGHT"), Number::New(SDLK_8));
	KEY->Set(String::NewSymbol("NINE"), Number::New(SDLK_9));
	KEY->Set(String::NewSymbol("COLON"), Number::New(SDLK_COLON));
	KEY->Set(String::NewSymbol("SEMICOLON"), Number::New(SDLK_SEMICOLON));
	KEY->Set(String::NewSymbol("LESS"), Number::New(SDLK_LESS));
	KEY->Set(String::NewSymbol("EQUALS"), Number::New(SDLK_EQUALS));
	KEY->Set(String::NewSymbol("GREATER"), Number::New(SDLK_GREATER));
	KEY->Set(String::NewSymbol("QUESTION"), Number::New(SDLK_QUESTION));
	KEY->Set(String::NewSymbol("AT"), Number::New(SDLK_AT));
	KEY->Set(String::NewSymbol("LEFTBRACKET"), Number::New(SDLK_LEFTBRACKET));
	KEY->Set(String::NewSymbol("BACKSLASH"), Number::New(SDLK_BACKSLASH));
	KEY->Set(String::NewSymbol("RIGHTBRACKET"), Number::New(SDLK_RIGHTBRACKET));
	KEY->Set(String::NewSymbol("CARET"), Number::New(SDLK_CARET));
	KEY->Set(String::NewSymbol("UNDERSCORE"), Number::New(SDLK_UNDERSCORE));
	KEY->Set(String::NewSymbol("BACKQUOTE"), Number::New(SDLK_BACKQUOTE));
	KEY->Set(String::NewSymbol("A"), Number::New(SDLK_a));
	KEY->Set(String::NewSymbol("B"), Number::New(SDLK_b));
	KEY->Set(String::NewSymbol("C"), Number::New(SDLK_c));
	KEY->Set(String::NewSymbol("D"), Number::New(SDLK_d));
	KEY->Set(String::NewSymbol("E"), Number::New(SDLK_e));
	KEY->Set(String::NewSymbol("F"), Number::New(SDLK_f));
	KEY->Set(String::NewSymbol("G"), Number::New(SDLK_g));
	KEY->Set(String::NewSymbol("H"), Number::New(SDLK_h));
	KEY->Set(String::NewSymbol("I"), Number::New(SDLK_i));
	KEY->Set(String::NewSymbol("J"), Number::New(SDLK_j));
	KEY->Set(String::NewSymbol("K"), Number::New(SDLK_k));
	KEY->Set(String::NewSymbol("L"), Number::New(SDLK_l));
	KEY->Set(String::NewSymbol("M"), Number::New(SDLK_m));
	KEY->Set(String::NewSymbol("N"), Number::New(SDLK_n));
	KEY->Set(String::NewSymbol("O"), Number::New(SDLK_o));
	KEY->Set(String::NewSymbol("P"), Number::New(SDLK_p));
	KEY->Set(String::NewSymbol("Q"), Number::New(SDLK_q));
	KEY->Set(String::NewSymbol("R"), Number::New(SDLK_r));
	KEY->Set(String::NewSymbol("S"), Number::New(SDLK_s));
	KEY->Set(String::NewSymbol("T"), Number::New(SDLK_t));
	KEY->Set(String::NewSymbol("U"), Number::New(SDLK_u));
	KEY->Set(String::NewSymbol("V"), Number::New(SDLK_v));
	KEY->Set(String::NewSymbol("W"), Number::New(SDLK_w));
	KEY->Set(String::NewSymbol("X"), Number::New(SDLK_x));
	KEY->Set(String::NewSymbol("Y"), Number::New(SDLK_y));
	KEY->Set(String::NewSymbol("Z"), Number::New(SDLK_z));
	KEY->Set(String::NewSymbol("DELETE"), Number::New(SDLK_DELETE));
	KEY->Set(String::NewSymbol("CAPSLOCK"), Number::New(SDLK_CAPSLOCK));
	KEY->Set(String::NewSymbol("F1"), Number::New(SDLK_F1));
	KEY->Set(String::NewSymbol("F2"), Number::New(SDLK_F2));
	KEY->Set(String::NewSymbol("F3"), Number::New(SDLK_F3));
	KEY->Set(String::NewSymbol("F4"), Number::New(SDLK_F4));
	KEY->Set(String::NewSymbol("F5"), Number::New(SDLK_F5));
	KEY->Set(String::NewSymbol("F6"), Number::New(SDLK_F6));
	KEY->Set(String::NewSymbol("F7"), Number::New(SDLK_F7));
	KEY->Set(String::NewSymbol("F8"), Number::New(SDLK_F8));
	KEY->Set(String::NewSymbol("F9"), Number::New(SDLK_F9));
	KEY->Set(String::NewSymbol("F10"), Number::New(SDLK_F10));
	KEY->Set(String::NewSymbol("F11"), Number::New(SDLK_F11));
	KEY->Set(String::NewSymbol("F12"), Number::New(SDLK_F12));
	KEY->Set(String::NewSymbol("PRINTSCREEN"), Number::New(SDLK_PRINTSCREEN));
	KEY->Set(String::NewSymbol("SCROLLLOCK"), Number::New(SDLK_SCROLLLOCK));
	KEY->Set(String::NewSymbol("PAUSE"), Number::New(SDLK_PAUSE));
	KEY->Set(String::NewSymbol("INSERT"), Number::New(SDLK_INSERT));
	KEY->Set(String::NewSymbol("HOME"), Number::New(SDLK_HOME));
	KEY->Set(String::NewSymbol("PAGEUP"), Number::New(SDLK_PAGEUP));
	KEY->Set(String::NewSymbol("END"), Number::New(SDLK_END));
	KEY->Set(String::NewSymbol("PAGEDOWN"), Number::New(SDLK_PAGEDOWN));
	KEY->Set(String::NewSymbol("RIGHT"), Number::New(SDLK_RIGHT));
	KEY->Set(String::NewSymbol("LEFT"), Number::New(SDLK_LEFT));
	KEY->Set(String::NewSymbol("DOWN"), Number::New(SDLK_DOWN));
	KEY->Set(String::NewSymbol("UP"), Number::New(SDLK_UP));
	KEY->Set(String::NewSymbol("HOME"), Number::New(SDLK_HOME));
	KEY->Set(String::NewSymbol("NUMLOCKCLEAR"), Number::New(SDLK_NUMLOCKCLEAR));
	KEY->Set(String::NewSymbol("KP_DIVIDE"), Number::New(SDLK_KP_DIVIDE));
	KEY->Set(String::NewSymbol("KP_MULTIPLY"), Number::New(SDLK_KP_MULTIPLY));
	KEY->Set(String::NewSymbol("KP_MINUS"), Number::New(SDLK_KP_MINUS));
	KEY->Set(String::NewSymbol("KP_PLUS"), Number::New(SDLK_KP_PLUS));
	KEY->Set(String::NewSymbol("KP_ENTER"), Number::New(SDLK_KP_ENTER));
	KEY->Set(String::NewSymbol("KP_ONE"), Number::New(SDLK_KP_1));
	KEY->Set(String::NewSymbol("KP_TWO"), Number::New(SDLK_KP_2));
	KEY->Set(String::NewSymbol("KP_THREE"), Number::New(SDLK_KP_3));
	KEY->Set(String::NewSymbol("KP_FOUR"), Number::New(SDLK_KP_4));
	KEY->Set(String::NewSymbol("KP_FIVE"), Number::New(SDLK_KP_5));
	KEY->Set(String::NewSymbol("KP_SIX"), Number::New(SDLK_KP_6));
	KEY->Set(String::NewSymbol("KP_SEVEN"), Number::New(SDLK_KP_7));
	KEY->Set(String::NewSymbol("KP_EIGHT"), Number::New(SDLK_KP_8));
	KEY->Set(String::NewSymbol("KP_NINE"), Number::New(SDLK_KP_9));
	KEY->Set(String::NewSymbol("KP_ZERO"), Number::New(SDLK_KP_0));
	KEY->Set(String::NewSymbol("KP_PERIOD"), Number::New(SDLK_KP_PERIOD));
	KEY->Set(String::NewSymbol("APPLICATION"), Number::New(SDLK_APPLICATION));
	KEY->Set(String::NewSymbol("POWER"), Number::New(SDLK_POWER));
	KEY->Set(String::NewSymbol("KP_EQUALS"), Number::New(SDLK_KP_EQUALS));
	KEY->Set(String::NewSymbol("F13"), Number::New(SDLK_F13));
	KEY->Set(String::NewSymbol("F14"), Number::New(SDLK_F14));
	KEY->Set(String::NewSymbol("F15"), Number::New(SDLK_F15));
	KEY->Set(String::NewSymbol("F16"), Number::New(SDLK_F16));
	KEY->Set(String::NewSymbol("F17"), Number::New(SDLK_F17));
	KEY->Set(String::NewSymbol("F18"), Number::New(SDLK_F18));
	KEY->Set(String::NewSymbol("F19"), Number::New(SDLK_F19));
	KEY->Set(String::NewSymbol("F20"), Number::New(SDLK_F20));
	KEY->Set(String::NewSymbol("F21"), Number::New(SDLK_F21));
	KEY->Set(String::NewSymbol("F22"), Number::New(SDLK_F22));
	KEY->Set(String::NewSymbol("F23"), Number::New(SDLK_F23));
	KEY->Set(String::NewSymbol("F24"), Number::New(SDLK_F24));
	KEY->Set(String::NewSymbol("EXECUTE"), Number::New(SDLK_EXECUTE));
	KEY->Set(String::NewSymbol("HELP"), Number::New(SDLK_HELP));
	KEY->Set(String::NewSymbol("MENU"), Number::New(SDLK_MENU));
	KEY->Set(String::NewSymbol("SELECT"), Number::New(SDLK_SELECT));
	KEY->Set(String::NewSymbol("STOP"), Number::New(SDLK_STOP));
	KEY->Set(String::NewSymbol("AGAIN"), Number::New(SDLK_AGAIN));
	KEY->Set(String::NewSymbol("UNDO"), Number::New(SDLK_UNDO));
	KEY->Set(String::NewSymbol("CUT"), Number::New(SDLK_CUT));
	KEY->Set(String::NewSymbol("COPY"), Number::New(SDLK_COPY));
	KEY->Set(String::NewSymbol("PASTE"), Number::New(SDLK_PASTE));
	KEY->Set(String::NewSymbol("FIND"), Number::New(SDLK_FIND));
	KEY->Set(String::NewSymbol("MUTE"), Number::New(SDLK_MUTE));
	KEY->Set(String::NewSymbol("VOLUMEUP"), Number::New(SDLK_VOLUMEUP));
	KEY->Set(String::NewSymbol("VOLUMEDOWN"), Number::New(SDLK_VOLUMEDOWN));
	KEY->Set(String::NewSymbol("KP_COMMA"), Number::New(SDLK_KP_COMMA));
	KEY->Set(String::NewSymbol("KP_EQUALSAS400"), Number::New(SDLK_KP_EQUALSAS400));
	KEY->Set(String::NewSymbol("ALTERASE"), Number::New(SDLK_ALTERASE));
	KEY->Set(String::NewSymbol("SYSREQ"), Number::New(SDLK_SYSREQ));
	KEY->Set(String::NewSymbol("CANCEL"), Number::New(SDLK_CANCEL));
	KEY->Set(String::NewSymbol("CLEAR"), Number::New(SDLK_CLEAR));
	KEY->Set(String::NewSymbol("PRIOR"), Number::New(SDLK_PRIOR));
	KEY->Set(String::NewSymbol("RETURN2"), Number::New(SDLK_RETURN2));
	KEY->Set(String::NewSymbol("SEPARATOR"), Number::New(SDLK_SEPARATOR));
	KEY->Set(String::NewSymbol("OUT"), Number::New(SDLK_OUT));
	KEY->Set(String::NewSymbol("OPER"), Number::New(SDLK_OPER));
	KEY->Set(String::NewSymbol("CLEARAGAIN"), Number::New(SDLK_CLEARAGAIN));
	KEY->Set(String::NewSymbol("CRSEL"), Number::New(SDLK_CRSEL));
	KEY->Set(String::NewSymbol("EXSEL"), Number::New(SDLK_EXSEL));
	KEY->Set(String::NewSymbol("KP_ZEROZERO"), Number::New(SDLK_KP_00));
	KEY->Set(String::NewSymbol("KP_ZEROZEROZERO"), Number::New(SDLK_KP_000));
	KEY->Set(String::NewSymbol("THOUSANDSSEPARATOR"), Number::New(SDLK_THOUSANDSSEPARATOR));
	KEY->Set(String::NewSymbol("DECIMALSEPARATOR"), Number::New(SDLK_DECIMALSEPARATOR));
	KEY->Set(String::NewSymbol("CURRENCYUNIT"), Number::New(SDLK_CURRENCYUNIT));
	KEY->Set(String::NewSymbol("CURRENCYSUBUNIT"), Number::New(SDLK_CURRENCYSUBUNIT));
	KEY->Set(String::NewSymbol("KP_LEFTPAREN"), Number::New(SDLK_KP_LEFTPAREN));
	KEY->Set(String::NewSymbol("KP_RIGHTPAREN"), Number::New(SDLK_KP_RIGHTPAREN));
	KEY->Set(String::NewSymbol("KP_LEFTBRACE"), Number::New(SDLK_KP_LEFTBRACE));
	KEY->Set(String::NewSymbol("KP_RIGHTBRACE"), Number::New(SDLK_KP_RIGHTBRACE));
	KEY->Set(String::NewSymbol("KP_TAB"), Number::New(SDLK_KP_TAB));
	KEY->Set(String::NewSymbol("KP_BACKSPACE"), Number::New(SDLK_KP_BACKSPACE));
	KEY->Set(String::NewSymbol("KP_A"), Number::New(SDLK_KP_A));
	KEY->Set(String::NewSymbol("KP_B"), Number::New(SDLK_KP_B));
	KEY->Set(String::NewSymbol("KP_C"), Number::New(SDLK_KP_C));
	KEY->Set(String::NewSymbol("KP_D"), Number::New(SDLK_KP_D));
	KEY->Set(String::NewSymbol("KP_E"), Number::New(SDLK_KP_E));
	KEY->Set(String::NewSymbol("KP_F"), Number::New(SDLK_KP_F));
	KEY->Set(String::NewSymbol("KP_XOR"), Number::New(SDLK_KP_XOR));
	KEY->Set(String::NewSymbol("KP_POWER"), Number::New(SDLK_KP_POWER));
	KEY->Set(String::NewSymbol("KP_PERCENT"), Number::New(SDLK_KP_PERCENT));
	KEY->Set(String::NewSymbol("KP_LESS"), Number::New(SDLK_KP_LESS));
	KEY->Set(String::NewSymbol("KP_GREATER"), Number::New(SDLK_KP_GREATER));
	KEY->Set(String::NewSymbol("KP_AMPERSAND"), Number::New(SDLK_KP_AMPERSAND));
	KEY->Set(String::NewSymbol("KP_DBLAMPERSAND"), Number::New(SDLK_KP_DBLAMPERSAND));
	KEY->Set(String::NewSymbol("KP_VERTICALBAR"), Number::New(SDLK_KP_VERTICALBAR));
	KEY->Set(String::NewSymbol("KP_DBLVERTICALBAR"), Number::New(SDLK_KP_DBLVERTICALBAR));
	KEY->Set(String::NewSymbol("KP_COLON"), Number::New(SDLK_KP_COLON));
	KEY->Set(String::NewSymbol("KP_HASH"), Number::New(SDLK_KP_HASH));
	KEY->Set(String::NewSymbol("KP_SPACE"), Number::New(SDLK_KP_SPACE));
	KEY->Set(String::NewSymbol("KP_AT"), Number::New(SDLK_KP_AT));
	KEY->Set(String::NewSymbol("KP_EXCLAM"), Number::New(SDLK_KP_EXCLAM));
	KEY->Set(String::NewSymbol("KP_MEMSTORE"), Number::New(SDLK_KP_MEMSTORE));
	KEY->Set(String::NewSymbol("KP_MEMRECALL"), Number::New(SDLK_KP_MEMRECALL));
	KEY->Set(String::NewSymbol("KP_MEMCLEAR"), Number::New(SDLK_KP_MEMCLEAR));
	KEY->Set(String::NewSymbol("KP_MEMADD"), Number::New(SDLK_KP_MEMADD));
	KEY->Set(String::NewSymbol("KP_MEMSUBTRACT"), Number::New(SDLK_KP_MEMSUBTRACT));
	KEY->Set(String::NewSymbol("KP_MEMMULTIPLY"), Number::New(SDLK_KP_MEMMULTIPLY));
	KEY->Set(String::NewSymbol("KP_MEMDIVIDE"), Number::New(SDLK_KP_MEMDIVIDE));
	KEY->Set(String::NewSymbol("KP_PLUSMINUS"), Number::New(SDLK_KP_PLUSMINUS));
	KEY->Set(String::NewSymbol("KP_CLEAR"), Number::New(SDLK_KP_CLEAR));
	KEY->Set(String::NewSymbol("KP_CLEARENTRY"), Number::New(SDLK_KP_CLEARENTRY));
	KEY->Set(String::NewSymbol("KP_BINARY"), Number::New(SDLK_KP_BINARY));
	KEY->Set(String::NewSymbol("KP_OCTAL"), Number::New(SDLK_KP_OCTAL));
	KEY->Set(String::NewSymbol("KP_DECIMAL"), Number::New(SDLK_KP_DECIMAL));
	KEY->Set(String::NewSymbol("KP_HEXADECIMAL"), Number::New(SDLK_KP_HEXADECIMAL));
	KEY->Set(String::NewSymbol("LCTRL"), Number::New(SDLK_LCTRL));
	KEY->Set(String::NewSymbol("LSHIFT"), Number::New(SDLK_LSHIFT));
	KEY->Set(String::NewSymbol("LALT"), Number::New(SDLK_LALT));
	KEY->Set(String::NewSymbol("LGUI"), Number::New(SDLK_LGUI));
	KEY->Set(String::NewSymbol("RCTRL"), Number::New(SDLK_RCTRL));
	KEY->Set(String::NewSymbol("RSHIFT"), Number::New(SDLK_RSHIFT));
	KEY->Set(String::NewSymbol("RALT"), Number::New(SDLK_RALT));
	KEY->Set(String::NewSymbol("RGUI"), Number::New(SDLK_RGUI));
	KEY->Set(String::NewSymbol("MODE"), Number::New(SDLK_MODE));
	KEY->Set(String::NewSymbol("AUDIONEXT"), Number::New(SDLK_AUDIONEXT));
	KEY->Set(String::NewSymbol("AUDIOPREV"), Number::New(SDLK_AUDIOPREV));
	KEY->Set(String::NewSymbol("AUDIOSTOP"), Number::New(SDLK_AUDIOSTOP));
	KEY->Set(String::NewSymbol("AUDIOPLAY"), Number::New(SDLK_AUDIOPLAY));
	KEY->Set(String::NewSymbol("AUDIOMUTE"), Number::New(SDLK_AUDIOMUTE));
	KEY->Set(String::NewSymbol("MEDIASELECT"), Number::New(SDLK_MEDIASELECT));
	KEY->Set(String::NewSymbol("WWW"), Number::New(SDLK_WWW));
	KEY->Set(String::NewSymbol("MAIL"), Number::New(SDLK_MAIL));
	KEY->Set(String::NewSymbol("CALCULATOR"), Number::New(SDLK_CALCULATOR));
	KEY->Set(String::NewSymbol("COMPUTER"), Number::New(SDLK_COMPUTER));
	KEY->Set(String::NewSymbol("AC_SEARCH"), Number::New(SDLK_AC_SEARCH));
	KEY->Set(String::NewSymbol("AC_HOME"), Number::New(SDLK_AC_HOME));
	KEY->Set(String::NewSymbol("AC_BACK"), Number::New(SDLK_AC_BACK));
	KEY->Set(String::NewSymbol("AC_FORWARD"), Number::New(SDLK_AC_FORWARD));
	KEY->Set(String::NewSymbol("AC_STOP"), Number::New(SDLK_AC_STOP));
	KEY->Set(String::NewSymbol("AC_REFRESH"), Number::New(SDLK_AC_REFRESH));
	KEY->Set(String::NewSymbol("AC_BOOKMARKS"), Number::New(SDLK_AC_BOOKMARKS));
	KEY->Set(String::NewSymbol("BRIGHTNESSDOWN"), Number::New(SDLK_BRIGHTNESSDOWN));
	KEY->Set(String::NewSymbol("BRIGHTNESSUP"), Number::New(SDLK_BRIGHTNESSUP));
	KEY->Set(String::NewSymbol("DISPLAYSWITCH"), Number::New(SDLK_DISPLAYSWITCH));
	KEY->Set(String::NewSymbol("KBDILLUMTOGGLE"), Number::New(SDLK_KBDILLUMTOGGLE));
	KEY->Set(String::NewSymbol("KBDILLUMDOWN"), Number::New(SDLK_KBDILLUMDOWN));
	KEY->Set(String::NewSymbol("KBDILLUMUP"), Number::New(SDLK_KBDILLUMUP));
	KEY->Set(String::NewSymbol("EJECT"), Number::New(SDLK_EJECT));
	KEY->Set(String::NewSymbol("SLEEP"), Number::New(SDLK_SLEEP));

	Handle<Object> SCANCODE = Object::New();
	exports->Set(String::NewSymbol("SCANCODE"), SCANCODE);
	// Keys are set in the order that they are listed on this page:
	//  http://wiki.libsdl.org/SDLScancodeLookup
	SCANCODE->Set(String::NewSymbol("UNKNOWN"), Number::New(SDL_SCANCODE_UNKNOWN));
	SCANCODE->Set(String::NewSymbol("A"), Number::New(SDL_SCANCODE_A));
	SCANCODE->Set(String::NewSymbol("B"), Number::New(SDL_SCANCODE_B));
	SCANCODE->Set(String::NewSymbol("C"), Number::New(SDL_SCANCODE_C));
	SCANCODE->Set(String::NewSymbol("D"), Number::New(SDL_SCANCODE_D));
	SCANCODE->Set(String::NewSymbol("E"), Number::New(SDL_SCANCODE_E));
	SCANCODE->Set(String::NewSymbol("F"), Number::New(SDL_SCANCODE_F));
	SCANCODE->Set(String::NewSymbol("G"), Number::New(SDL_SCANCODE_G));
	SCANCODE->Set(String::NewSymbol("H"), Number::New(SDL_SCANCODE_H));
	SCANCODE->Set(String::NewSymbol("I"), Number::New(SDL_SCANCODE_I));
	SCANCODE->Set(String::NewSymbol("J"), Number::New(SDL_SCANCODE_J));
	SCANCODE->Set(String::NewSymbol("K"), Number::New(SDL_SCANCODE_K));
	SCANCODE->Set(String::NewSymbol("L"), Number::New(SDL_SCANCODE_L));
	SCANCODE->Set(String::NewSymbol("M"), Number::New(SDL_SCANCODE_M));
	SCANCODE->Set(String::NewSymbol("N"), Number::New(SDL_SCANCODE_N));
	SCANCODE->Set(String::NewSymbol("O"), Number::New(SDL_SCANCODE_O));
	SCANCODE->Set(String::NewSymbol("P"), Number::New(SDL_SCANCODE_P));
	SCANCODE->Set(String::NewSymbol("Q"), Number::New(SDL_SCANCODE_Q));
	SCANCODE->Set(String::NewSymbol("R"), Number::New(SDL_SCANCODE_R));
	SCANCODE->Set(String::NewSymbol("S"), Number::New(SDL_SCANCODE_S));
	SCANCODE->Set(String::NewSymbol("T"), Number::New(SDL_SCANCODE_T));
	SCANCODE->Set(String::NewSymbol("U"), Number::New(SDL_SCANCODE_U));
	SCANCODE->Set(String::NewSymbol("V"), Number::New(SDL_SCANCODE_V));
	SCANCODE->Set(String::NewSymbol("W"), Number::New(SDL_SCANCODE_W));
	SCANCODE->Set(String::NewSymbol("X"), Number::New(SDL_SCANCODE_X));
	SCANCODE->Set(String::NewSymbol("Y"), Number::New(SDL_SCANCODE_Y));
	SCANCODE->Set(String::NewSymbol("ONE"), Number::New(SDL_SCANCODE_1));
	SCANCODE->Set(String::NewSymbol("TWO"), Number::New(SDL_SCANCODE_2));
	SCANCODE->Set(String::NewSymbol("THREE"), Number::New(SDL_SCANCODE_3));
	SCANCODE->Set(String::NewSymbol("FOUR"), Number::New(SDL_SCANCODE_4));
	SCANCODE->Set(String::NewSymbol("FIVE"), Number::New(SDL_SCANCODE_5));
	SCANCODE->Set(String::NewSymbol("SIX"), Number::New(SDL_SCANCODE_6));
	SCANCODE->Set(String::NewSymbol("SEVEN"), Number::New(SDL_SCANCODE_7));
	SCANCODE->Set(String::NewSymbol("EIGHT"), Number::New(SDL_SCANCODE_8));
	SCANCODE->Set(String::NewSymbol("NINE"), Number::New(SDL_SCANCODE_9));
	SCANCODE->Set(String::NewSymbol("ZERO"), Number::New(SDL_SCANCODE_0));
	SCANCODE->Set(String::NewSymbol("RETURN"), Number::New(SDL_SCANCODE_RETURN));
	SCANCODE->Set(String::NewSymbol("BACKSPACE"), Number::New(SDL_SCANCODE_BACKSPACE));
	SCANCODE->Set(String::NewSymbol("TAB"), Number::New(SDL_SCANCODE_TAB));
	SCANCODE->Set(String::NewSymbol("SPACE"), Number::New(SDL_SCANCODE_SPACE));
	SCANCODE->Set(String::NewSymbol("MINUS"), Number::New(SDL_SCANCODE_MINUS));
	SCANCODE->Set(String::NewSymbol("EQUALS"), Number::New(SDL_SCANCODE_EQUALS));
	SCANCODE->Set(String::NewSymbol("LEFTBRACKET"), Number::New(SDL_SCANCODE_LEFTBRACKET));
	SCANCODE->Set(String::NewSymbol("RIGHTBRACKET"), Number::New(SDL_SCANCODE_RIGHTBRACKET));
	SCANCODE->Set(String::NewSymbol("BACKSLASH"), Number::New(SDL_SCANCODE_BACKSLASH));
	SCANCODE->Set(String::NewSymbol("NONUSHASH"), Number::New(SDL_SCANCODE_NONUSHASH));
	SCANCODE->Set(String::NewSymbol("SEMICOLON"), Number::New(SDL_SCANCODE_SEMICOLON));
	SCANCODE->Set(String::NewSymbol("APOSTROPHE"), Number::New(SDL_SCANCODE_APOSTROPHE));
	SCANCODE->Set(String::NewSymbol("GRAVE"), Number::New(SDL_SCANCODE_GRAVE));
	SCANCODE->Set(String::NewSymbol("COMMA"), Number::New(SDL_SCANCODE_COMMA));
	SCANCODE->Set(String::NewSymbol("PERIOD"), Number::New(SDL_SCANCODE_PERIOD));
	SCANCODE->Set(String::NewSymbol("SLASH"), Number::New(SDL_SCANCODE_SLASH));
	SCANCODE->Set(String::NewSymbol("CAPSLOCK"), Number::New(SDL_SCANCODE_CAPSLOCK));
	SCANCODE->Set(String::NewSymbol("F1"), Number::New(SDL_SCANCODE_F1));
	SCANCODE->Set(String::NewSymbol("F2"), Number::New(SDL_SCANCODE_F2));
	SCANCODE->Set(String::NewSymbol("F3"), Number::New(SDL_SCANCODE_F3));
	SCANCODE->Set(String::NewSymbol("F4"), Number::New(SDL_SCANCODE_F4));
	SCANCODE->Set(String::NewSymbol("F5"), Number::New(SDL_SCANCODE_F5));
	SCANCODE->Set(String::NewSymbol("F6"), Number::New(SDL_SCANCODE_F6));
	SCANCODE->Set(String::NewSymbol("F7"), Number::New(SDL_SCANCODE_F7));
	SCANCODE->Set(String::NewSymbol("F8"), Number::New(SDL_SCANCODE_F8));
	SCANCODE->Set(String::NewSymbol("F9"), Number::New(SDL_SCANCODE_F9));
	SCANCODE->Set(String::NewSymbol("F10"), Number::New(SDL_SCANCODE_F10));
	SCANCODE->Set(String::NewSymbol("F11"), Number::New(SDL_SCANCODE_F11));
	SCANCODE->Set(String::NewSymbol("F12"), Number::New(SDL_SCANCODE_F12));
	SCANCODE->Set(String::NewSymbol("PRINTSCREEN"), Number::New(SDL_SCANCODE_PRINTSCREEN));
	SCANCODE->Set(String::NewSymbol("SCROLLLOCK"), Number::New(SDL_SCANCODE_SCROLLLOCK));
	SCANCODE->Set(String::NewSymbol("PAUSE"), Number::New(SDL_SCANCODE_PAUSE));
	SCANCODE->Set(String::NewSymbol("INSERT"), Number::New(SDL_SCANCODE_INSERT));
	SCANCODE->Set(String::NewSymbol("HOME"), Number::New(SDL_SCANCODE_HOME));
	SCANCODE->Set(String::NewSymbol("PAGEUP"), Number::New(SDL_SCANCODE_PAGEUP));
	SCANCODE->Set(String::NewSymbol("DELETE"), Number::New(SDL_SCANCODE_DELETE));
	SCANCODE->Set(String::NewSymbol("END"), Number::New(SDL_SCANCODE_END));
	SCANCODE->Set(String::NewSymbol("PAGEDOWN"), Number::New(SDL_SCANCODE_PAGEDOWN));
	SCANCODE->Set(String::NewSymbol("RIGHT"), Number::New(SDL_SCANCODE_RIGHT));
	SCANCODE->Set(String::NewSymbol("LEFT"), Number::New(SDL_SCANCODE_LEFT));
	SCANCODE->Set(String::NewSymbol("DOWN"), Number::New(SDL_SCANCODE_DOWN));
	SCANCODE->Set(String::NewSymbol("UP"), Number::New(SDL_SCANCODE_UP));
	SCANCODE->Set(String::NewSymbol("NUMLOCKCLEAR"), Number::New(SDL_SCANCODE_NUMLOCKCLEAR));
	SCANCODE->Set(String::NewSymbol("KP_DIVIDE"), Number::New(SDL_SCANCODE_KP_DIVIDE));
	SCANCODE->Set(String::NewSymbol("KP_MULTIPLY"), Number::New(SDL_SCANCODE_KP_MULTIPLY));
	SCANCODE->Set(String::NewSymbol("KP_MINUS"), Number::New(SDL_SCANCODE_KP_MINUS));
	SCANCODE->Set(String::NewSymbol("KP_PLUS"), Number::New(SDL_SCANCODE_KP_ENTER));
	SCANCODE->Set(String::NewSymbol("KP_ONE"), Number::New(SDL_SCANCODE_KP_1));
	SCANCODE->Set(String::NewSymbol("KP_TWO"), Number::New(SDL_SCANCODE_KP_2));
	SCANCODE->Set(String::NewSymbol("KP_THREE"), Number::New(SDL_SCANCODE_KP_3));
	SCANCODE->Set(String::NewSymbol("KP_FOUR"), Number::New(SDL_SCANCODE_KP_4));
	SCANCODE->Set(String::NewSymbol("KP_FIVE"), Number::New(SDL_SCANCODE_KP_5));
	SCANCODE->Set(String::NewSymbol("KP_SIX"), Number::New(SDL_SCANCODE_KP_6));
	SCANCODE->Set(String::NewSymbol("KP_SEVEN"), Number::New(SDL_SCANCODE_KP_7));
	SCANCODE->Set(String::NewSymbol("KP_EIGHT"), Number::New(SDL_SCANCODE_KP_8));
	SCANCODE->Set(String::NewSymbol("KP_NINE"), Number::New(SDL_SCANCODE_KP_9));
	SCANCODE->Set(String::NewSymbol("KP_ZERO"), Number::New(SDL_SCANCODE_KP_0));
	SCANCODE->Set(String::NewSymbol("KP_PERIOD"), Number::New(SDL_SCANCODE_KP_PERIOD));
	SCANCODE->Set(String::NewSymbol("NONUSHBACKSLASH"), Number::New(SDL_SCANCODE_NONUSBACKSLASH));
	SCANCODE->Set(String::NewSymbol("APPLICATION"), Number::New(SDL_SCANCODE_APPLICATION));
	SCANCODE->Set(String::NewSymbol("POWER"), Number::New(SDL_SCANCODE_POWER));
	SCANCODE->Set(String::NewSymbol("KP_EQUALS"), Number::New(SDL_SCANCODE_KP_EQUALS));
	SCANCODE->Set(String::NewSymbol("F13"), Number::New(SDL_SCANCODE_F13));
	SCANCODE->Set(String::NewSymbol("F14"), Number::New(SDL_SCANCODE_F14));
	SCANCODE->Set(String::NewSymbol("F15"), Number::New(SDL_SCANCODE_F15));
	SCANCODE->Set(String::NewSymbol("F16"), Number::New(SDL_SCANCODE_F16));
	SCANCODE->Set(String::NewSymbol("F17"), Number::New(SDL_SCANCODE_F17));
	SCANCODE->Set(String::NewSymbol("F18"), Number::New(SDL_SCANCODE_F18));
	SCANCODE->Set(String::NewSymbol("F19"), Number::New(SDL_SCANCODE_F19));
	SCANCODE->Set(String::NewSymbol("F20"), Number::New(SDL_SCANCODE_F20));
	SCANCODE->Set(String::NewSymbol("F21"), Number::New(SDL_SCANCODE_F21));
	SCANCODE->Set(String::NewSymbol("F22"), Number::New(SDL_SCANCODE_F22));
	SCANCODE->Set(String::NewSymbol("F23"), Number::New(SDL_SCANCODE_F23));
	SCANCODE->Set(String::NewSymbol("F24"), Number::New(SDL_SCANCODE_F24));
	SCANCODE->Set(String::NewSymbol("EXECUTE"), Number::New(SDL_SCANCODE_EXECUTE));
	SCANCODE->Set(String::NewSymbol("HELP"), Number::New(SDL_SCANCODE_HELP));
	SCANCODE->Set(String::NewSymbol("MENU"), Number::New(SDL_SCANCODE_MENU));
	SCANCODE->Set(String::NewSymbol("SELECT"), Number::New(SDL_SCANCODE_SELECT));
	SCANCODE->Set(String::NewSymbol("STOP"), Number::New(SDL_SCANCODE_STOP));
	SCANCODE->Set(String::NewSymbol("AGAIN"), Number::New(SDL_SCANCODE_AGAIN));
	SCANCODE->Set(String::NewSymbol("UNDO"), Number::New(SDL_SCANCODE_UNDO));
	SCANCODE->Set(String::NewSymbol("CUT"), Number::New(SDL_SCANCODE_CUT));
	SCANCODE->Set(String::NewSymbol("COPY"), Number::New(SDL_SCANCODE_COPY));
	SCANCODE->Set(String::NewSymbol("PASTE"), Number::New(SDL_SCANCODE_PASTE));
	SCANCODE->Set(String::NewSymbol("FIND"), Number::New(SDL_SCANCODE_FIND));
	SCANCODE->Set(String::NewSymbol("MUTE"), Number::New(SDL_SCANCODE_MUTE));
	SCANCODE->Set(String::NewSymbol("VOLUMEUP"), Number::New(SDL_SCANCODE_VOLUMEUP));
	SCANCODE->Set(String::NewSymbol("VOLUMEDOWN"), Number::New(SDL_SCANCODE_VOLUMEDOWN));
	// For some reason, these are defined in the lookup table but don't exist in a header?
	// SCANCODE->Set(String::NewSymbol("LOCKINGCAPSLOCK"), Number::New(SDL_SCANCODE_LOCKINGCAPSLOCK));
	// SCANCODE->Set(String::NewSymbol("LOCKINGNUMLOCK"), Number::New(SDL_SCANCODE_LOCKINGNUMLOCK));
	// SCANCODE->Set(String::NewSymbol("LOCKINGSCROLLLOCK"), Number::New(SDL_SCANCODE_LOCKINGSCROLLLOCK));
	SCANCODE->Set(String::NewSymbol("KP_COMMA"), Number::New(SDL_SCANCODE_KP_COMMA));
	SCANCODE->Set(String::NewSymbol("KP_EQUALSAS400"), Number::New(SDL_SCANCODE_KP_EQUALSAS400));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL1"), Number::New(SDL_SCANCODE_INTERNATIONAL1));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL2"), Number::New(SDL_SCANCODE_INTERNATIONAL2));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL3"), Number::New(SDL_SCANCODE_INTERNATIONAL3));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL4"), Number::New(SDL_SCANCODE_INTERNATIONAL4));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL5"), Number::New(SDL_SCANCODE_INTERNATIONAL5));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL6"), Number::New(SDL_SCANCODE_INTERNATIONAL6));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL7"), Number::New(SDL_SCANCODE_INTERNATIONAL7));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL8"), Number::New(SDL_SCANCODE_INTERNATIONAL8));
	SCANCODE->Set(String::NewSymbol("INTERNATIONAL9"), Number::New(SDL_SCANCODE_INTERNATIONAL9));
	SCANCODE->Set(String::NewSymbol("LANG1"), Number::New(SDL_SCANCODE_LANG1));
	SCANCODE->Set(String::NewSymbol("LANG2"), Number::New(SDL_SCANCODE_LANG2));
	SCANCODE->Set(String::NewSymbol("LANG3"), Number::New(SDL_SCANCODE_LANG3));
	SCANCODE->Set(String::NewSymbol("LANG4"), Number::New(SDL_SCANCODE_LANG4));
	SCANCODE->Set(String::NewSymbol("LANG5"), Number::New(SDL_SCANCODE_LANG5));
	SCANCODE->Set(String::NewSymbol("LANG6"), Number::New(SDL_SCANCODE_LANG6));
	SCANCODE->Set(String::NewSymbol("LANG7"), Number::New(SDL_SCANCODE_LANG7));
	SCANCODE->Set(String::NewSymbol("LANG8"), Number::New(SDL_SCANCODE_LANG8));
	SCANCODE->Set(String::NewSymbol("LANG9"), Number::New(SDL_SCANCODE_LANG9));
	SCANCODE->Set(String::NewSymbol("ALTERASE"), Number::New(SDL_SCANCODE_ALTERASE));
	SCANCODE->Set(String::NewSymbol("SYSREQ"), Number::New(SDL_SCANCODE_SYSREQ));
	SCANCODE->Set(String::NewSymbol("CANCEL"), Number::New(SDL_SCANCODE_CANCEL));
	SCANCODE->Set(String::NewSymbol("CLEAR"), Number::New(SDL_SCANCODE_CLEAR));
	SCANCODE->Set(String::NewSymbol("PRIOR"), Number::New(SDL_SCANCODE_PRIOR));
	SCANCODE->Set(String::NewSymbol("RETURN2"), Number::New(SDL_SCANCODE_RETURN2));
	SCANCODE->Set(String::NewSymbol("SEPARATOR"), Number::New(SDL_SCANCODE_SEPARATOR));
	SCANCODE->Set(String::NewSymbol("OUT"), Number::New(SDL_SCANCODE_OUT));
	SCANCODE->Set(String::NewSymbol("OPER"), Number::New(SDL_SCANCODE_OPER));
	SCANCODE->Set(String::NewSymbol("CLEARAGAIN"), Number::New(SDL_SCANCODE_CLEARAGAIN));
	SCANCODE->Set(String::NewSymbol("CRSEL"), Number::New(SDL_SCANCODE_CRSEL));
	SCANCODE->Set(String::NewSymbol("EXSEL"), Number::New(SDL_SCANCODE_EXSEL));
	SCANCODE->Set(String::NewSymbol("KP_ZEROZERO"), Number::New(SDL_SCANCODE_KP_00));
	SCANCODE->Set(String::NewSymbol("KP_ZEROZEROZERO"), Number::New(SDL_SCANCODE_KP_000));
	SCANCODE->Set(String::NewSymbol("THOUSANDSSEPARATOR"), Number::New(SDL_SCANCODE_THOUSANDSSEPARATOR));
	SCANCODE->Set(String::NewSymbol("DECIMALSEPARATOR"), Number::New(SDL_SCANCODE_DECIMALSEPARATOR));
	SCANCODE->Set(String::NewSymbol("CURRENCYUNIT"), Number::New(SDL_SCANCODE_CURRENCYUNIT));
	SCANCODE->Set(String::NewSymbol("CURRENCYSUBUNIT"), Number::New(SDL_SCANCODE_CURRENCYSUBUNIT));
	SCANCODE->Set(String::NewSymbol("KP_LEFTPAREN"), Number::New(SDL_SCANCODE_KP_LEFTPAREN));
	SCANCODE->Set(String::NewSymbol("KP_RIGHTPAREN"), Number::New(SDL_SCANCODE_KP_RIGHTPAREN));
	SCANCODE->Set(String::NewSymbol("KP_LEFTBRACE"), Number::New(SDL_SCANCODE_KP_LEFTBRACE));
	SCANCODE->Set(String::NewSymbol("KP_RIGHTBRACE"), Number::New(SDL_SCANCODE_KP_RIGHTBRACE));
	SCANCODE->Set(String::NewSymbol("KP_TAB"), Number::New(SDL_SCANCODE_KP_TAB));
	SCANCODE->Set(String::NewSymbol("KP_BACKSPACE"), Number::New(SDL_SCANCODE_KP_BACKSPACE));
	SCANCODE->Set(String::NewSymbol("KP_A"), Number::New(SDL_SCANCODE_KP_A));
	SCANCODE->Set(String::NewSymbol("KP_B"), Number::New(SDL_SCANCODE_KP_D));
	SCANCODE->Set(String::NewSymbol("KP_C"), Number::New(SDL_SCANCODE_KP_C));
	SCANCODE->Set(String::NewSymbol("KP_D"), Number::New(SDL_SCANCODE_KP_D));
	SCANCODE->Set(String::NewSymbol("KP_E"), Number::New(SDL_SCANCODE_KP_E));
	SCANCODE->Set(String::NewSymbol("KP_F"), Number::New(SDL_SCANCODE_KP_F));
	SCANCODE->Set(String::NewSymbol("KP_XOR"), Number::New(SDL_SCANCODE_KP_XOR));
	SCANCODE->Set(String::NewSymbol("KP_POWER"), Number::New(SDL_SCANCODE_KP_POWER));
	SCANCODE->Set(String::NewSymbol("KP_PERCENT"), Number::New(SDL_SCANCODE_KP_PERCENT));
	SCANCODE->Set(String::NewSymbol("KP_LESS"), Number::New(SDL_SCANCODE_KP_LESS));
	SCANCODE->Set(String::NewSymbol("KP_GREATER"), Number::New(SDL_SCANCODE_KP_GREATER));
	SCANCODE->Set(String::NewSymbol("KP_AMPERSAND"), Number::New(SDL_SCANCODE_KP_AMPERSAND));
	SCANCODE->Set(String::NewSymbol("KP_DBLAMPERSAND"), Number::New(SDL_SCANCODE_KP_DBLAMPERSAND));
	SCANCODE->Set(String::NewSymbol("KP_VERTICALBAR"), Number::New(SDL_SCANCODE_KP_VERTICALBAR));
	SCANCODE->Set(String::NewSymbol("KP_DBLVERTICALBAR"), Number::New(SDL_SCANCODE_KP_DBLVERTICALBAR));
	SCANCODE->Set(String::NewSymbol("KP_COLON"), Number::New(SDL_SCANCODE_KP_COLON));
	SCANCODE->Set(String::NewSymbol("KP_HASH"), Number::New(SDL_SCANCODE_KP_HASH));
	SCANCODE->Set(String::NewSymbol("KP_SPACE"), Number::New(SDL_SCANCODE_KP_SPACE));
	SCANCODE->Set(String::NewSymbol("KP_AT"), Number::New(SDL_SCANCODE_KP_AT));
	SCANCODE->Set(String::NewSymbol("KP_EXCLAM"), Number::New(SDL_SCANCODE_KP_EXCLAM));
	SCANCODE->Set(String::NewSymbol("KP_MEMSTORE"), Number::New(SDL_SCANCODE_KP_MEMSTORE));
	SCANCODE->Set(String::NewSymbol("KP_MEMRECALL"), Number::New(SDL_SCANCODE_KP_MEMRECALL));
	SCANCODE->Set(String::NewSymbol("KP_MEMCLEAR"), Number::New(SDL_SCANCODE_KP_MEMCLEAR));
	SCANCODE->Set(String::NewSymbol("KP_MEMADD"), Number::New(SDL_SCANCODE_KP_MEMADD));
	SCANCODE->Set(String::NewSymbol("KP_MEMSUBTRACT"), Number::New(SDL_SCANCODE_KP_MEMSUBTRACT));
	SCANCODE->Set(String::NewSymbol("KP_MEMMULTIPLY"), Number::New(SDL_SCANCODE_KP_MEMMULTIPLY));
	SCANCODE->Set(String::NewSymbol("KP_MEMDIVIDE"), Number::New(SDL_SCANCODE_KP_MEMDIVIDE));
	SCANCODE->Set(String::NewSymbol("KP_PLUSMINUS"), Number::New(SDL_SCANCODE_KP_PLUSMINUS));
	SCANCODE->Set(String::NewSymbol("KP_CLEAR"), Number::New(SDL_SCANCODE_KP_CLEAR));
	SCANCODE->Set(String::NewSymbol("KP_CLEARENTRY"), Number::New(SDL_SCANCODE_KP_CLEARENTRY));
	SCANCODE->Set(String::NewSymbol("KP_BINARY"), Number::New(SDL_SCANCODE_KP_BINARY));
	SCANCODE->Set(String::NewSymbol("KP_OCTAL"), Number::New(SDL_SCANCODE_KP_OCTAL));
	SCANCODE->Set(String::NewSymbol("KP_DECIMAL"), Number::New(SDL_SCANCODE_KP_DECIMAL));
	SCANCODE->Set(String::NewSymbol("KP_HEXADECIMAL"), Number::New(SDL_SCANCODE_KP_HEXADECIMAL));
	SCANCODE->Set(String::NewSymbol("LCTRL"), Number::New(SDL_SCANCODE_LCTRL));
	SCANCODE->Set(String::NewSymbol("LSHIFT"), Number::New(SDL_SCANCODE_LSHIFT));
	SCANCODE->Set(String::NewSymbol("LALT"), Number::New(SDL_SCANCODE_LALT));
	SCANCODE->Set(String::NewSymbol("LGUI"), Number::New(SDL_SCANCODE_LGUI));
	SCANCODE->Set(String::NewSymbol("RCTRL"), Number::New(SDL_SCANCODE_RCTRL));
	SCANCODE->Set(String::NewSymbol("RSHIFT"), Number::New(SDL_SCANCODE_RSHIFT));
	SCANCODE->Set(String::NewSymbol("RALT"), Number::New(SDL_SCANCODE_RALT));
	SCANCODE->Set(String::NewSymbol("RGUI"), Number::New(SDL_SCANCODE_RGUI));
	SCANCODE->Set(String::NewSymbol("MODE"), Number::New(SDL_SCANCODE_MODE));
	SCANCODE->Set(String::NewSymbol("AUDIONEXT"), Number::New(SDL_SCANCODE_AUDIONEXT));
	SCANCODE->Set(String::NewSymbol("AUDIOPREV"), Number::New(SDL_SCANCODE_AUDIOPREV));
	SCANCODE->Set(String::NewSymbol("AUDIOSTOP"), Number::New(SDL_SCANCODE_AUDIOSTOP));
	SCANCODE->Set(String::NewSymbol("AUDIOPLAY"), Number::New(SDL_SCANCODE_AUDIOPLAY));
	SCANCODE->Set(String::NewSymbol("AUDIOMUTE"), Number::New(SDL_SCANCODE_AUDIOMUTE));
	SCANCODE->Set(String::NewSymbol("MEDIASELECT"), Number::New(SDL_SCANCODE_MEDIASELECT));
	SCANCODE->Set(String::NewSymbol("WWW"), Number::New(SDL_SCANCODE_WWW));
	SCANCODE->Set(String::NewSymbol("MAIL"), Number::New(SDL_SCANCODE_MAIL));
	SCANCODE->Set(String::NewSymbol("CALCULATOR"), Number::New(SDL_SCANCODE_CALCULATOR));
	SCANCODE->Set(String::NewSymbol("COMPUTER"), Number::New(SDL_SCANCODE_COMPUTER));
	SCANCODE->Set(String::NewSymbol("AC_SEARCH"), Number::New(SDL_SCANCODE_AC_SEARCH));
	SCANCODE->Set(String::NewSymbol("AC_HOME"), Number::New(SDL_SCANCODE_AC_HOME));
	SCANCODE->Set(String::NewSymbol("AC_BACK"), Number::New(SDL_SCANCODE_AC_BACK));
	SCANCODE->Set(String::NewSymbol("AC_FORWARD"), Number::New(SDL_SCANCODE_AC_FORWARD));
	SCANCODE->Set(String::NewSymbol("AC_STOP"), Number::New(SDL_SCANCODE_AC_STOP));
	SCANCODE->Set(String::NewSymbol("AC_REFRESH"), Number::New(SDL_SCANCODE_AC_REFRESH));
	SCANCODE->Set(String::NewSymbol("AC_BOOKMARKS"), Number::New(SDL_SCANCODE_AC_BOOKMARKS));
	SCANCODE->Set(String::NewSymbol("BRIGHTNESSDOWN"), Number::New(SDL_SCANCODE_BRIGHTNESSDOWN));
	SCANCODE->Set(String::NewSymbol("BRIGHTNESSUP"), Number::New(SDL_SCANCODE_BRIGHTNESSUP));
	SCANCODE->Set(String::NewSymbol("DISPLAYSWITCH"), Number::New(SDL_SCANCODE_DISPLAYSWITCH));
	SCANCODE->Set(String::NewSymbol("KBDILLUMTOGGLE"), Number::New(SDL_SCANCODE_KBDILLUMTOGGLE));
	SCANCODE->Set(String::NewSymbol("KBDILLUMDOWN"), Number::New(SDL_SCANCODE_KBDILLUMDOWN));
	SCANCODE->Set(String::NewSymbol("KBDILLUMUP"), Number::New(SDL_SCANCODE_KBDILLUMUP));
	SCANCODE->Set(String::NewSymbol("EJECT"), Number::New(SDL_SCANCODE_EJECT));
	SCANCODE->Set(String::NewSymbol("SLEEP"), Number::New(SDL_SCANCODE_SLEEP));

	Handle<Object> KMOD = Object::New();
	exports->Set(String::NewSymbol("KMOD"), KMOD);
	KMOD->Set(String::NewSymbol("NONE"), Number::New(KMOD_NONE));
	KMOD->Set(String::NewSymbol("LSHIFT"), Number::New(KMOD_LSHIFT));
	KMOD->Set(String::NewSymbol("RSHIFT"), Number::New(KMOD_RSHIFT));
	KMOD->Set(String::NewSymbol("LCTRL"), Number::New(KMOD_LCTRL));
	KMOD->Set(String::NewSymbol("RCTRL"), Number::New(KMOD_RCTRL));
	KMOD->Set(String::NewSymbol("LALT"), Number::New(KMOD_LALT));
	KMOD->Set(String::NewSymbol("RALT"), Number::New(KMOD_RALT));
	KMOD->Set(String::NewSymbol("LGUI"), Number::New(KMOD_LGUI));
	KMOD->Set(String::NewSymbol("RGUI"), Number::New(KMOD_RGUI));
	KMOD->Set(String::NewSymbol("NUM"), Number::New(KMOD_NUM));
	KMOD->Set(String::NewSymbol("CAPS"), Number::New(KMOD_CAPS));
	KMOD->Set(String::NewSymbol("MODE"), Number::New(KMOD_MODE));
	KMOD->Set(String::NewSymbol("CTRL"), Number::New(KMOD_CTRL));
	KMOD->Set(String::NewSymbol("SHIFT"), Number::New(KMOD_SHIFT));
	KMOD->Set(String::NewSymbol("ALT"), Number::New(KMOD_ALT));
	KMOD->Set(String::NewSymbol("GUI"), Number::New(KMOD_GUI));

	Nan::SetPrototypeMethod(exports, "getKeyFromName", GetKeyFromName);
	Nan::SetPrototypeMethod(exports, "getKeyFromScancode", GetKeyFromScancode);
	Nan::SetPrototypeMethod(exports, "getKeyName", GetKeyName);

	Nan::SetPrototypeMethod(exports, "getScancodeFromKey", GetScancodeFromKey);
	Nan::SetPrototypeMethod(exports, "getScancodeFromName", GetScancodeFromName);
	Nan::SetPrototypeMethod(exports, "getScancodeName", GetScancodeName);

	Nan::SetPrototypeMethod(exports, "hasScreenKeyboardSupport", HasScreenKeyboardSupport);
	Nan::SetPrototypeMethod(exports, "isScreenKeyboardShown", IsScreenKeyboardShown);

	Nan::SetPrototypeMethod(exports, "getKeyboardFocus", GetKeyboardFocus);
	Nan::SetPrototypeMethod(exports, "getKeyboardState", GetKeyboardState);
	Nan::SetPrototypeMethod(exports, "getModState", GetModState);
	Nan::SetPrototypeMethod(exports, "setModState", SetModState);

	Nan::SetPrototypeMethod(exports, "isTextInputActive", IsTextInputActive);
	Nan::SetPrototypeMethod(exports, "setTextInputRect", SetTextInputRect);
	Nan::SetPrototypeMethod(exports, "startTextInput", StartTextInput);
	Nan::SetPrototypeMethod(exports, "stopTextInput", StopTextInput);
}

// NAN_METHOD(sdl::GetKeyFromName) {
//

// 	if(info.Length() < 1) {
// 		return ThrowException(Exception::TypeError(
// 			String::New("Invalid arguments: Expected GetKeyFromName(String)")));
// 	}

// 	String::Utf8Value name(info[0]);
// 	SDL_Keycode code = SDL_GetKeyFromName(*name);

// 	info.GetReturnValue().Set(Number::New(code));
// }
FUNCTION_BEGINP(sdl, GetKeyFromName, 1)
	EXTRACT_STRING(name, 0);
	SDL_Keycode code = SDL_GetKeyFromName(*name);
FUNCTION_END(Number::New(code))

// NAN_METHOD(sdl::GetKeyFromScancode) {
//

// 	if(info.Length() < 1) {
// 		return ThrowException(Exception::TypeError(
// 			String::New("Invalid arguments: Expected GetKeyFromScancode(Number)")));
// 	}

// 	SDL_Scancode scan = static_cast<SDL_Scancode>(info[0]->Int32Value());
// 	SDL_Keycode key = SDL_GetKeyFromScancode(scan);

// 	info.GetReturnValue().Set(Number::New(key));
// }
FUNCTION_BEGINP(sdl, GetKeyFromScancode, 1)
	EXTRACT_INT32(scan, 0);
	SDL_Keycode key = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(scan));
FUNCTION_END(Number::New(key))

NAN_METHOD(sdl::GetKeyName) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetKeyName(Number)")));
	}

	SDL_Keycode key = static_cast<SDL_Keycode>(info[0]->Int32Value());
	const char *name = SDL_GetKeyName(key);

	info.GetReturnValue().Set(String::New(name));
}

NAN_METHOD(sdl::GetScancodeFromKey) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetScancodeFromKey(Number)")));
	}

	SDL_Keycode key = static_cast<SDL_Keycode>(info[0]->Int32Value());
	SDL_Scancode scan = SDL_GetScancodeFromKey(key);

	info.GetReturnValue().Set(Number::New(scan));
}
NAN_METHOD(sdl::GetScancodeFromName) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetScancodeFromName(String)")));
	}

	String::Utf8Value name(info[0]);
	SDL_Scancode scan = SDL_GetScancodeFromName(*name);

	info.GetReturnValue().Set(Number::New(scan));
}
NAN_METHOD(sdl::GetScancodeName) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected GetScancodeName(Number)")));
	}

	SDL_Scancode scan = static_cast<SDL_Scancode>(info[0]->Int32Value());
	const char *name = SDL_GetScancodeName(scan);

	info.GetReturnValue().Set(String::New(name));
}

NAN_METHOD(sdl::HasScreenKeyboardSupport) {


	SDL_bool ret = SDL_HasScreenKeyboardSupport();

	info.GetReturnValue().Set(Boolean::New(ret ? true : false));
}
NAN_METHOD(sdl::IsScreenKeyboardShown) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected IsScreenKeyboardShown(Window)")));
	}

	WindowWrapper* wrap = ObjectWrap::Unwrap<WindowWrapper>(Handle<Object>::Cast(info[0]));
	SDL_bool ret = SDL_IsScreenKeyboardShown(wrap->window_);

	info.GetReturnValue().Set(Boolean::New(ret ? true : false));
}

NAN_METHOD(sdl::GetKeyboardFocus) {


	SDL_Window* window = SDL_GetKeyboardFocus();
	Handle<Object> ret = Object::New();
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
	Handle<Array> jsState = Array::New(size);
	for(int i = 0; i < size; i++) {
		jsState->Set(i, Boolean::New(state[i] == 1 ? true : false));
	}

	info.GetReturnValue().Set(jsState);
}
NAN_METHOD(sdl::GetModState) {


	SDL_Keymod mod = SDL_GetModState();

	info.GetReturnValue().Set(Number::New(mod));
}
NAN_METHOD(sdl::SetModState) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected SetModState(Number)")));
	}

	SDL_Keymod mod = static_cast<SDL_Keymod>(info[0]->Int32Value());
	SDL_SetModState(mod);

	return Undefined();
}

NAN_METHOD(sdl::IsTextInputActive) {


	SDL_bool ret = SDL_IsTextInputActive();

	info.GetReturnValue().Set(Boolean::New(ret));
}
NAN_METHOD(sdl::SetTextInputRect) {


	if(info.Length() < 1) {
		return ThrowException(Exception::TypeError(
			String::New("Invalid arguments: Expected SetTextInputRect(Rect)")));
	}

	RectWrapper* rect = ObjectWrap::Unwrap<RectWrapper>(Handle<Object>::Cast(info[0]));
	SDL_SetTextInputRect(rect->wrapped);

	return Undefined();
}
NAN_METHOD(sdl::StartTextInput) {


	SDL_StartTextInput();

	return Undefined();
}
NAN_METHOD(sdl::StopTextInput) {


	SDL_StopTextInput();

	return Undefined();
}
