 /**************************************************
* @file:     LCD.c
* @revision: 1.0
* @date:     13-Jan-2021
* @brief:    Global Functions for LCD module
* @Author:	 MohamedRaafat
***************************************************/

#include "externs.h"

/**************************************************
File Global (Static) Variables
***************************************************/
static uint8_t scroll_data_stored;
static char lcd_scroll_msg[50]; // msg to be scrolled


/**************************************************
* @function: delay_ms
* @param:    length_ms: Delay Length
* @return:	 none
* @brief:    local function to generate delay Use Timer.
**************************************************/
void delay_ms(unsigned int length_ms)
{
    SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;  // Make sure clock is enabled
    LPTMR0_CSR = 0;                     // Reset LPTMR settings         
    LPTMR0_CMR = length_ms;             // Set compare value (in ms)

    // Use 1kHz LPO with no prescaler
    LPTMR0_PSR = LPTMR_PSR_PCS(1) | LPTMR_PSR_PBYP_MASK;
    
    // Start the timer and wait for it to reach the compare value
    LPTMR0_CSR = LPTMR_CSR_TEN_MASK;
    while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK))
        ;
    
    LPTMR0_CSR = 0;                     // Turn off timer
}

/**************************************************
* @function: LCD_Initialize
* @param:    none
* @return:	 none
* @brief:    local function to Initialization LCD 
*		 and make Configrations for Pins
**************************************************/
void LCD_Initialize(void)
{
	
	// PTC7 ->	D7
	// PTC0 ->	D6
	// PTC3 -> 	D5
	// PTC4 -> 	D4
	// PTC5 -> 	EN
	// PTC6 -> 	RW
	// PTC10 -> RS
	
	// Enable Clock to PORTC
	SIM->SCGC5 = SIM_SCGC5_PORTC(1);
	
	// Enable all LCD pins as GPIO
	PORTC_PCR7  |= PORT_PCR_MUX(1);
	PORTC_PCR0  |= PORT_PCR_MUX(1);
	PORTC_PCR3  |= PORT_PCR_MUX(1);
	PORTC_PCR4  |= PORT_PCR_MUX(1);
	PORTC_PCR5  |= PORT_PCR_MUX(1);
	PORTC_PCR6  |= PORT_PCR_MUX(1);
	PORTC_PCR10 |= PORT_PCR_MUX(1);
	
	// Configure all pins as output
	GPIOC->PDDR |= (LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4 |
			    LCD_EN | LCD_RW | LCD_RS);
	
	LCD_Command(0x02);  // Move the cursor to original position
	LCD_Command(0x28);  // Enable 4-bit, 2 line, 5x7 dots mode for chars 
	LCD_Command(0x0E);  // Display ON, Cursor on
	LCD_Command(0x01);  // Clear Display 		
}

/**************************************************
* @function: LCD_Command
* @param:    cmd : Command to the LCD
* @return:	 none
* @brief:    local function to Send Command to LCD 
**************************************************/
void LCD_Command(uint8_t cmd)
{
	//lcd_Ready();
	GPIOC->PDOR  &= ~(LCD_RS);		// Select Command Register {RS=LOW}
	GPIOC->PDOR  &= ~(LCD_RW);		// Write to LCD {RW=LOW}
	
	// 11110000 --> DEC = 240 --> HEX = 0x0F
	write_nibble(cmd & 0xF0);    		// Write Upper nibble
	
	// Generate a High-to-low pulse on EN pin to latch the data
	GPIOC->PDOR |= LCD_EN;   		// EN=HIGH
	delay_ms(1);           			// Wait for ~1msec
	GPIOC->PDOR &= ~LCD_EN; 			// EN=LOW
	delay_ms(1);           			// Wait for ~1msec
	
	write_nibble((cmd << 4) & 0xF0); 	// Write Lower nibble

	// Generate a High-to-low pulse on EN pin to latch the data
	GPIOC->PDOR |= LCD_EN;  			// EN=HIGH
	delay_ms(1);           			// Wait for ~1msec
	GPIOC->PDOR &= ~LCD_EN;  		// EN=LOW
	delay_ms(1);           			// Wait for ~1msec
}

