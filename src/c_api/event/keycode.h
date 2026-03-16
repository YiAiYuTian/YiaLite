/* 
    Simple DirectMedia Layer
    Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>
    Modified for YiaLite
*/

#ifndef C_YIALITE_KEYCODE_H
#define C_YIALITE_KEYCODE_H

#include <stdint.h>

typedef uint32_t YiaLite_Keycode;
typedef uint16_t YiaLite_Keymod;

//keycode
#define C_YIALITE_KEY_EXTENDED_MASK          (1u << 29)
#define C_YIALITE_KEY_SCANCODE_MASK          (1u << 30)
#define C_YIALITE_SCANCODE_TO_KEYCODE(X)  (X | C_YIALITE_KEY_SCANCODE_MASK)
#define C_YIALITE_KEY_UNKNOWN                0x00000000u /**< 0 */
#define C_YIALITE_KEY_RETURN                 0x0000000du /**< '\r' */
#define C_YIALITE_KEY_ESCAPE                 0x0000001bu /**< '\x1B' */
#define C_YIALITE_KEY_BACKSPACE              0x00000008u /**< '\b' */
#define C_YIALITE_KEY_TAB                    0x00000009u /**< '\t' */
#define C_YIALITE_KEY_SPACE                  0x00000020u /**< ' ' */
#define C_YIALITE_KEY_EXCLAIM                0x00000021u /**< '!' */
#define C_YIALITE_KEY_DBLAPOSTROPHE          0x00000022u /**< '"' */
#define C_YIALITE_KEY_HASH                   0x00000023u /**< '#' */
#define C_YIALITE_KEY_DOLLAR                 0x00000024u /**< '$' */
#define C_YIALITE_KEY_PERCENT                0x00000025u /**< '%' */
#define C_YIALITE_KEY_AMPERSAND              0x00000026u /**< '&' */
#define C_YIALITE_KEY_APOSTROPHE             0x00000027u /**< '\'' */
#define C_YIALITE_KEY_LEFTPAREN              0x00000028u /**< '(' */
#define C_YIALITE_KEY_RIGHTPAREN             0x00000029u /**< ')' */
#define C_YIALITE_KEY_ASTERISK               0x0000002au /**< '*' */
#define C_YIALITE_KEY_PLUS                   0x0000002bu /**< '+' */
#define C_YIALITE_KEY_COMMA                  0x0000002cu /**< ',' */
#define C_YIALITE_KEY_MINUS                  0x0000002du /**< '-' */
#define C_YIALITE_KEY_PERIOD                 0x0000002eu /**< '.' */
#define C_YIALITE_KEY_SLASH                  0x0000002fu /**< '/' */
#define C_YIALITE_KEY_0                      0x00000030u /**< '0' */
#define C_YIALITE_KEY_1                      0x00000031u /**< '1' */
#define C_YIALITE_KEY_2                      0x00000032u /**< '2' */
#define C_YIALITE_KEY_3                      0x00000033u /**< '3' */
#define C_YIALITE_KEY_4                      0x00000034u /**< '4' */
#define C_YIALITE_KEY_5                      0x00000035u /**< '5' */
#define C_YIALITE_KEY_6                      0x00000036u /**< '6' */
#define C_YIALITE_KEY_7                      0x00000037u /**< '7' */
#define C_YIALITE_KEY_8                      0x00000038u /**< '8' */
#define C_YIALITE_KEY_9                      0x00000039u /**< '9' */
#define C_YIALITE_KEY_COLON                  0x0000003au /**< ':' */
#define C_YIALITE_KEY_SEMICOLON              0x0000003bu /**< ';' */
#define C_YIALITE_KEY_LESS                   0x0000003cu /**< '<' */
#define C_YIALITE_KEY_EQUALS                 0x0000003du /**< '=' */
#define C_YIALITE_KEY_GREATER                0x0000003eu /**< '>' */
#define C_YIALITE_KEY_QUESTION               0x0000003fu /**< '?' */
#define C_YIALITE_KEY_AT                     0x00000040u /**< '@' */
#define C_YIALITE_KEY_LEFTBRACKET            0x0000005bu /**< '[' */
#define C_YIALITE_KEY_BACKSLASH              0x0000005cu /**< '\\' */
#define C_YIALITE_KEY_RIGHTBRACKET           0x0000005du /**< ']' */
#define C_YIALITE_KEY_CARET                  0x0000005eu /**< '^' */
#define C_YIALITE_KEY_UNDERSCORE             0x0000005fu /**< '_' */
#define C_YIALITE_KEY_GRAVE                  0x00000060u /**< '`' */
#define C_YIALITE_KEY_A                      0x00000061u /**< 'a' */
#define C_YIALITE_KEY_B                      0x00000062u /**< 'b' */
#define C_YIALITE_KEY_C                      0x00000063u /**< 'c' */
#define C_YIALITE_KEY_D                      0x00000064u /**< 'd' */
#define C_YIALITE_KEY_E                      0x00000065u /**< 'e' */
#define C_YIALITE_KEY_F                      0x00000066u /**< 'f' */
#define C_YIALITE_KEY_G                      0x00000067u /**< 'g' */
#define C_YIALITE_KEY_H                      0x00000068u /**< 'h' */
#define C_YIALITE_KEY_I                      0x00000069u /**< 'i' */
#define C_YIALITE_KEY_J                      0x0000006au /**< 'j' */
#define C_YIALITE_KEY_K                      0x0000006bu /**< 'k' */
#define C_YIALITE_KEY_L                      0x0000006cu /**< 'l' */
#define C_YIALITE_KEY_M                      0x0000006du /**< 'm' */
#define C_YIALITE_KEY_N                      0x0000006eu /**< 'n' */
#define C_YIALITE_KEY_O                      0x0000006fu /**< 'o' */
#define C_YIALITE_KEY_P                      0x00000070u /**< 'p' */
#define C_YIALITE_KEY_Q                      0x00000071u /**< 'q' */
#define C_YIALITE_KEY_R                      0x00000072u /**< 'r' */
#define C_YIALITE_KEY_S                      0x00000073u /**< 's' */
#define C_YIALITE_KEY_T                      0x00000074u /**< 't' */
#define C_YIALITE_KEY_U                      0x00000075u /**< 'u' */
#define C_YIALITE_KEY_V                      0x00000076u /**< 'v' */
#define C_YIALITE_KEY_W                      0x00000077u /**< 'w' */
#define C_YIALITE_KEY_X                      0x00000078u /**< 'x' */
#define C_YIALITE_KEY_Y                      0x00000079u /**< 'y' */
#define C_YIALITE_KEY_Z                      0x0000007au /**< 'z' */
#define C_YIALITE_KEY_LEFTBRACE              0x0000007bu /**< '{' */
#define C_YIALITE_KEY_PIPE                   0x0000007cu /**< '|' */
#define C_YIALITE_KEY_RIGHTBRACE             0x0000007du /**< '}' */
#define C_YIALITE_KEY_TILDE                  0x0000007eu /**< '~' */
#define C_YIALITE_KEY_DELETE                 0x0000007fu /**< '\x7F' */
#define C_YIALITE_KEY_PLUSMINUS              0x000000b1u /**< '\xB1' */
#define C_YIALITE_KEY_CAPSLOCK               0x40000039u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK) */
#define C_YIALITE_KEY_F1                     0x4000003au /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1) */
#define C_YIALITE_KEY_F2                     0x4000003bu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2) */
#define C_YIALITE_KEY_F3                     0x4000003cu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3) */
#define C_YIALITE_KEY_F4                     0x4000003du /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4) */
#define C_YIALITE_KEY_F5                     0x4000003eu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5) */
#define C_YIALITE_KEY_F6                     0x4000003fu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6) */
#define C_YIALITE_KEY_F7                     0x40000040u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7) */
#define C_YIALITE_KEY_F8                     0x40000041u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8) */
#define C_YIALITE_KEY_F9                     0x40000042u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9) */
#define C_YIALITE_KEY_F10                    0x40000043u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10) */
#define C_YIALITE_KEY_F11                    0x40000044u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11) */
#define C_YIALITE_KEY_F12                    0x40000045u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12) */
#define C_YIALITE_KEY_PRINTSCREEN            0x40000046u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN) */
#define C_YIALITE_KEY_SCROLLLOCK             0x40000047u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK) */
#define C_YIALITE_KEY_PAUSE                  0x40000048u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE) */
#define C_YIALITE_KEY_INSERT                 0x40000049u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT) */
#define C_YIALITE_KEY_HOME                   0x4000004au /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME) */
#define C_YIALITE_KEY_PAGEUP                 0x4000004bu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP) */
#define C_YIALITE_KEY_END                    0x4000004du /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END) */
#define C_YIALITE_KEY_PAGEDOWN               0x4000004eu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN) */
#define C_YIALITE_KEY_RIGHT                  0x4000004fu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT) */
#define C_YIALITE_KEY_LEFT                   0x40000050u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT) */
#define C_YIALITE_KEY_DOWN                   0x40000051u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN) */
#define C_YIALITE_KEY_UP                     0x40000052u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP) */

