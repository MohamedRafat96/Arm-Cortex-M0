 /**************************************************
* @file:     LCD.h
* @revision: 1.0
* @date:     13-Jan-2021
* @brief:    Global definitions for LCD module
* @Author:	 MohamedRaafat
***************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "externs.h"


/**************************************************
LCD Constants For Configrations 4-bit Mode
**************************************************/
#define LCD_D7	((uint32_t)1 << 7)	// PTC7 Data Bus 
#define LCD_D6	((uint32_t)1 << 0)	// PTC0 Data Bus 
#define LCD_D5	((uint32_t)1 << 3)	// PTC3 Data Bus
#define LCD_D4	((uint32_t)1 << 4)	// PTC4 Data Bus
#define LCD_EN	((uint32_t)1 << 5)	// PTC5 Enable Internal Latch In LCD
#define LCD_RW	((uint32_t)1 << 6)	// PTC6 Read/Write Register 
#define LCD_RS	((uint32_t)1 << 10)	// PTC10 Select Data Or Command To LCD 


/**************************************************
Data Structures and Typedefs
***************************************************/
typedef enum
{
	LCD_LINE1,
	LCD_LINE2
}lcd_line;

typedef enum{
	SCROLL,
	UNSCROLL
}lcd_scrolling;

/**************************************************
Global function prototypes
***************************************************/
void LCD_Initialize(void);				// Initialization LCD 
void LCD_Command(uint8_t);				// Send Command To LCD
void write_nibble(uint8_t);				// set/clear the data lines based on input data
uint8_t lcd_string_write(char **str);
void lcd_SendCharacter(unsigned char character);
void lcd_data_write_string(char *data, lcd_line line,unsigned char column, lcd_scrolling scroll_type);
void lcd_data_write_Integer(double number, lcd_line line,unsigned char column, lcd_scrolling scroll_type);
void delay_ms(unsigned int length_ms);
void lcd_Ready(void);

#endif /* LCD_H_ */
