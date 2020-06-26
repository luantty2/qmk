#pragma once

#ifndef KEYBOARDS_CANDY_BLE_H_
#define KEYBOARDS_CANDY_BLE_H_

#include "quantum.h"

#define LAYOUT( \
  	K00,                \
  	K10, K11, K12, K13, \
  	K20, K21, K22, K23, \
  	K30, K31, K32, K33, \
  	K40, K41, K42, K43  \
  ) { \
  	{ K00,   KC_NO, KC_NO, KC_NO }, \
  	{ K10,   K11,   K12,   K13 }, \
  	{ K20,   K21,   K22,   K23 }, \
  	{ K30,   K31,   K32,   K33 }, \
  	{ K40,   K41,   K42,   K43 }  \
  }
#endif /* KEYBOARDS_BOOTLEG31_H_ */
