/* 
    Simple DirectMedia Layer
        Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>
*/

#ifndef KEYCODE_H
#define KEYCODE_H

//keycode
#define YIALITE_KEY_EXTENDED_MASK          (1u << 29)
#define YIALITE_KEY_SCANCODE_MASK          (1u << 30)
#define YIALITE_SCANCODE_TO_KEYCODE(X)  (X | YIALITE_KEY_SCANCODE_MASK)
#define YIALITE_KEY_UNKNOWN                0x00000000u /**< 0 */
#define YIALITE_KEY_RETURN                 0x0000000du /**< '\r' */
#define YIALITE_KEY_ESCAPE                 0x0000001bu /**< '\x1B' */
#define YIALITE_KEY_BACKSPACE              0x00000008u /**< '\b' */
#define YIALITE_KEY_TAB                    0x00000009u /**< '\t' */
#define YIALITE_KEY_SPACE                  0x00000020u /**< ' ' */
#define YIALITE_KEY_EXCLAIM                0x00000021u /**< '!' */
#define YIALITE_KEY_DBLAPOSTROPHE          0x00000022u /**< '"' */
#define YIALITE_KEY_HASH                   0x00000023u /**< '#' */
#define YIALITE_KEY_DOLLAR                 0x00000024u /**< '$' */
#define YIALITE_KEY_PERCENT                0x00000025u /**< '%' */
#define YIALITE_KEY_AMPERSAND              0x00000026u /**< '&' */
#define YIALITE_KEY_APOSTROPHE             0x00000027u /**< '\'' */
#define YIALITE_KEY_LEFTPAREN              0x00000028u /**< '(' */
#define YIALITE_KEY_RIGHTPAREN             0x00000029u /**< ')' */
#define YIALITE_KEY_ASTERISK               0x0000002au /**< '*' */
#define YIALITE_KEY_PLUS                   0x0000002bu /**< '+' */
#define YIALITE_KEY_COMMA                  0x0000002cu /**< ',' */
#define YIALITE_KEY_MINUS                  0x0000002du /**< '-' */
#define YIALITE_KEY_PERIOD                 0x0000002eu /**< '.' */
#define YIALITE_KEY_SLASH                  0x0000002fu /**< '/' */
#define YIALITE_KEY_0                      0x00000030u /**< '0' */
#define YIALITE_KEY_1                      0x00000031u /**< '1' */
#define YIALITE_KEY_2                      0x00000032u /**< '2' */
#define YIALITE_KEY_3                      0x00000033u /**< '3' */
#define YIALITE_KEY_4                      0x00000034u /**< '4' */
#define YIALITE_KEY_5                      0x00000035u /**< '5' */
#define YIALITE_KEY_6                      0x00000036u /**< '6' */
#define YIALITE_KEY_7                      0x00000037u /**< '7' */
#define YIALITE_KEY_8                      0x00000038u /**< '8' */
#define YIALITE_KEY_9                      0x00000039u /**< '9' */
#define YIALITE_KEY_COLON                  0x0000003au /**< ':' */
#define YIALITE_KEY_SEMICOLON              0x0000003bu /**< ';' */
#define YIALITE_KEY_LESS                   0x0000003cu /**< '<' */
#define YIALITE_KEY_EQUALS                 0x0000003du /**< '=' */
#define YIALITE_KEY_GREATER                0x0000003eu /**< '>' */
#define YIALITE_KEY_QUESTION               0x0000003fu /**< '?' */
#define YIALITE_KEY_AT                     0x00000040u /**< '@' */
#define YIALITE_KEY_LEFTBRACKET            0x0000005bu /**< '[' */
#define YIALITE_KEY_BACKSLASH              0x0000005cu /**< '\\' */
#define YIALITE_KEY_RIGHTBRACKET           0x0000005du /**< ']' */
#define YIALITE_KEY_CARET                  0x0000005eu /**< '^' */
#define YIALITE_KEY_UNDERSCORE             0x0000005fu /**< '_' */
#define YIALITE_KEY_GRAVE                  0x00000060u /**< '`' */
#define YIALITE_KEY_A                      0x00000061u /**< 'a' */
#define YIALITE_KEY_B                      0x00000062u /**< 'b' */
#define YIALITE_KEY_C                      0x00000063u /**< 'c' */
#define YIALITE_KEY_D                      0x00000064u /**< 'd' */
#define YIALITE_KEY_E                      0x00000065u /**< 'e' */
#define YIALITE_KEY_F                      0x00000066u /**< 'f' */
#define YIALITE_KEY_G                      0x00000067u /**< 'g' */
#define YIALITE_KEY_H                      0x00000068u /**< 'h' */
#define YIALITE_KEY_I                      0x00000069u /**< 'i' */
#define YIALITE_KEY_J                      0x0000006au /**< 'j' */
#define YIALITE_KEY_K                      0x0000006bu /**< 'k' */
#define YIALITE_KEY_L                      0x0000006cu /**< 'l' */
#define YIALITE_KEY_M                      0x0000006du /**< 'm' */
#define YIALITE_KEY_N                      0x0000006eu /**< 'n' */
#define YIALITE_KEY_O                      0x0000006fu /**< 'o' */
#define YIALITE_KEY_P                      0x00000070u /**< 'p' */
#define YIALITE_KEY_Q                      0x00000071u /**< 'q' */
#define YIALITE_KEY_R                      0x00000072u /**< 'r' */
#define YIALITE_KEY_S                      0x00000073u /**< 's' */
#define YIALITE_KEY_T                      0x00000074u /**< 't' */
#define YIALITE_KEY_U                      0x00000075u /**< 'u' */
#define YIALITE_KEY_V                      0x00000076u /**< 'v' */
#define YIALITE_KEY_W                      0x00000077u /**< 'w' */
#define YIALITE_KEY_X                      0x00000078u /**< 'x' */
#define YIALITE_KEY_Y                      0x00000079u /**< 'y' */
#define YIALITE_KEY_Z                      0x0000007au /**< 'z' */
#define YIALITE_KEY_LEFTBRACE              0x0000007bu /**< '{' */
#define YIALITE_KEY_PIPE                   0x0000007cu /**< '|' */
#define YIALITE_KEY_RIGHTBRACE             0x0000007du /**< '}' */
#define YIALITE_KEY_TILDE                  0x0000007eu /**< '~' */
#define YIALITE_KEY_DELETE                 0x0000007fu /**< '\x7F' */
#define YIALITE_KEY_PLUSMINUS              0x000000b1u /**< '\xB1' */
#define YIALITE_KEY_CAPSLOCK               0x40000039u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK) */
#define YIALITE_KEY_F1                     0x4000003au /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1) */
#define YIALITE_KEY_F2                     0x4000003bu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2) */
#define YIALITE_KEY_F3                     0x4000003cu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3) */
#define YIALITE_KEY_F4                     0x4000003du /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4) */
#define YIALITE_KEY_F5                     0x4000003eu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5) */
#define YIALITE_KEY_F6                     0x4000003fu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6) */
#define YIALITE_KEY_F7                     0x40000040u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7) */
#define YIALITE_KEY_F8                     0x40000041u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8) */
#define YIALITE_KEY_F9                     0x40000042u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9) */
#define YIALITE_KEY_F10                    0x40000043u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10) */
#define YIALITE_KEY_F11                    0x40000044u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11) */
#define YIALITE_KEY_F12                    0x40000045u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12) */
#define YIALITE_KEY_PRINTSCREEN            0x40000046u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN) */
#define YIALITE_KEY_SCROLLLOCK             0x40000047u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK) */
#define YIALITE_KEY_PAUSE                  0x40000048u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE) */
#define YIALITE_KEY_INSERT                 0x40000049u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT) */
#define YIALITE_KEY_HOME                   0x4000004au /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME) */
#define YIALITE_KEY_PAGEUP                 0x4000004bu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP) */
#define YIALITE_KEY_END                    0x4000004du /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END) */
#define YIALITE_KEY_PAGEDOWN               0x4000004eu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN) */
#define YIALITE_KEY_RIGHT                  0x4000004fu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT) */
#define YIALITE_KEY_LEFT                   0x40000050u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT) */
#define YIALITE_KEY_DOWN                   0x40000051u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN) */
#define YIALITE_KEY_UP                     0x40000052u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP) */

