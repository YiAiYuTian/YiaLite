#ifndef KEYCODE_H
#define KEYCODE_H

//keycode
#define LITE_KEY_EXTENDED_MASK          (1u << 29)
#define LITE_KEY_SCANCODE_MASK          (1u << 30)
#define LITE_SCANCODE_TO_KEYCODE(X)  (X | LITE_KEY_SCANCODE_MASK)
#define LITE_KEY_UNKNOWN                0x00000000u /**< 0 */
#define LITE_KEY_RETURN                 0x0000000du /**< '\r' */
#define LITE_KEY_ESCAPE                 0x0000001bu /**< '\x1B' */
#define LITE_KEY_BACKSPACE              0x00000008u /**< '\b' */
#define LITE_KEY_TAB                    0x00000009u /**< '\t' */
#define LITE_KEY_SPACE                  0x00000020u /**< ' ' */
#define LITE_KEY_EXCLAIM                0x00000021u /**< '!' */
#define LITE_KEY_DBLAPOSTROPHE          0x00000022u /**< '"' */
#define LITE_KEY_HASH                   0x00000023u /**< '#' */
#define LITE_KEY_DOLLAR                 0x00000024u /**< '$' */
#define LITE_KEY_PERCENT                0x00000025u /**< '%' */
#define LITE_KEY_AMPERSAND              0x00000026u /**< '&' */
#define LITE_KEY_APOSTROPHE             0x00000027u /**< '\'' */
#define LITE_KEY_LEFTPAREN              0x00000028u /**< '(' */
#define LITE_KEY_RIGHTPAREN             0x00000029u /**< ')' */
#define LITE_KEY_ASTERISK               0x0000002au /**< '*' */
#define LITE_KEY_PLUS                   0x0000002bu /**< '+' */
#define LITE_KEY_COMMA                  0x0000002cu /**< ',' */
#define LITE_KEY_MINUS                  0x0000002du /**< '-' */
#define LITE_KEY_PERIOD                 0x0000002eu /**< '.' */
#define LITE_KEY_SLASH                  0x0000002fu /**< '/' */
#define LITE_KEY_0                      0x00000030u /**< '0' */
#define LITE_KEY_1                      0x00000031u /**< '1' */
#define LITE_KEY_2                      0x00000032u /**< '2' */
#define LITE_KEY_3                      0x00000033u /**< '3' */
#define LITE_KEY_4                      0x00000034u /**< '4' */
#define LITE_KEY_5                      0x00000035u /**< '5' */
#define LITE_KEY_6                      0x00000036u /**< '6' */
#define LITE_KEY_7                      0x00000037u /**< '7' */
#define LITE_KEY_8                      0x00000038u /**< '8' */
#define LITE_KEY_9                      0x00000039u /**< '9' */
#define LITE_KEY_COLON                  0x0000003au /**< ':' */
#define LITE_KEY_SEMICOLON              0x0000003bu /**< ';' */
#define LITE_KEY_LESS                   0x0000003cu /**< '<' */
#define LITE_KEY_EQUALS                 0x0000003du /**< '=' */
#define LITE_KEY_GREATER                0x0000003eu /**< '>' */
#define LITE_KEY_QUESTION               0x0000003fu /**< '?' */
#define LITE_KEY_AT                     0x00000040u /**< '@' */
#define LITE_KEY_LEFTBRACKET            0x0000005bu /**< '[' */
#define LITE_KEY_BACKSLASH              0x0000005cu /**< '\\' */
#define LITE_KEY_RIGHTBRACKET           0x0000005du /**< ']' */
#define LITE_KEY_CARET                  0x0000005eu /**< '^' */
#define LITE_KEY_UNDERSCORE             0x0000005fu /**< '_' */
#define LITE_KEY_GRAVE                  0x00000060u /**< '`' */
#define LITE_KEY_A                      0x00000061u /**< 'a' */
#define LITE_KEY_B                      0x00000062u /**< 'b' */
#define LITE_KEY_C                      0x00000063u /**< 'c' */
#define LITE_KEY_D                      0x00000064u /**< 'd' */
#define LITE_KEY_E                      0x00000065u /**< 'e' */
#define LITE_KEY_F                      0x00000066u /**< 'f' */
#define LITE_KEY_G                      0x00000067u /**< 'g' */
#define LITE_KEY_H                      0x00000068u /**< 'h' */
#define LITE_KEY_I                      0x00000069u /**< 'i' */
#define LITE_KEY_J                      0x0000006au /**< 'j' */
#define LITE_KEY_K                      0x0000006bu /**< 'k' */
#define LITE_KEY_L                      0x0000006cu /**< 'l' */
#define LITE_KEY_M                      0x0000006du /**< 'm' */
#define LITE_KEY_N                      0x0000006eu /**< 'n' */
#define LITE_KEY_O                      0x0000006fu /**< 'o' */
#define LITE_KEY_P                      0x00000070u /**< 'p' */
#define LITE_KEY_Q                      0x00000071u /**< 'q' */
#define LITE_KEY_R                      0x00000072u /**< 'r' */
#define LITE_KEY_S                      0x00000073u /**< 's' */
#define LITE_KEY_T                      0x00000074u /**< 't' */
#define LITE_KEY_U                      0x00000075u /**< 'u' */
#define LITE_KEY_V                      0x00000076u /**< 'v' */
#define LITE_KEY_W                      0x00000077u /**< 'w' */
#define LITE_KEY_X                      0x00000078u /**< 'x' */
#define LITE_KEY_Y                      0x00000079u /**< 'y' */
#define LITE_KEY_Z                      0x0000007au /**< 'z' */
#define LITE_KEY_LEFTBRACE              0x0000007bu /**< '{' */
#define LITE_KEY_PIPE                   0x0000007cu /**< '|' */
#define LITE_KEY_RIGHTBRACE             0x0000007du /**< '}' */
#define LITE_KEY_TILDE                  0x0000007eu /**< '~' */
#define LITE_KEY_DELETE                 0x0000007fu /**< '\x7F' */
#define LITE_KEY_PLUSMINUS              0x000000b1u /**< '\xB1' */
#define LITE_KEY_CAPSLOCK               0x40000039u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK) */
#define LITE_KEY_F1                     0x4000003au /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1) */
#define LITE_KEY_F2                     0x4000003bu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2) */
#define LITE_KEY_F3                     0x4000003cu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3) */
#define LITE_KEY_F4                     0x4000003du /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4) */
#define LITE_KEY_F5                     0x4000003eu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5) */
#define LITE_KEY_F6                     0x4000003fu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6) */
#define LITE_KEY_F7                     0x40000040u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7) */
#define LITE_KEY_F8                     0x40000041u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8) */
#define LITE_KEY_F9                     0x40000042u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9) */
#define LITE_KEY_F10                    0x40000043u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10) */
#define LITE_KEY_F11                    0x40000044u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11) */
#define LITE_KEY_F12                    0x40000045u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12) */
#define LITE_KEY_PRINTSCREEN            0x40000046u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN) */
#define LITE_KEY_SCROLLLOCK             0x40000047u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK) */
#define LITE_KEY_PAUSE                  0x40000048u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE) */
#define LITE_KEY_INSERT                 0x40000049u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT) */
#define LITE_KEY_HOME                   0x4000004au /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME) */
#define LITE_KEY_PAGEUP                 0x4000004bu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP) */
#define LITE_KEY_END                    0x4000004du /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END) */
#define LITE_KEY_PAGEDOWN               0x4000004eu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN) */
#define LITE_KEY_RIGHT                  0x4000004fu /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT) */
#define LITE_KEY_LEFT                   0x40000050u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT) */
#define LITE_KEY_DOWN                   0x40000051u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN) */
#define LITE_KEY_UP                     0x40000052u /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP) */

