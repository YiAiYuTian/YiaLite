#ifndef KEYCODE_H
#define KEYCODE_H

//keycode
#define KEY_EXTENDED_MASK          (1u << 29)
#define KEY_SCANCODE_MASK          (1u << 30)
#define SCANCODE_TO_KEYCODE(X)  (X | KEY_SCANCODE_MASK)
#define KEY_UNKNOWN                0x00000000u /**< 0 */
#define KEY_RETURN                 0x0000000du /**< '\r' */
#define KEY_ESCAPE                 0x0000001bu /**< '\x1B' */
#define KEY_BACKSPACE              0x00000008u /**< '\b' */
#define KEY_TAB                    0x00000009u /**< '\t' */
#define KEY_SPACE                  0x00000020u /**< ' ' */
#define KEY_EXCLAIM                0x00000021u /**< '!' */
#define KEY_DBLAPOSTROPHE          0x00000022u /**< '"' */
#define KEY_HASH                   0x00000023u /**< '#' */
#define KEY_DOLLAR                 0x00000024u /**< '$' */
#define KEY_PERCENT                0x00000025u /**< '%' */
#define KEY_AMPERSAND              0x00000026u /**< '&' */
#define KEY_APOSTROPHE             0x00000027u /**< '\'' */
#define KEY_LEFTPAREN              0x00000028u /**< '(' */
#define KEY_RIGHTPAREN             0x00000029u /**< ')' */
#define KEY_ASTERISK               0x0000002au /**< '*' */
#define KEY_PLUS                   0x0000002bu /**< '+' */
#define KEY_COMMA                  0x0000002cu /**< ',' */
#define KEY_MINUS                  0x0000002du /**< '-' */
#define KEY_PERIOD                 0x0000002eu /**< '.' */
#define KEY_SLASH                  0x0000002fu /**< '/' */
#define KEY_0                      0x00000030u /**< '0' */
#define KEY_1                      0x00000031u /**< '1' */
#define KEY_2                      0x00000032u /**< '2' */
#define KEY_3                      0x00000033u /**< '3' */
#define KEY_4                      0x00000034u /**< '4' */
#define KEY_5                      0x00000035u /**< '5' */
#define KEY_6                      0x00000036u /**< '6' */
#define KEY_7                      0x00000037u /**< '7' */
#define KEY_8                      0x00000038u /**< '8' */
#define KEY_9                      0x00000039u /**< '9' */
#define KEY_COLON                  0x0000003au /**< ':' */
#define KEY_SEMICOLON              0x0000003bu /**< ';' */
#define KEY_LESS                   0x0000003cu /**< '<' */
#define KEY_EQUALS                 0x0000003du /**< '=' */
#define KEY_GREATER                0x0000003eu /**< '>' */
#define KEY_QUESTION               0x0000003fu /**< '?' */
#define KEY_AT                     0x00000040u /**< '@' */
#define KEY_LEFTBRACKET            0x0000005bu /**< '[' */
#define KEY_BACKSLASH              0x0000005cu /**< '\\' */
#define KEY_RIGHTBRACKET           0x0000005du /**< ']' */
#define KEY_CARET                  0x0000005eu /**< '^' */
#define KEY_UNDERSCORE             0x0000005fu /**< '_' */
#define KEY_GRAVE                  0x00000060u /**< '`' */
#define KEY_A                      0x00000061u /**< 'a' */
#define KEY_B                      0x00000062u /**< 'b' */
#define KEY_C                      0x00000063u /**< 'c' */
#define KEY_D                      0x00000064u /**< 'd' */
#define KEY_E                      0x00000065u /**< 'e' */
#define KEY_F                      0x00000066u /**< 'f' */
#define KEY_G                      0x00000067u /**< 'g' */
#define KEY_H                      0x00000068u /**< 'h' */
#define KEY_I                      0x00000069u /**< 'i' */
#define KEY_J                      0x0000006au /**< 'j' */
#define KEY_K                      0x0000006bu /**< 'k' */
#define KEY_L                      0x0000006cu /**< 'l' */
#define KEY_M                      0x0000006du /**< 'm' */
#define KEY_N                      0x0000006eu /**< 'n' */
#define KEY_O                      0x0000006fu /**< 'o' */
#define KEY_P                      0x00000070u /**< 'p' */
#define KEY_Q                      0x00000071u /**< 'q' */
#define KEY_R                      0x00000072u /**< 'r' */
#define KEY_S                      0x00000073u /**< 's' */
#define KEY_T                      0x00000074u /**< 't' */
#define KEY_U                      0x00000075u /**< 'u' */
#define KEY_V                      0x00000076u /**< 'v' */
#define KEY_W                      0x00000077u /**< 'w' */
#define KEY_X                      0x00000078u /**< 'x' */
#define KEY_Y                      0x00000079u /**< 'y' */
#define KEY_Z                      0x0000007au /**< 'z' */
#define KEY_LEFTBRACE              0x0000007bu /**< '{' */
#define KEY_PIPE                   0x0000007cu /**< '|' */
#define KEY_RIGHTBRACE             0x0000007du /**< '}' */
#define KEY_TILDE                  0x0000007eu /**< '~' */
#define KEY_DELETE                 0x0000007fu /**< '\x7F' */
#define KEY_PLUSMINUS              0x000000b1u /**< '\xB1' */
#define KEY_CAPSLOCK               0x40000039u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK) */
#define KEY_F1                     0x4000003au /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1) */
#define KEY_F2                     0x4000003bu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2) */
#define KEY_F3                     0x4000003cu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3) */
#define KEY_F4                     0x4000003du /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4) */
#define KEY_F5                     0x4000003eu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5) */
#define KEY_F6                     0x4000003fu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6) */
#define KEY_F7                     0x40000040u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7) */
#define KEY_F8                     0x40000041u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8) */
#define KEY_F9                     0x40000042u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9) */
#define KEY_F10                    0x40000043u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10) */
#define KEY_F11                    0x40000044u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11) */
#define KEY_F12                    0x40000045u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12) */
#define KEY_PRINTSCREEN            0x40000046u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN) */
#define KEY_SCROLLLOCK             0x40000047u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK) */
#define KEY_PAUSE                  0x40000048u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE) */
#define KEY_INSERT                 0x40000049u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT) */
#define KEY_HOME                   0x4000004au /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME) */
#define KEY_PAGEUP                 0x4000004bu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP) */
#define KEY_END                    0x4000004du /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END) */
#define KEY_PAGEDOWN               0x4000004eu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN) */
#define KEY_RIGHT                  0x4000004fu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT) */
#define KEY_LEFT                   0x40000050u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT) */
#define KEY_DOWN                   0x40000051u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN) */
#define KEY_UP                     0x40000052u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP) */