//keymod
#define YIALITE_KEY_MOD_NONE   0x0000u /**< no modifier is applicable. */
#define YIALITE_KEY_MOD_LSHIFT 0x0001u /**< the left Shift key is down. */
#define YIALITE_KEY_MOD_RSHIFT 0x0002u /**< the right Shift key is down. */
#define YIALITE_KEY_MOD_LEVEL5 0x0004u /**< the Level 5 Shift key is down. */
#define YIALITE_KEY_MOD_LCTRL  0x0040u /**< the left Ctrl (Control) key is down. */
#define YIALITE_KEY_MOD_RCTRL  0x0080u /**< the right Ctrl (Control) key is down. */
#define YIALITE_KEY_MOD_LALT   0x0100u /**< the left Alt key is down. */
#define YIALITE_KEY_MOD_RALT   0x0200u /**< the right Alt key is down. */
#define YIALITE_KEY_MOD_LGUI   0x0400u /**< the left GUI key (often the Windows key) is down. */
#define YIALITE_KEY_MOD_RGUI   0x0800u /**< the right GUI key (often the Windows key) is down. */
#define YIALITE_KEY_MOD_NUM    0x1000u /**< the Num Lock key (may be located on an extended keypad) is down. */
#define YIALITE_KEY_MOD_CAPS   0x2000u /**< the Caps Lock key is down. */
#define YIALITE_KEY_MOD_MODE   0x4000u /**< the !AltGr key is down. */
#define YIALITE_KEY_MOD_SCROLL 0x8000u /**< the Scroll Lock key is down. */
#define YIALITE_KEY_MOD_CTRL   (YIALITE_KEY_MOD_LCTRL | YIALITE_KEY_MOD_RCTRL)   /**< Any Ctrl key is down. */
#define YIALITE_KEY_MOD_SHIFT  (YIALITE_KEY_MOD_LSHIFT | YIALITE_KEY_MOD_RSHIFT) /**< Any Shift key is down. */
#define YIALITE_KEY_MOD_ALT    (YIALITE_KEY_MOD_LALT | YIALITE_KEY_MOD_RALT)     /**< Any Alt key is down. */
#define YIALITE_KEY_MOD_GUI    (YIALITE_KEY_MOD_LGUI | YIALITE_KEY_MOD_RGUI)     /**< Any GUI key is down. */

#endif