//keymod
#define C_YIALITE_KEY_MOD_NONE   0x0000u /**< no modifier is applicable. */
#define C_YIALITE_KEY_MOD_LSHIFT 0x0001u /**< the left Shift key is down. */
#define C_YIALITE_KEY_MOD_RSHIFT 0x0002u /**< the right Shift key is down. */
#define C_YIALITE_KEY_MOD_LEVEL5 0x0004u /**< the Level 5 Shift key is down. */
#define C_YIALITE_KEY_MOD_LCTRL  0x0040u /**< the left Ctrl (Control) key is down. */
#define C_YIALITE_KEY_MOD_RCTRL  0x0080u /**< the right Ctrl (Control) key is down. */
#define C_YIALITE_KEY_MOD_LALT   0x0100u /**< the left Alt key is down. */
#define C_YIALITE_KEY_MOD_RALT   0x0200u /**< the right Alt key is down. */
#define C_YIALITE_KEY_MOD_LGUI   0x0400u /**< the left GUI key (often the Windows key) is down. */
#define C_YIALITE_KEY_MOD_RGUI   0x0800u /**< the right GUI key (often the Windows key) is down. */
#define C_YIALITE_KEY_MOD_NUM    0x1000u /**< the Num Lock key (may be located on an extended keypad) is down. */
#define C_YIALITE_KEY_MOD_CAPS   0x2000u /**< the Caps Lock key is down. */
#define C_YIALITE_KEY_MOD_MODE   0x4000u /**< the !AltGr key is down. */
#define C_YIALITE_KEY_MOD_SCROLL 0x8000u /**< the Scroll Lock key is down. */
#define C_YIALITE_KEY_MOD_CTRL   (C_YIALITE_KEY_MOD_LCTRL | C_YIALITE_KEY_MOD_RCTRL)   /**< Any Ctrl key is down. */
#define C_YIALITE_KEY_MOD_SHIFT  (C_YIALITE_KEY_MOD_LSHIFT | C_YIALITE_KEY_MOD_RSHIFT) /**< Any Shift key is down. */
#define C_YIALITE_KEY_MOD_ALT    (C_YIALITE_KEY_MOD_LALT | C_YIALITE_KEY_MOD_RALT)     /**< Any Alt key is down. */
#define C_YIALITE_KEY_MOD_GUI    (C_YIALITE_KEY_MOD_LGUI | C_YIALITE_KEY_MOD_RGUI)     /**< Any GUI key is down. */

#endif