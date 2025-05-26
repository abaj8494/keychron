/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "keymap_dvorak.h"
#define BASE_LED_INDEX 0
#define L1_LED_INDEX 1
#define L2_LED_INDEX 2
#define FN_LED_INDEX 3

enum custom_keycodes {
    M0 = SAFE_RANGE, // rpi
    M1, // kiyo
    M2, // startx
    M3, // music
    M4, // sudo shutdown now
    M5, // kill tmux window
    M6, // new tmux window
    M7, // previous tmux window
    M8, // next tmux window
    M9, // vol up ncmpcpp
    M10, // vol down ncmpcpp
    M11, // y tap, escape held
    M12, // n tap, ctrl-c held
    M13, // clock
    M14, // exit
    M15, // fullscreen
    M16, // prev workspace
    M17, // next workspace
    M18, //new terminal
    M19, // select
    M20,
    M21,
    M22,
    M23,
    M24,
    M25,
};

enum layers {
    BASE,
    L1,
    L2,
    FN,
};


/* The Matrix is intended to possess the following functionality:
 * NOTE: the mappings assume the OS is in DVORAK, hence the unusual mappings
 *
 * BASE = MUTE, _______, L1, L2, FN
 *        yTapESCheld, NUM_LOCK, DIVIDE, MULTIPLY, SUBTRACT,
 *        nTapCTRLCheld, NP7, NP8, NP9, NP+,
 *        prevTrack, NP4, NP5, NP6,
 *        nextTrack, NP1, NP2, NP3, NPENTER,
 *        play/pause, NP0, PERIOD
 * L1 = MUTE, BASE, _______, L2, FN
 *        rpi, photos, killTERM, spawnTERM, deleteSong,
 *        kiyomi, prevNCMPCPP, topNCMPCPP, nextNCMPCPP, SPACE 
 *        startx, tmuxLEFT, SCREENSAVER, tmuxRIGHT,
 *        music, voldownNCMPCPP, G, volupNCMPCPP, NPENTER,
 *        sudoshutdownnow, play/pauseNCMPCPP, NP8
 * L2 = MUTE, BASE, L1, _______, FN
 *        ncmClock, ncmCLEAR, ncmLYRICS, ncmREPEAT, backspace,
 *        ncmUPALBUM, _______, _______, _______, ripDisc 
 *        ncmDOWNALBUM, _______, _______, _______,
 *        ncmUPARTIST, _______, _______, _______, ncmINFO,
 *        ncmDOWNARTIST, ncmSELECT, ncmJUMPTOCURRSONG
 * FN = MUTE, BASE, L1, L2, _______
 *        BTdev1, rgbMODE, rgbBright+, Hue+, _______,
 *        BTdev2, rgbRevMode, rgbBright-, Hue-, _______, 
 *        BTdev3, rgbSat+, rgbSpeed+, fullScreen,
 *        2GHzMode, rgbSat-, rgbSpeed-, _______, _______,
 *        _______, toggleRGB, _______
 *
 */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tenkey_27(
        KC_MUTE, _______, TO(L1), TO(L2), TO(FN),
        M11,	 KC_NUM, KC_PSLS,KC_PAST,KC_PMNS,
        M12,	 KC_P7,	 KC_P8,	 KC_P9,	 KC_PPLS,
        KC_MEDIA_NEXT_TRACK,	 KC_P4,	 KC_P5,	 KC_P6,
        KC_MEDIA_PREV_TRACK,	 KC_P1,	 KC_P2,	 KC_P3,	 KC_ENTER,
        KC_MEDIA_PLAY_PAUSE,  KC_P0,          KC_PDOT         ),

    [L1] = LAYOUT_tenkey_27(
        KC_F, TO(BASE), _______, TO(L2), TO(FN),
        M0, M14, M5, M6, KC_B,
        M1, KC_M, KC_U, KC_COMMA, KC_SPACE,
        M2, M7, M15, M8,
        M3, M9, KC_G, M10, KC_ENTER,
        M4, KC_R,          KC_P8          ),

    [L2] = LAYOUT_tenkey_27(
        _______, TO(BASE), TO(L1), _______, TO(FN),
        M13, KC_I, KC_P, KC_O, KC_BSPC,
	KC_MINUS, _______, _______, _______, M12,
        KC_EQUAL, _______, _______, _______,
        KC_UNDERSCORE, _______, _______, _______, KC_G,
        KC_PLUS, KC_F,          KC_S          ),

    [FN] = LAYOUT_tenkey_27(
        M18, TO(BASE), TO(L1), TO(L2), _______,
        BT_HST1, RGB_MOD, RGB_VAI, RGB_HUI, M14,
        BT_HST2, RGB_RMOD,RGB_VAD, RGB_HUD, _______,
        BT_HST3, RGB_SAI, RGB_SPI, M15,
        P2P4G, RGB_SAD, RGB_SPD, M20, _______,
        _______, RGB_TOG,          M20          )

};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [L1]   = {ENCODER_CCW_CW(KC_V, KC_C)},
    [L2]   = {ENCODER_CCW_CW(KC_SLASH, KC_DOT)},
    [FN]   = {ENCODER_CCW_CW(M16, M17)}
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    static uint16_t pressed_time_m11 = 0;
    static uint16_t pressed_time_m12 = 0;
    switch (keycode) {
	case M0: // prints rpi
            if (record->event.pressed) {
                SEND_STRING_DELAY("org", 10); 
		
            }
            return false; // Skip further processing of this keycode
	case M1: // prints kiyo
	    if (record->event.pressed) {
		SEND_STRING_DELAY("vgts", 10);
	    }
            return false;
        case M2: // prints startx
	    if (record->event.pressed) {
	        SEND_STRING_DELAY(";kaokb", 10);
	    }
	    return false;
	case M3: // opens a new terminal and runs the music script
	    if (record->event.pressed) {
		// opens a new terminal
		register_code(KC_LGUI);        // Press Windows (Left GUI)
		register_code(KC_ENT);         // Press Enter
		unregister_code(KC_ENT);       // Release Enter
		unregister_code(KC_LGUI);      // Release Windows (Left GUI)

		wait_ms(10000);
		SEND_STRING_DELAY("mf;gi", 10);
	    }
	    return false;
	case M4:
	    if (record->event.pressed) {
		SEND_STRING_DELAY(";fhs ;jfkhs,l ls,", 10);
	    }
	    return false;
	case M5: // Kill Tmux window:  Ctrl+N & 
	    if (record->event.pressed) {
		SEND_STRING_DELAY(SS_LCTL("n") "b", 10);
	    }
	    return false;
	case M6: // New Tmux window:   Ctrl+N c
	    if (record->event.pressed) {
		SEND_STRING_DELAY(SS_LCTL("n") "i", 10);
	    }
	    return false;
	case M7: // Previous window:   Ctrl+N p
	    if (record->event.pressed) {
		SEND_STRING_DELAY(SS_LCTL("n") "r", 10);
	    }
	    return false;
	case M8: // Next window:       Ctrl+N n
	    if (record->event.pressed) {
		SEND_STRING_DELAY(SS_LCTL("n") "l", 10);
	    }
	    return false;
	case M9: // vol up ncmpcpp
	    if (record->event.pressed) {
		SEND_STRING_DELAY(SS_LSFT("w"), 10);
	    }
	    return false;
	case M10: // vol down ncmpcpp
	    if (record->event.pressed) {
		SEND_STRING_DELAY(SS_LSFT("e"), 10);
	    }
	    return false;
        case M11:
            if (record->event.pressed) {
                // Record the time when M11 is pressed
                pressed_time_m11 = timer_read();
            } else {
                // Key is released — decide tap or hold
                if (timer_elapsed(pressed_time_m11) < TAPPING_TERM) {
                    // Tapped quickly -> 'y'
                    tap_code(KC_T);
                } else {
                    // Held -> Escape
                    tap_code(KC_ESC);
                }
            }
            return false; // We handled M11 completely
        case M12:
            if (record->event.pressed) {
                // Record the time when M12 is pressed
                pressed_time_m12 = timer_read();
            } else {
                // Key is released — decide tap or hold
                if (timer_elapsed(pressed_time_m12) < TAPPING_TERM) {
                    // Tapped quickly -> 'n'
                    tap_code(KC_L);
                } else {
                    // Held -> Ctrl-C
                    tap_code16(C(KC_I));
                }
            }
            return false; // We handled M12 completely
        case M13:
            if (record->event.pressed) {
                SEND_STRING("I");
            }
            return false;
        case M14:
            if (record->event.pressed) {
                SEND_STRING_DELAY("dbgk", 20);
            }
            return false; // Skip further processing of this keycod
        case M15: // Command + F
            if (record->event.pressed) {
                tap_code16(G(KC_Y));
            }
            return false;

        case M16: // Command + Tab
            if (record->event.pressed) {
                tap_code16(G(KC_TAB));
            }
            return false;

        case M17: // Command + Shift + Tab
            if (record->event.pressed) {
                tap_code16(G(S(KC_TAB)));
            }
            return false;

        case M18: // Command + Enter
            if (record->event.pressed) {
		register_code(KC_LGUI);        // Press Windows (Left GUI)
		register_code(KC_ENT);         // Press Enter
		unregister_code(KC_ENT);       // Release Enter
		unregister_code(KC_LGUI);      // Release Windows (Left GUI)
            }
            return false;
        case M19: // prints startx
	    if (record->event.pressed) {
	        SEND_STRING_DELAY("b;dk }hrm;", 10);
	    }
	    return false;
        case M20: // prints startx
	    if (record->event.pressed) {
	        SEND_STRING_DELAY("b;dk 'hrm;", 10);
	    }
	    return false;

        default:
            return true;
    }
    return true;

}