/**************************************************
* @function: write_nibble
* @brief:    This function set/clear the data lines based
*            on input data
* @param:    nibble: Lower/Upper 4 bits of byte
* @return:	 none
**************************************************/
/*
	if(data & 1){GPIOC->PDOR |= LCD_D4;} else{GPIOC->PDOR &= ~LCD_D4;}
	if(data & 2){GPIOC->PDOR |= LCD_D5;} else{GPIOC->PDOR &= ~LCD_D5;}
	if(data & 4){GPIOC->PDOR |= LCD_D6;} else{GPIOC->PDOR &= ~LCD_D6;}
	if(data & 8){GPIOC->PDOR |= LCD_D7;} else{GPIOC->PDOR &= ~LCD_D7;}
*/
void write_nibble(uint8_t nibble)
{
	
	uint32_t gpio_temp;
	
	// Get GPIO-C Data Register
	gpio_temp = GPIOC->PDOR;
	
	// Update the LCD data line DB7
	if (nibble & 0x80){ gpio_temp |= LCD_D7; }
	else{ gpio_temp &= ~LCD_D7; }
		
	// Update the LCD data line DB6
	if (nibble & 0x40){ gpio_temp |= LCD_D6; }
	else{ gpio_temp &= ~LCD_D6; }
		
	// Update the LCD data line DB5
	if (nibble & 0x20){ gpio_temp |= LCD_D5; }
	else{ gpio_temp &= ~LCD_D5; }
		
	// Update the LCD data line DB4
	if (nibble & 0x10){ gpio_temp |= LCD_D4; }
	else{ gpio_temp &= ~LCD_D4; }
		
	// Write updated data to GPIO-C Port
	GPIOC->PDOR = gpio_temp;
}

void lcd_SendCharacter(unsigned char character)
{
	GPIOC->PDOR |=  LCD_RS; 	// Select data register    (RS=HIGH)
	GPIOC->PDOR &= ~LCD_RW; 	// Select write operation  (RW=LOW)

	write_nibble(character & 0xF0);	// Write Upper nibble
		
	// Generate a High-to-low pulse on EN pin to latch the data
	GPIOC->PDOR |= LCD_EN;   	// EN=HIGH
	delay_ms(1);           		// Wait for ~1msec
	GPIOC->PDOR &= ~LCD_EN;  	// EN=LOW
	delay_ms(1);           		// Wait for ~1msec

	write_nibble((character << 4) & 0xF0); // Write Lower nibble
	
      // Generate a High-to-low pulse on EN pin to latch the data
	GPIOC->PDOR |= LCD_EN;   	// EN=HIGH
	delay_ms(1);           		// Wait for ~1msec
	GPIOC->PDOR &= ~LCD_EN;  	// EN=LOW
	delay_ms(1);           		// Wait for ~1msec
}

/**************************************************
* @function: lcd_string_write
* @brief:    Write character string to LCD
* @param:    
*		 **str: Pointer to pointer to data
* @return:	 
*            cnt: Number of characters written
**************************************************/


