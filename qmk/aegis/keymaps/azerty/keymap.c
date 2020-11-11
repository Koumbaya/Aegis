#include "aegis.h"
#include "keymap_french.h"
#include <avr/io.h>
#include <timer.h>
#include "pincontrol.h"
#include <string.h>
#include "action_layer.h"
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif
#define _QWERTY 0
#define _RAISE 1
#define _LOWER 2
#define _ADJUST 3

#define SOLENOID_DEFAULT_DWELL 12 
#define SOLENOID_MAX_DWELL 100
#define SOLENOID_MIN_DWELL 4
#define SOLENOID_PIN F4

bool solenoid_enabled = true;
bool solenoid_on = false;
bool solenoid_buzz = false;
bool solenoid_buzzing = false;
volatile uint32_t solenoid_start = 0;
uint8_t solenoid_dwell = SOLENOID_DEFAULT_DWELL;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RAISE,
  LOWER,
  ADJUST,
  BACKLIT,
  SOLENOID_TOG,
  SOLENOID_DWELL_MINUS,
  SOLENOID_DWELL_PLUS,
  SOLENOID_BUZZ_ON,
  SOLENOID_BUZZ_OFF
};
// FR_OVRR, FR_PLUS,
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
  KC_ESC,           FR_A,   FR_Z,   KC_E,   KC_R,   KC_T,            KC_Y,  KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPACE,   \
  LSFT_T(KC_TAB),   FR_Q,   KC_S,   KC_D,   KC_F,   KC_G,            KC_H,  KC_J,   KC_K,   KC_L,   FR_M,   KC_DELETE,   \
  KC_LCTRL,         FR_W,   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,  KC_M,   KC_LEFT,   KC_UP,   KC_DOWN,   KC_RIGHT,   \
               KC_LGUI,   MO(_LOWER),   LALT_T(KC_SPC),             RSFT_T(KC_ENT),   MO(_RAISE),   MO(_ADJUST)\
),   
	KEYMAP(
    FR_AMP, FR_EACU, FR_QUOT, FR_APOS, FR_LPRN, FR_MINS,               FR_EGRV, FR_UNDS, FR_CCED, FR_AGRV, FR_RPRN, FR_EQL,
    LSFT_T(KC_TAB),   KC_NO,   KC_NO, KC_BSLS, KC_TILD, KC_NUHS,               KC_LCBR, KC_QUOT, KC_BSLS, KC_LBRC, KC_RBRC, KC_DEL,
    KC_LCTRL, KC_NUBS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                 KC_NO,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_NO, 
                               _______, _______, _______,               _______, _______, _______
),

	KEYMAP(
         FR_1,   FR_2,    FR_3,    FR_4,    FR_5,    FR_6,                 FR_7,    FR_8,    FR_9,    FR_0, FR_OVRR, FR_PLUS, \
      LSFT_T(KC_TAB),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_DEL, \
      KC_LCTRL, KC_F11,  KC_F12, KC_COPY, KC_PSTE,   KC_NO,                KC_NO, KC_COMM, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                                _______, _______, _______,              _______, _______, _______ \
),

	KEYMAP(
      _______, FR_TILD, FR_HASH, ALGR(KC_E), FR_LCBR, FR_LBRC,          FR_GRV, FR_BSLS, FR_CCIRC,   FR_AT, FR_RBRC, FR_RCBR, \
      RGB_MOD, RGB_TOG, RGB_VAI,    RGB_SAI, RGB_HUI, FR_LCBR,         _______, FR_PERC,  _______, _______, _______, FR_RCBR, \
      RGB_RMOD, _______, RGB_VAD,    RGB_SAD, RGB_HUD, FR_LPRN,         FR_PIPE, FR_QUES,   FR_DOT, FR_SLSH, FR_SECT, _______, \
                                    _______, _______, _______,         _______, _______, _______
),
  KEYMAP(
    _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG,                _______, _______, _______, _______, _______, RESET,
    _______,    _______ , _______, _______, _______,  RGB_MOD,     _______, _______,  _______, _______,  _______, EEP_RST,
    _______, RGB_RMOD,RGB_HUD,RGB_SAD, RGB_VAD, RGB_RMOD,                _______, _______, _______, _______, _______, _______,
                                     _______, _______, _______,        _______, _______, _______
    )

};

const uint16_t PROGMEM fn_actions[] = {

};

void solenoid_buzz_on(void) {
  solenoid_buzz = true;
}

void solenoid_buzz_off(void) {
  solenoid_buzz = false;
}

void solenoid_dwell_minus(void) {
  if (solenoid_dwell > 0) solenoid_dwell--;
}

void solenoid_dwell_plus(void) {
  if (solenoid_dwell < SOLENOID_MAX_DWELL) solenoid_dwell++;
}

void solenoid_toggle(void) {
  solenoid_enabled = !solenoid_enabled;
}

void solenoid_stop(void) {
  digitalWrite(SOLENOID_PIN, PinLevelLow); 
  solenoid_on = false;
  solenoid_buzzing = false;
}

void solenoid_fire(void) {
  if (!solenoid_enabled) return;

  if (!solenoid_buzz && solenoid_on) return;
  if (solenoid_buzz && solenoid_buzzing) return;

  solenoid_on = true;
  solenoid_buzzing = true;
  solenoid_start = timer_read32();
  digitalWrite(SOLENOID_PIN, PinLevelHigh);
}

void solenoid_check(void) {
  uint32_t elapsed = 0;

  if (!solenoid_on) return;

  elapsed = timer_elapsed32(solenoid_start);

  //Check if it's time to finish this solenoid click cycle 
  if (elapsed > solenoid_dwell) {
    solenoid_stop();
    return;
  }

  //Check whether to buzz the solenoid on and off
  if (solenoid_buzz) {
    if (elapsed / SOLENOID_MIN_DWELL % 2 == 0){
      if (!solenoid_buzzing) {
        solenoid_buzzing = true;
        digitalWrite(SOLENOID_PIN, PinLevelHigh);
      }
    }
    else {
      if (solenoid_buzzing) {
        solenoid_buzzing = false;
        digitalWrite(SOLENOID_PIN, PinLevelLow);
      }
    }
  }

}

void solenoid_setup(void) {
  pinMode(SOLENOID_PIN, PinDirectionOutput);
  digitalWrite(SOLENOID_PIN, PinLevelLow);
  timer_init();
}


int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  solenoid_setup();
	#ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(false);   // turns on the display
    #endif
}


// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void matrix_scan_user(void) {
  solenoid_check();
	  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (true) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    solenoid_fire();
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case SOLENOID_TOG:
      if (record->event.pressed) {
        solenoid_toggle();
      }
      break;
    case SOLENOID_DWELL_MINUS:
      if (record->event.pressed) {
        solenoid_dwell_minus();
      }
      break;
    case SOLENOID_DWELL_PLUS:
      if (record->event.pressed) {
        solenoid_dwell_plus();
      }
      break;
    case SOLENOID_BUZZ_ON:
      if (record->event.pressed) {
        solenoid_buzz_on();
      }
      break;
    case SOLENOID_BUZZ_OFF:
      if (record->event.pressed) {
        solenoid_buzz_off();
      }
      break;
  }
  return true;
}


void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}