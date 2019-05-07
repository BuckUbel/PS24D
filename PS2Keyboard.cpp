#include "PS2Keyboard.h"

#define BUFFER_SIZE 45
static volatile uint8_t buffer[BUFFER_SIZE];
static volatile uint8_t head, tail;
static uint8_t DataPin;
static uint8_t CharBuffer=0;
static uint8_t UTF8next=0;
static const PS2Keymap_t *keymap=NULL;

// The ISR for the external interrupt
void ps2interrupt(void)
{
  static uint8_t bitcount=0;
  static uint8_t incoming=0;
  static uint32_t prev_ms=0;
  uint32_t now_ms;
  uint8_t n, val;

  val = digitalRead(DataPin);
  now_ms = millis();
  if (now_ms - prev_ms > 250) {
    bitcount = 0;
    incoming = 0;
  }
  prev_ms = now_ms;
  n = bitcount - 1;
  if (n <= 7) {
    incoming |= (val << n);
  }
  bitcount++;
  if (bitcount == 11) {
    uint8_t i = head + 1;
    if (i >= BUFFER_SIZE) i = 0;
    if (i != tail) {
      buffer[i] = incoming;
      head = i;
    }
    bitcount = 0;
    incoming = 0;
  }
}

static inline uint8_t get_scan_code(void)
{
  uint8_t c, i;

  i = tail;
  if (i == head) return 0;
  i++;
  if (i >= BUFFER_SIZE) i = 0;
  c = buffer[i];
  tail = i;
  return c;
}

const PROGMEM PS2Keymap_t PS2Keymap_German = {
  // without shift
  {0, PS2_F9, 0, PS2_F5, PS2_F3, PS2_F1, PS2_F2, PS2_F12,
  0, PS2_F10, PS2_F8, PS2_F6, PS2_F4, PS2_TAB, '^', 0,
  0, 0 /*Lalt*/, 0 /*Lshift*/, 0, 0 /*Lctrl*/, 'q', '1', 0,
  0, 0, 'y', 's', 'a', 'w', '2', 0,
  0, 'c', 'x', 'd', 'e', '4', '3', 0,
  0, ' ', 'v', 'f', 't', 'r', '5', 0,
  0, 'n', 'b', 'h', 'g', 'z', '6', 0,
  0, 0, 'm', 'j', 'u', '7', '8', 0,
  0, ',', 'k', 'i', 'o', '0', '9', 0,
  0, '.', '-', 'l', PS2_o_DIAERESIS, 'p', PS2_SHARP_S, 0,
  0, 0, PS2_a_DIAERESIS, 0, PS2_u_DIAERESIS, '\'', 0, 0,
  0 /*CapsLock*/, 0 /*Rshift*/, PS2_ENTER /*Enter*/, '+', 0, '#', 0, 0,
  0, '<', 0, 0, 0, 0, PS2_BACKSPACE, 0,
  0, '1', 0, '4', '7', 0, 0, 0,
  '0', '.', '2', '5', '6', '8', PS2_ESC, 0 /*NumLock*/,
  PS2_F11, '+', '3', '-', '*', '9', PS2_SCROLL, 0,
  0, 0, 0, PS2_F7 },
  // with shift
  {0, PS2_F9, 0, PS2_F5, PS2_F3, PS2_F1, PS2_F2, PS2_F12,
  0, PS2_F10, PS2_F8, PS2_F6, PS2_F4, PS2_TAB, PS2_DEGREE_SIGN, 0,
  0, 0 /*Lalt*/, 0 /*Lshift*/, 0, 0 /*Lctrl*/, 'Q', '!', 0,
  0, 0, 'Y', 'S', 'A', 'W', '"', 0,
  0, 'C', 'X', 'D', 'E', '$', PS2_SECTION_SIGN, 0,
  0, ' ', 'V', 'F', 'T', 'R', '%', 0,
  0, 'N', 'B', 'H', 'G', 'Z', '&', 0,
  0, 0, 'M', 'J', 'U', '/', '(', 0,
  0, ';', 'K', 'I', 'O', '=', ')', 0,
  0, ':', '_', 'L', PS2_O_DIAERESIS, 'P', '?', 0,
  0, 0, PS2_A_DIAERESIS, 0, PS2_U_DIAERESIS, '`', 0, 0,
  0 /*CapsLock*/, 0 /*Rshift*/, PS2_ENTER /*Enter*/, '*', 0, '\'', 0, 0,
  0, '>', 0, 0, 0, 0, PS2_BACKSPACE, 0,
  0, '1', 0, '4', '7', 0, 0, 0,
  '0', '.', '2', '5', '6', '8', PS2_ESC, 0 /*NumLock*/,
  PS2_F11, '+', '3', '-', '*', '9', PS2_SCROLL, 0,
  0, 0, 0, PS2_F7 },
  1,
  // with altgr
  {0, PS2_F9, 0, PS2_F5, PS2_F3, PS2_F1, PS2_F2, PS2_F12,
  0, PS2_F10, PS2_F8, PS2_F6, PS2_F4, PS2_TAB, 0, 0,
  0, 0 /*Lalt*/, 0 /*Lshift*/, 0, 0 /*Lctrl*/, '@', 0, 0,
  0, 0, 0, 0, 0, 0, PS2_SUPERSCRIPT_TWO, 0,
  0, 0, 0, 0, PS2_CURRENCY_SIGN, 0, PS2_SUPERSCRIPT_THREE, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, PS2_MICRO_SIGN, 0, 0, '{', '[', 0,
  0, 0, 0, 0, 0, '}', ']', 0,
  0, 0, 0, 0, 0, 0, '\\', 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0 /*CapsLock*/, 0 /*Rshift*/, PS2_ENTER /*Enter*/, '~', 0, '#', 0, 0,
  0, '|', 0, 0, 0, 0, PS2_BACKSPACE, 0,
  0, '1', 0, '4', '7', 0, 0, 0,
  '0', '.', '2', '5', '6', '8', PS2_ESC, 0 /*NumLock*/,
  PS2_F11, '+', '3', '-', '*', '9', PS2_SCROLL, 0,
  0, 0, 0, PS2_F7 }
};

