 
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings

//extern rgblight_config_t rgblight_config;
#endif

 
extern uint8_t is_master;
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _GAMING,
  _GAMING2
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  TOGGLE_ALTTAB,
  //RGBRST,
    //MACRO1,
  //MACRO2,
  GAMING,
  GAMING2
};

enum {
    TD_CAPLOCK,
    TD_LGUICTRL,
    TD_ESC_FORGAMING,
    TD_GAMING_LAYER

};


typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_1_TAP,
    TD_1_HOLD,
    TD_2_TAP,
    TD_2_HOLD,
    TD_3_TAP,
    TD_3_HOLD
} td_state_t;

 
// Create a global instance of the tapdance state type
static td_state_t td_state;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,             KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     TD(TD_CAPLOCK), KC_Z,            KC_X,    KC_C,    KC_V,    KC_B,                 KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, MT(MOD_LSFT, KC_ENT),
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            TD(TD_LGUICTRL), LOWER, MT(MOD_LALT,KC_SPC),              KC_SPC, RAISE, KC_LALT
                                      //|--------------------------|  |--------------------------|


  ),

  [_LOWER] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     TOGGLE_ALTTAB, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_F6,                     KC_MINS, KC_EQL, KC_LBRC,  KC_RBRC, KC_PIPE, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, XXXXXXX, KC_F2, XXXXXXX, LALT(KC_F4), LALT(KC_D),                  RALT(KC_N), LGUI(LCTL(KC_LEFT)) , LALT(LCTL(KC_DOWN)), LALT(LCTL(KC_UP)), LGUI(LCTL(KC_RIGHT)), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         RCTL(KC_F), KC_TRNS, XXXXXXX,    XXXXXXX, RAISE, KC_RALT
                                      //|--------------------------|  |--------------------------|
  ),


  [_RAISE] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_PSCR, KC_F1  , KC_F2   , KC_F3 , KC_F4  , KC_F5  ,                      KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MUTE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, KC_F6  , KC_F7   , KC_F8 , KC_F9  , KC_F10 ,                       XXXXXXX , KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_F11 , KC_F12  , KC_F13 , KC_F14 , KC_F15 ,                      XXXXXXX ,KC_HOME,  KC_PGDN, KC_PGUP, KC_END, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, LOWER, XXXXXXX,    XXXXXXX, KC_TRNS, XXXXXXX
                                      //|--------------------------|  |--------------------------|
  ),

  [_ADJUST] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_GRV, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_PWR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   RESET,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 TO(_GAMING), TO(_GAMING2),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, KC_TRNS, XXXXXXX,    XXXXXXX, KC_TRNS, XXXXXXX
                                      //|--------------------------|  |--------------------------|
  ),
  [_GAMING] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     TD(TD_ESC_FORGAMING),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    TD(TD_GAMING_LAYER),                  KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, KC_ENT,
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL, KC_SPC, MT(MOD_LALT,TO(_QWERTY)),     TO(_QWERTY), RAISE, KC_RALT
                                      //|--------------------------|  |--------------------------|


  ),
  [_GAMING2] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                 KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, MT(MOD_LSFT, KC_ENT),
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            TD(TD_LGUICTRL), LOWER, KC_SPC,              TO(_QWERTY), RAISE, KC_RALT
                                      //|--------------------------|  |--------------------------|


  )

  };



  // Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_1_TAP;
        else return TD_1_HOLD;
    }

    if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_2_TAP;
        else return TD_2_HOLD;
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_3_TAP;
        else return TD_3_HOLD;
    }
    return TD_NONE;

}


//Hacer que reciba lista de keycodes para ahorrar espacios

// Handle the possible states for each tapdance keycode you define:

void escgaming_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_3_TAP: 
            register_code16(KC_ESC);
            break;
        case TD_1_HOLD: 
            register_code16(KC_TAB);
            break;
        case TD_1_TAP: 
            register_code16(KC_TAB);
            break;
        default:
            break;
    }
} 

void escgaming_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_3_TAP: 
            unregister_code16(KC_ESC);
            break;
        case TD_1_HOLD: 
            unregister_code16(KC_TAB);
            break;
        case TD_1_TAP: 
            unregister_code16(KC_TAB);
            break;
        default:
            break;
    }
}



void gaming_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_1_TAP: 
            register_code16(KC_B);
            break;
        case TD_1_HOLD:
            register_code16(KC_B);
            break;
        case TD_3_TAP:
            register_code16(TO(_QWERTY));
            break;
        default:
            break;
    }
} 