uint8_t lcd_string_write(char **str)
{
	uint8_t cnt = 0; // Counting string length
	
	// Write until entire string (msg) is finished 
	// (max 16 char per line)
	while (**str && cnt < 16)
	{
		if (!scroll_data_stored)
		{
			// Store the message be scrolled (character by character)
			lcd_scroll_msg[cnt] = **str;
		}
		
		GPIOC->PDOR |=  LCD_RS; 	// Select data register    (RS=HIGH)
		GPIOC->PDOR &= ~LCD_RW; 	// Select write operation  (RW=LOW)

		write_nibble(**str & 0xF0);	// Write Upper nibble
		
		// Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_EN;   	// EN=HIGH
		delay_ms(1);           		// Wait for ~1msec
		GPIOC->PDOR &= ~LCD_EN;  	// EN=LOW
		delay_ms(1);           		// Wait for ~1msec

		write_nibble((**str << 4) & 0xF0); // Write Lower nibble
	
            // Generate a High-to-low pulse on EN pin to latch the data
		GPIOC->PDOR |= LCD_EN;   	// EN=HIGH
	      delay_ms(1);           		// Wait for ~1msec
	      GPIOC->PDOR &= ~LCD_EN;  	// EN=LOW
	      delay_ms(1);           		// Wait for ~1msec
			
		(*str)++; 				// Go to next character
		cnt++;     				// Increment string length check count
	}
	
	return cnt;
}
/**************************************************
* @function: lcd_data_write_string
* @param:    
*		 *data: Pointer to data
*            line: 16x2 LCD line (Line 1 or 2)
*            scroll_type: Scroll/Unscroll type
* @return:	 none
* @brief:    Write data to LCD
***************************************************/
void lcd_data_write_string(char *data, lcd_line line,unsigned char column, lcd_scrolling scroll_type)
{
	//lcd_Ready();
	uint8_t char_written; // actual number of characters
	                      // written on LCD
	char *temp = " ";     // Space to be filled for
	                      // unused blocks on Line
	char *pscroll_msg;    // Pointing to scrolling msg
	uint8_t i;
	char tmp;
	static uint8_t scroll_chars;
	
	// Enter here if data to be displayed without scrolling OR
	// Data to be scrolled on LCD needs to be stored for first time
	if (line == LCD_LINE1)
	{
		if (line == 0 && column<16)
		LCD_Command((column & 0x0F)|0x80);
	}
	else
	{
		if (line == 1 && column<16)
		LCD_Command((column & 0x0F)|0xC0);
	}
		
	if ((scroll_type == UNSCROLL) || (!scroll_data_stored))
	{		
		// Write data string to LCD (in returns gets how many
		// characters are written)
		char_written = lcd_string_write(&data);
		
		if (scroll_type == SCROLL)
		{
			scroll_chars = char_written;
			
			// Fill remaining scroll message
			while (*data && scroll_chars < 49)
			{
				lcd_scroll_msg[scroll_chars] = *data++;
				scroll_chars++;
			}
			
			// End the scroll message
			lcd_scroll_msg[scroll_chars] = '\0';
			
			// Indicate data to be scrolled is stored
			scroll_data_stored = 1;
		}
		else
		{		
			// Fill remaining blocks in the line with space
			// (unscroll message)
			while (char_written < 16)
			{
				lcd_string_write(&temp);
				char_written++;
			}
		}
	}
	else // If message is to be scrolled
	{
		// Get the first character of message (to be stored
		// at the end of message to form a circular loop)
		tmp = lcd_scroll_msg[0];
		
		// Shift the message by 1 character to left
		for (i=0; i<scroll_chars; i++)
		{
			lcd_scroll_msg[i] = lcd_scroll_msg[i+1];
		}
		
		// Store first character at the end (loopback)
		lcd_scroll_msg[scroll_chars-1] = tmp;
		
		// Display shifted message (The message is shifted
		// to left by 1 character every 300msec to get a 
		// feeling that it is actually scrolling from right
		// to left)
		pscroll_msg = lcd_scroll_msg;
		(void)lcd_string_write(&pscroll_msg);
	}
}

/**************************************************
* @function: lcd_data_write_Integer
* @param:    number : pass integer value to displayed in LCD
*		 line: 16x2 LCD line (Line 1 or 2)
*            scroll_type: Scroll/Unscroll type
* @return:	 none
* @brief:    Write data to LCD
***************************************************/
void lcd_data_write_Integer(double number, lcd_line line,unsigned char column, lcd_scrolling scroll_type)
{
	//lcd_Ready();
	char number_str[10];  			// Store Numbers
	sprintf(number_str, "%2.2f", number);  // Store numbers in array of characters 
	lcd_data_write_string(number_str , line ,column, scroll_type); // Display Numbers in LCD 
}
void lcd_Ready(void)
{
	uint32_t status;
	
	PTC->PDDR = 0;
	GPIOC->PDOR &= ~LCD_RS; 	// Select data register    (RS=LOW)
	GPIOC->PDOR |=  LCD_RW; 	// Select write operation  (RW=HIGH)
	
	do
	{
		PTC->PSOR |= LCD_EN;   	// EN=HIGH
		delay_ms(0);
		status = PTC->PDIR;
		PTC->PCOR |= LCD_EN;
		delay_ms(0);
		
	}while(status & 0x80);
	GPIOC->PDOR &=  ~LCD_RW; 	// Select write operation  (RW=LOW)
	PTC->PDDR = 0xFF;
}
