 /**************************************************
* @file:     KEYPAD.h
* @revision: 1.0
* @date:     13-Jan-2021
* @brief:    Global definitions for Keypad module
* @Author:	 MohamedRaafat
***************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "AllHeaders.h"
/**************************************************
Constants
***************************************************/
// Keypad IO Pins
#define ROW1   ((uint32_t)1 << 9)  		// PTC9
#define ROW2   ((uint32_t)1 << 8)  		// PTC8
#define ROW3   ((uint32_t)1 << 5)  		// PTA5
#define ROW4   ((uint32_t)1 << 4)  		// PTA4

#define COL4   ((uint32_t)1 << 1)  		// PTA1
#define COL3   ((uint32_t)1 << 2)  		// PTA2
#define COL2   ((uint32_t)1 << 4)  		// PTD4
#define COL1   ((uint32_t)1 << 12)  	// PTA12


typedef enum
{
	KEY_0,
	KEY_1 = '1',
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_Star,
	KEY_hash,
}key_enm;

void init_keypad(void);
char KeyPadScan(void);

#endif /* KEYPAD_H_ */
