#include QMK_KEYBOARD_H

#define BR_LARNG RALT(KC_LBRC)    // å
#define BR_UARNG RALT(S(KC_LBRC)) // Å
#define BR_LOUML RALT(KC_SCLN)    // ö
#define BR_UOUML RALT(S(KC_SCLN)) // Ö
#define BR_LAUML RALT(KC_QUOT)    // ä
#define BR_UAUML RALT(S(KC_QUOT)) // Ä

#define BR_ESCL LT(3, KC_ESC)

#define ________ KC_TRNS
#define xxxxxxxx KC_NO

#define LAYOUT LAYOUT_planck_mit

enum custom_keycodes {
    BR_ARWSM = SAFE_RANGE,
    BR_ARWLG,
    BR_NEQL,
    BR_PDOT,
    BR_ALT,
    BR_T_ALT,
};

enum layers {
    TOP = 0,
    NPAD,
    LWR,
    RSE,
    FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [TOP] = LAYOUT(
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,
    KC_LCTL,  MO(FN),   BR_ALT,   KC_LGUI,  MO(LWR),      KC_SPC,         MO(RSE),  KC_LEFT,  KC_UP,    KC_DOWN,  KC_RIGHT
  ),

  [NPAD] = LAYOUT(
    ________, ________, ________, ________, ________, ________, KC_7,     KC_8,     KC_9,     KC_PSLS,  KC_PAST,  ________,
    ________, ________, ________, ________, ________, ________, KC_4,     KC_5,     KC_6,     KC_PMNS,  KC_PPLS,  ________,
    ________, ________, ________, ________, ________, ________, KC_1,     KC_2,     KC_3,     BR_PDOT,  ________, ________,
    ________, TG(NPAD), ________, ________, TG(NPAD),      ________,      KC_0,     KC_PEQL,  ________, ________, ________
  ),

  [LWR] = LAYOUT(
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      BR_LARNG,
    ________, KC_MRWD,  KC_MPLY,  KC_MFFD,  ________, ________, ________, ________, ________, ________,  BR_LOUML, BR_LAUML,
    ________, KC_MUTE,  KC_VOLD,  KC_VOLU,  ________, ________, ________, ________, ________, ________,  ________, ________,
    ________, ________, ________, ________, ________,      ________,      ________, ________, ________,  ________, ________
  ),

  // Raise
  [RSE] = LAYOUT(
    KC_GRV,   KC_EXLM,  KC_AT,    KC_HASH, KC_DLR,    KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_DEL,
    ________, KC_MINUS, KC_EQUAL, xxxxxxxx, ________, ________, ________, ________, KC_LPRN,  KC_RPRN,  KC_LBRC,  KC_RBRC,
    ________, BR_NEQL,  BR_ARWSM, BR_ARWLG, ________, ________, ________, ________, KC_LCBR,  KC_RCBR,  KC_BSLS,  KC_PIPE,
    ________, ________, ________, ________, ________,      ________,      ________, ________, ________, ________, ________
  ),

  // Fn
  [FN] = LAYOUT(
    ________, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    ________, ________, ________, ________, KC_DEL,
    ________, KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   ________, ________, ________, ________, ________,
    ________, ________, ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
    ________, ________, BR_T_ALT, ________, TG(NPAD),       ________,     TG(NROW), KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END
  )
};

// TODO: RALT should be a toggle

// void matrix_init_user(void) {
// }

// void matrix_scan_user(void) {
// }

#if AUDIO_ENABLE
float tone_ralt_on[][2]     = SONG(SCROLL_LOCK_ON_SOUND);
float tone_ralt_off[][2]     = SONG(SCROLL_LOCK_OFF_SOUND);
#endif

bool is_ralt = false;

void process_alt(keyrecord_t *record) {
    uint16_t keycode = KC_LALT;

    if (is_ralt) {
        keycode = KC_RALT;
    }

    if (record->event.pressed) {
        register_code(keycode);
    } else {
        unregister_code(keycode);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == BR_ALT) {
        process_alt(record);
        return false;
    }

    if (keycode == BR_T_ALT && record->event.pressed) {
        is_ralt = !is_ralt;

        #ifdef AUDIO_ENABLE
          stop_all_notes();
          if (is_ralt) {
            PLAY_SONG(tone_ralt_on);
          } else {
            PLAY_SONG(tone_ralt_off);
          }
        #endif
        return false;
    }

    if (record->event.pressed) {
        uint8_t is_shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

        if (is_shifted) switch (keycode) {
        case BR_ARWSM:
            SEND_STRING("<-");
            return false;
        case BR_ARWLG:
            SEND_STRING("<=");
            return false;
        case BR_NEQL:
            SEND_STRING("!==");
            return false;
        case BR_PDOT:
            SEND_STRING(SS_TAP(X_KP_DOT));
            return false;
        case KC_BSLS:
            SEND_STRING("|>");
            return false;
        }

        switch (keycode) {
        case BR_ARWSM:
            SEND_STRING("->");
            return false;
        case BR_ARWLG:
            SEND_STRING("=>");
            return false;
        case BR_NEQL:
            SEND_STRING("!=");
            return false;
        case BR_PDOT:
            SEND_STRING(".");
            return false;
        }
    }

    return true;
};