//keymod
#define LITE_KEY_MOD_NONE   0x0000u /**< no modifier is applicable. */
#define LITE_KEY_MOD_LSHIFT 0x0001u /**< the left Shift key is down. */
#define LITE_KEY_MOD_RSHIFT 0x0002u /**< the right Shift key is down. */
#define LITE_KEY_MOD_LEVEL5 0x0004u /**< the Level 5 Shift key is down. */
#define LITE_KEY_MOD_LCTRL  0x0040u /**< the left Ctrl (Control) key is down. */
#define LITE_KEY_MOD_RCTRL  0x0080u /**< the right Ctrl (Control) key is down. */
#define LITE_KEY_MOD_LALT   0x0100u /**< the left Alt key is down. */
#define LITE_KEY_MOD_RALT   0x0200u /**< the right Alt key is down. */
#define LITE_KEY_MOD_LGUI   0x0400u /**< the left GUI key (often the Windows key) is down. */
#define LITE_KEY_MOD_RGUI   0x0800u /**< the right GUI key (often the Windows key) is down. */
#define LITE_KEY_MOD_NUM    0x1000u /**< the Num Lock key (may be located on an extended keypad) is down. */
#define LITE_KEY_MOD_CAPS   0x2000u /**< the Caps Lock key is down. */
#define LITE_KEY_MOD_MODE   0x4000u /**< the !AltGr key is down. */
#define LITE_KEY_MOD_SCROLL 0x8000u /**< the Scroll Lock key is down. */
#define LITE_KEY_MOD_CTRL   (LITE_KEY_MOD_LCTRL | LITE_KEY_MOD_RCTRL)   /**< Any Ctrl key is down. */
#define LITE_KEY_MOD_SHIFT  (LITE_KEY_MOD_LSHIFT | LITE_KEY_MOD_RSHIFT) /**< Any Shift key is down. */
#define LITE_KEY_MOD_ALT    (LITE_KEY_MOD_LALT | LITE_KEY_MOD_RALT)     /**< Any Alt key is down. */
#define LITE_KEY_MOD_GUI    (LITE_KEY_MOD_LGUI | LITE_KEY_MOD_RGUI)     /**< Any GUI key is down. */

#endif