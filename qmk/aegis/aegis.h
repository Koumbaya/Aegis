#ifndef KB_H
#define KB_H

#include "quantum.h"
//include "rev1.h"

#ifdef SSD1306OLED
    #include "ssd1306.h"
#endif

#ifdef USE_I2C
    #include <stddef.h>
    #ifdef __AVR__
        #include <avr/interrupt.h>
        #include <avr/io.h>
    #endif
#endif

#define KEYMAP( \
	K00, K10, K01, K11, K02, K12,     K03, K13, K04, K14, K05, K15, \
	K20, K30, K21, K31, K22, K32,     K23, K33, K24, K34, K25, K35, \
	K40, K50, K41, K51, K42, K52,     K43, K53, K44, K54, K45, K55, \
	                K06, K26, K46,    K16, K36, K56 \
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06 }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16 }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26 }, \
	{ K30,   K31,   K32,   K33,   K34,   K35,   K36 }, \
	{ K40,   K41,   K42,   K43,   K44,   K45,   K46 }, \
	{ K50,   K51,   K52,   K53,   K54,   K55,   K56 }  \
}

#endif