bool set_layer_indicators(void) {
    switch (get_highest_layer(layer_state)) {
        case BASE:
            printf("Matched base, rgb_matrix_indicators_user\n");
            // rgb_matrix_set_color(BASE_LED_INDEX,  255, 255, 255); // white  // circle
            rgb_matrix_set_color(BASE_LED_INDEX,  212, 0, 255); // purp  // circle
            rgb_matrix_set_color(L1_LED_INDEX, 0, 0, 0);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX,  0, 0, 0);  // square
            rgb_matrix_set_color(FN_LED_INDEX,  0, 0, 0);  // cross
            break;
        case L1:
            printf("Matched L1, rgb_matrix_indicators_user\n");
            rgb_matrix_set_color(BASE_LED_INDEX,  0, 0, 0);  // circle
            // rgb_matrix_set_color(L1_LED_INDEX, 255, 255, 255);  // triangle
            rgb_matrix_set_color(L1_LED_INDEX,  212, 0, 255);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX,  0, 0, 0);  // square
            rgb_matrix_set_color(FN_LED_INDEX,  0, 0, 0);  // cross
            break;
        case L2:
            printf("Matched L2, rgb_matrix_indicators_user\n");
            rgb_matrix_set_color(BASE_LED_INDEX,  0, 0, 0);  // circle
            rgb_matrix_set_color(L1_LED_INDEX,  0, 0, 0);  // triangle
            // rgb_matrix_set_color(L2_LED_INDEX, 255, 255, 255);  // square
            rgb_matrix_set_color(L2_LED_INDEX,  212, 0, 255);  // square
            rgb_matrix_set_color(FN_LED_INDEX,  0, 0, 0);  // cross0
            break;
        case FN:
            printf("Matched FN, rgb_matrix_indicators_user\n");
            rgb_matrix_set_color(BASE_LED_INDEX,  0, 0, 0);  // circle
            rgb_matrix_set_color(L1_LED_INDEX,  0, 0, 0);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX,  0, 0, 0);  // square
            // rgb_matrix_set_color(FN_LED_INDEX, 255, 255, 255);  // cross
             rgb_matrix_set_color(FN_LED_INDEX,  212, 0, 255);  // cross
            break;
   }
   return true;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    // Put your existing code inside or just call your helper:
    return set_layer_indicators();
}
#endif

