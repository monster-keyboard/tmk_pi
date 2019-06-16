#include "keymap_common.h"

#define ___ NO
#define KC____ KC_NO
const uint8_t keymaps[32][MATRIX_ROWS][MATRIX_COLS] = {
{//layer 0
       /*___1,___2,___3,___4,___5,___6,___7,___8,___9,__10,__11,__12,__13,__14,__15,__16,__17,__18,__19,__20,__21,__22,__23,__24*/
/*1*/ KR( ESC, ___,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12,PSCR,SLCK,PAUS, ___, ___, ___, ___, ___, ___, ___),
/*2*/ KR( GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSPC, INS,HOME,PGUP,NLCK,PSLS,PAST,PMNS, ___, ___, ___),
/*3*/ KR( TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSLS, DEL, END,PGDN,  P7,  P8,  P9, ___, ___, ___, ___),
/*4*/ KR(CAPS,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT, ___, ENT, ___, ___, ___,  P4,  P5,  P6,PPLS, ___, ___, ___), 
/*5*/ KR(LSFT,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH, ___, ___,RSFT, ___,  UP, ___,  P1,  P2,  P3, ___, ___, ___, ___), 
/*6*/ KR(LCTL,LGUI,LALT, ___, ___, SPC, ___, ___, ___, ___,RALT,RGUI,MENU,RCTL,RGHT,DOWN,LEFT,  P0, ___,PDOT,PENT, ___, ___, ___),
/*7*/ KR( ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___),
/*8*/ KR( ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___),
}
};

const action_t fn_actions[] = {
    /* Poker Layout */
    [0] = ACTION_LAYER_MOMENTARY(6),  // to Fn overlay
    [1] = ACTION_LAYER_TOGGLE(4),     // toggle arrow overlay
    [2] = ACTION_LAYER_TOGGLE(5),     // toggle Esc overlay
    [3] = ACTION_MODS_KEY(MOD_RCTL|MOD_RSFT, KC_ESC), // Task(RControl,RShift+Esc)
    [4] = ACTION_LAYER_MOMENTARY(7),  // to Layout selector
    [5] = ACTION_DEFAULT_LAYER_SET(0),  // set qwerty layout
    [6] = ACTION_DEFAULT_LAYER_SET(1),  // set colemak layout
    [7] = ACTION_DEFAULT_LAYER_SET(2),  // set dvorak layout
    [8] = ACTION_DEFAULT_LAYER_SET(3),  // set workman layout
};