void gaming_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_1_TAP: 
            unregister_code16(KC_B);
            break;
        case TD_1_HOLD:
            unregister_code16(KC_B);
            break;
        case TD_3_TAP:
            break;
        default:
            break;
    }
} 

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_LGUICTRL] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LGUI),
    [TD_ESC_FORGAMING] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, escgaming_finished, escgaming_reset),
    [TD_GAMING_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gaming_layer_finished, gaming_layer_reset)
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}




#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif


//int RGB_current_mode;
//int RGB_current_val;
//void matrix_init_user(void) {
//    #ifdef RGBLIGHT_ENABLE
//      RGB_current_mode = rgblight_config.mode;
//      RGB_current_mode = rgblight_config.val;
//    #endif
//}

//void rgb_matrix_indicators_user(void) {
//  #ifdef RGB_MATRIX_ENABLE
//  switch (biton32(layer_state)) {
//    case _RAISE:
//      for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
//          rgb_matrix_set_color(i, lk255, 0, 0);
//      }
//      break;
//
//    case _LOWER:
//      for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
//         rgb_matrix_set_color(i, 0, 0, 100);
//      }
//      break;
//
//    default:
//        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
//                  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
//          rgb_matrix_set_color(i, 0, RGB_current_val*255, 0);
//      }
//       }
//      break;
//  }
//  #endif
//}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_logo(void) {
    
    
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("     "), false);
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
 
} 


bool oled_task_user(void) {
    // Renders the current keyboard state (layers and mods)
    render_logo();
    //render_space();
    //render_layer_state();
    //render_space();
    //render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    //render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    return false;
}

//void render_space(void) {
//    oled_write_P(PSTR("     "), false);
//}

//void render_layer_state(void) {
//    static const char PROGMEM default_layer[] = {
//        0x20, 0x94, 0x95, 0x96, 0x20,
//        0x20, 0xb4, 0xb5, 0xb6, 0x20,
//        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
//    static const char PROGMEM raise_layer[] = {
//        0x20, 0x97, 0x98, 0x99, 0x20,
//        0x20, 0xb7, 0xb8, 0xb9, 0x20,
//        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
//    static const char PROGMEM lower_layer[] = {
//        0x20, 0x9a, 0x9b, 0x9c, 0x20,
//        0x20, 0xba, 0xbb, 0xbc, 0x20,
//        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
//    static const char PROGMEM adjust_layer[] = {
//        0x20, 0x9d, 0x9e, 0x9f, 0x20,
//        0x20, 0xbd, 0xbe, 0xbf, 0x20,
//        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
//    if(layer_state_is(_ADJUST)) {
//        oled_write_P(adjust_layer, false);
//    } else if(layer_state_is(_LOWER)) {
//        oled_write_P(lower_layer, false);
//    } else if(layer_state_is(_RAISE)) {
//        oled_write_P(raise_layer, false);
//    } else {
//        oled_write_P(default_layer, false);
//    }
//}


//void render_mod_status_gui_alt(uint8_t modifiers) {
//    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
//    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
//    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
//    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};
//
//    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
//    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
//    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
//    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};
//
//    // fillers between the modifier icons bleed into the icon frames
//    static const char PROGMEM off_off_1[] = {0xc5, 0};
//    static const char PROGMEM off_off_2[] = {0xc6, 0};
//    static const char PROGMEM on_off_1[] = {0xc7, 0};
//    static const char PROGMEM on_off_2[] = {0xc8, 0};
//    static const char PROGMEM off_on_1[] = {0xc9, 0};
//    static const char PROGMEM off_on_2[] = {0xca, 0};
//    static const char PROGMEM on_on_1[] = {0xcb, 0};
//    static const char PROGMEM on_on_2[] = {0xcc, 0};
//
//    if(modifiers & MOD_MASK_GUI) {
//        oled_write_P(gui_on_1, false);
//    } else {
//        oled_write_P(gui_off_1, false);
//    }
//
//    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
//        oled_write_P(on_on_1, false);
//    } else if(modifiers & MOD_MASK_GUI) {
//        oled_write_P(on_off_1, false);
//    } else if(modifiers & MOD_MASK_ALT) {
//        oled_write_P(off_on_1, false);
//    } else {
//        oled_write_P(off_off_1, false);
//    }
//
//    if(modifiers & MOD_MASK_ALT) {
//        oled_write_P(alt_on_1, false);
//    } else {
//        oled_write_P(alt_off_1, false);
//    }
//
//    if(modifiers & MOD_MASK_GUI) {
//        oled_write_P(gui_on_2, false);
//    } else {
//        oled_write_P(gui_off_2, false);
//    }
//
//    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
//        oled_write_P(on_on_2, false);
//    } else if(modifiers & MOD_MASK_GUI) {
//        oled_write_P(on_off_2, false);
//    } else if(modifiers & MOD_MASK_ALT) {
//        oled_write_P(off_on_2, false);
//    } else {
//        oled_write_P(off_off_2, false);
//    }
//
//    if(modifiers & MOD_MASK_ALT) {
//        oled_write_P(alt_on_2, false);
//    } else {
//        oled_write_P(alt_off_2, false);
//    }
//}