#define BREAK     0x01
#define MODIFIER  0x02
#define SHIFT_L   0x04
#define SHIFT_R   0x08
#define ALTGR     0x10

static char get_iso8859_code(void)
{
  static uint8_t state=0;
  uint8_t s;
  char c;

  while (1) {
    s = get_scan_code();
    if (!s) return 0;
    if (s == 0xF0) {
      state |= BREAK;
    } else if (s == 0xE0) {
      state |= MODIFIER;
    } else {
      if (state & BREAK) {
        if (s == 0x12) {
          state &= ~SHIFT_L;
        } else if (s == 0x59) {
          state &= ~SHIFT_R;
        } else if (s == 0x11 && (state & MODIFIER)) {
          state &= ~ALTGR;
        }
        // CTRL, ALT & WIN keys could be added
        // but is that really worth the overhead?
        state &= ~(BREAK | MODIFIER);
        continue;
      }
      if (s == 0x12) {
        state |= SHIFT_L;
        continue;
      } else if (s == 0x59) {
        state |= SHIFT_R;
        continue;
      } else if (s == 0x11 && (state & MODIFIER)) {
        state |= ALTGR;
      }
      c = 0;
      if (state & MODIFIER) {
        switch (s) {
          case 0x70: c = PS2_INSERT;      break;
          case 0x6C: c = PS2_HOME;        break;
          case 0x7D: c = PS2_PAGEUP;      break;
          case 0x71: c = PS2_DELETE;      break;
          case 0x69: c = PS2_END;         break;
          case 0x7A: c = PS2_PAGEDOWN;    break;
          case 0x75: c = PS2_UPARROW;     break;
          case 0x6B: c = PS2_LEFTARROW;   break;
          case 0x72: c = PS2_DOWNARROW;   break;
          case 0x74: c = PS2_RIGHTARROW;  break;
          case 0x4A: c = '/';             break;
          case 0x5A: c = PS2_ENTER;       break;
          default: break;
        }
      } else if ((state & ALTGR) && keymap->uses_altgr) {
        if (s < PS2_KEYMAP_SIZE)
          c = pgm_read_byte(keymap->altgr + s);
      } else if (state & (SHIFT_L | SHIFT_R)) {
        if (s < PS2_KEYMAP_SIZE)
          c = pgm_read_byte(keymap->shift + s);
      } else {
        if (s < PS2_KEYMAP_SIZE)
          c = pgm_read_byte(keymap->noshift + s);
      }
      state &= ~(BREAK | MODIFIER);
      if (c) return c;
    }
  }
}

bool PS2Keyboard::available() {
  if (CharBuffer || UTF8next) return true;
  CharBuffer = get_iso8859_code();
  if (CharBuffer) return true;
  return false;
}

void PS2Keyboard::clear() {
  CharBuffer = 0;
  UTF8next = 0;
}

uint8_t PS2Keyboard::readScanCode(void)
{
  return get_scan_code();
}

int PS2Keyboard::read() {
  uint8_t result;

  result = UTF8next;
  if (result) {
    UTF8next = 0;
  } else {
    result = CharBuffer;
    if (result) {
      CharBuffer = 0;
    } else {
      result = get_iso8859_code();
    }
    if (result >= 128) {
      UTF8next = (result & 0x3F) | 0x80;
      result = ((result >> 6) & 0x1F) | 0xC0;
    }
  }
  if (!result) return -1;
  return result;
}

int PS2Keyboard::readUnicode() {
  int result;

  result = CharBuffer;
  if (!result) result = get_iso8859_code();
  if (!result) return -1;
  UTF8next = 0;
  CharBuffer = 0;
  return result;
}

PS2Keyboard::PS2Keyboard() {
  // nothing to do here, begin() does it all
}

void PS2Keyboard::begin(uint8_t data_pin, uint8_t irq_pin) {
  
  DataPin = data_pin;
  keymap = &PS2Keymap_German;

  // initialize the pins
#ifdef INPUT_PULLUP
  pinMode(irq_pin, INPUT_PULLUP);
  pinMode(data_pin, INPUT_PULLUP);
#else
  pinMode(irq_pin, INPUT);
  digitalWrite(irq_pin, HIGH);
  pinMode(data_pin, INPUT);
  digitalWrite(data_pin, HIGH);
#endif

  head = 0;
  tail = 0;
  attachInterrupt(digitalPinToInterrupt(irq_pin), ps2interrupt, FALLING);
}