//keymod
#define KEY_MOD_NONE   0x0000u /**< no modifier is applicable. */
#define KEY_MOD_LSHIFT 0x0001u /**< the left Shift key is down. */
#define KEY_MOD_RSHIFT 0x0002u /**< the right Shift key is down. */
#define KEY_MOD_LEVEL5 0x0004u /**< the Level 5 Shift key is down. */
#define KEY_MOD_LCTRL  0x0040u /**< the left Ctrl (Control) key is down. */
#define KEY_MOD_RCTRL  0x0080u /**< the right Ctrl (Control) key is down. */
#define KEY_MOD_LALT   0x0100u /**< the left Alt key is down. */
#define KEY_MOD_RALT   0x0200u /**< the right Alt key is down. */
#define KEY_MOD_LGUI   0x0400u /**< the left GUI key (often the Windows key) is down. */
#define KEY_MOD_RGUI   0x0800u /**< the right GUI key (often the Windows key) is down. */
#define KEY_MOD_NUM    0x1000u /**< the Num Lock key (may be located on an extended keypad) is down. */
#define KEY_MOD_CAPS   0x2000u /**< the Caps Lock key is down. */
#define KEY_MOD_MODE   0x4000u /**< the !AltGr key is down. */
#define KEY_MOD_SCROLL 0x8000u /**< the Scroll Lock key is down. */
#define KEY_MOD_CTRL   (KEY_MOD_LCTRL | KEY_MOD_RCTRL)   /**< Any Ctrl key is down. */
#define KEY_MOD_SHIFT  (KEY_MOD_LSHIFT | KEY_MOD_RSHIFT) /**< Any Shift key is down. */
#define KEY_MOD_ALT    (KEY_MOD_LALT | KEY_MOD_RALT)     /**< Any Alt key is down. */
#define KEY_MOD_GUI    (KEY_MOD_LGUI | KEY_MOD_RGUI)     /**< Any GUI key is down. */

#endif