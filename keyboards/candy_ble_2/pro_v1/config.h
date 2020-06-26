#ifndef MASTER_CONFIG_H_
#define MASTER_CONFIG_H_

#include "custom_board.h"

#define THIS_DEVICE_ROWS 5
#define THIS_DEVICE_COLS 4

#define MATRIX_ROW_PINS { PIN18, PIN13, PIN14, PIN16, PIN17 }
#define MATRIX_COL_PINS { PIN8, PIN9, PIN10, PIN11, }

#ifdef ENCODER_ENABLE
	#define ENCODERS_PAD_A { PIN7 }
	#define ENCODERS_PAD_B { PIN22 }
#endif

#define TAP_CODE_DELAY 50
#define IS_LEFT_HAND  true
#define ENABLE_STARTUP_ADV_NOLIST

#endif /* MASTER_CONFIG_H_ */