//void render_mod_status_ctrl_shift(uint8_t modifiers) {
//    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
//    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
//    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
//    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};
//
//    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
//    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
//    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
//    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};
//
//    // fillers between the modifier icons bleed into the icon frames
//    static const char PROGMEM off_off_1[] = {0xc5, 0};
//    static const char PROGMEM off_off_2[] = {0xc6, 0};
//    static const char PROGMEM on_off_1[] = {0xc7, 0};
//    static const char PROGMEM on_off_2[] = {0xc8, 0};
//    static const char PROGMEM off_on_1[] = {0xc9, 0};
//    static const char PROGMEM off_on_2[] = {0xca, 0};
//    static const char PROGMEM on_on_1[] = {0xcb, 0};
//    static const char PROGMEM on_on_2[] = {0xcc, 0};
//
//    if(modifiers & MOD_MASK_CTRL) {
//        oled_write_P(ctrl_on_1, false);
//    } else {
//        oled_write_P(ctrl_off_1, false);
//    }
//
//    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
//        oled_write_P(on_on_1, false);
//    } else if(modifiers & MOD_MASK_CTRL) {
//        oled_write_P(on_off_1, false);
//    } else if(modifiers & MOD_MASK_SHIFT) {
//        oled_write_P(off_on_1, false);
//    } else {
//        oled_write_P(off_off_1, false);
//    }
//
//    if(modifiers & MOD_MASK_SHIFT) {
//        oled_write_P(shift_on_1, false);
//    } else {
//        oled_write_P(shift_off_1, false);
//    }
//
//    if(modifiers & MOD_MASK_CTRL) {
//        oled_write_P(ctrl_on_2, false);
//    } else {
//        oled_write_P(ctrl_off_2, false);
//    }
//
//    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
//        oled_write_P(on_on_2, false);
//    } else if(modifiers & MOD_MASK_CTRL) {
//        oled_write_P(on_off_2, false);
//    } else if(modifiers & MOD_MASK_SHIFT) {
//        oled_write_P(off_on_2, false);
//    } else {
//        oled_write_P(off_off_2, false);
//    }
//
//    if(modifiers & MOD_MASK_SHIFT) {
//        oled_write_P(shift_on_2, false);
//    } else {
//        oled_write_P(shift_off_2, false);
//    }
//}


#endif






bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_tab_toggled;
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        // update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        // update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        unregister_code(KC_LALT);
        is_tab_toggled ^= 1;

      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case TOGGLE_ALTTAB:
            if (record->event.pressed) {                    
                if (is_tab_toggled) { 
                    is_tab_toggled ^= 1;
                    register_code(KC_LALT);
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);                                                                                                                                                  
                } else { 
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                }
            }
        return false;
        
//        case MACRO1:
//    if (record->event.pressed) {  
//            SEND_STRING("Aqui pones lo que quieras en el macro 1");
//        } else {
//            
//        }
//        return false;
//         case MACRO2:
//    if (record->event.pressed) {
//            SEND_STRING("Aqui pones lo que quieras en el macro 2");
//        } else {
//            
//        }
//        return false;    

//    case RGBRST:
//      #ifdef RGBLIGHT_ENABLE
//        if (record->event.pressed) {
//          eeconfig_update_rgblight_default();
//          rgblight_enable();
//          RGB_current_mode = rgblight_config.mode;
//        }
//      #endif
//      #ifdef RGB_MATRIX_ENABLE
//        if (record->event.pressed) {
//          eeconfig_update_rgb_matrix_default();
//          rgb_matrix_enable();
//        }
//      #endif
//      break;

  }
  return true;
}

