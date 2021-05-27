 /**************************************************
* @file:     KEYPAD.h
* @revision: 1.0
* @date:     13-Jan-2021
* @brief:    Global definitions for Keypad module
* @Author:	 MohamedRaafat
***************************************************/

#include "AllHeaders.h"



/**************************************************
Data Structures and Typedefs
***************************************************/
typedef struct
{
	uint8_t key_pressed;
	uint8_t dbnce;
}keypad_str;

//Holds the state of key
//static keypad_str key_state_tbl[KEY_hash];

/**************************************************
Local function prototypes
***************************************************/
char search_col1_value(void);
void search_col2(void);
void search_col3(void);
void search_col4(void);
void update_key_status(key_enm key_event);


/**************************************************
* @function: init_keypad
* @brief:    Initialize the 4x4 matrix keypad GPIO's
* @param:    none
* @return:	 none
***************************************************/
void init_keypad(void)
{
	// Enable clock for PORTA, PORTC and PORTD
	SIM->SCGC5 |= (SIM_SCGC5_PORTA(1) | SIM_SCGC5_PORTC(1) |
								 SIM_SCGC5_PORTD(1));
	
	// Configure ROW keypad GPIO's as output
	GPIOC->PDDR |= (ROW1 | ROW2); 
	GPIOA->PDDR |= (ROW3 | ROW4);              

	// Configure COLUMN keypad GPIO's as input
	GPIOA->PDDR &= (~COL3 & ~COL4);    
	GPIOA->PDDR &= ~COL1;
	GPIOD->PDDR &= ~COL2;
	
	// Confgure all Keypad pins as GPIO's. Enable pull-up on 
	// column input pins
	PORTA_PCR1 = (PORT_PCR_MUX(1) | PORT_PCR_PE(0));
	PORTA_PCR2 = (PORT_PCR_MUX(1) | PORT_PCR_PE(0)); 
	PORTA_PCR12= (PORT_PCR_MUX(1) | PORT_PCR_PE(0)); 
	PORTD_PCR4 = (PORT_PCR_MUX(1) | PORT_PCR_PE(0)); 
	
	PORTA_PCR4 = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); 
	PORTA_PCR5 = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); 
	PORTC_PCR8 = (PORT_PCR_MUX(1) | PORT_PCR_PE(1)); 
	PORTC_PCR9 = (PORT_PCR_MUX(1) | PORT_PCR_PE(1));
}

/**************************************************
* @function: keypad_scan
* @brief:    This function checks if any key is pressed
*            on 4x4 matrix keypad
* @param:    none
* @return:	 Character
***************************************************/

char KeyPadScan(void)
{
	/*************************************************
	************** Search In Column (1) **************
	*************************************************/
	
	/*****************************************
	ROW1:LOW  --> PTC9,	ROW2:HIGH --> PTC8
	ROW3:HIGH --> PTA5,	ROW4:HIGH --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, Low);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 12)==0)
	{
		return '1';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:LOW  --> PTC8
	ROW3:HIGH --> PTA5,	ROW4:HIGH --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, Low);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 12)==0)
	{
		return '4';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:HIGH  --> PTC8
	ROW3:LOW  --> PTA5,	ROW4:HIGH  --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, Low);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 12)==0)
	{
		return '7';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:HIGH  --> PTC8
	ROW3:HIGH  --> PTA5,	ROW4:Low   --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, Low);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 12)==0)
	{
		return '*';
	}
	
	/*************************************************
	************** Search In Column (2) **************
	*************************************************/
	
	/*****************************************
	ROW1:LOW  --> PTC9,	ROW2:HIGH --> PTC8
	ROW3:HIGH --> PTA5,	ROW4:HIGH --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, Low);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortD, 4)==0)
	{
		return '2';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:LOW  --> PTC8
	ROW3:HIGH --> PTA5,	ROW4:HIGH --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, Low);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortD, 4)==0)
	{
		return '5';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:HIGH  --> PTC8
	ROW3:LOW  --> PTA5,	ROW4:HIGH  --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, Low);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortD, 4)==0)
	{
		return '8';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:HIGH  --> PTC8
	ROW3:HIGH  --> PTA5,	ROW4:Low   --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, Low);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortD, 4)==0)
	{
		return '0';
	}
	
	/*************************************************
	************** Search In Column (3) **************
	*************************************************/
	
	/*****************************************
	ROW1:LOW  --> PTC9,	ROW2:HIGH --> PTC8
	ROW3:HIGH --> PTA5,	ROW4:HIGH --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, Low);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 2)==0)
	{
		return '3';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:LOW  --> PTC8
	ROW3:HIGH --> PTA5,	ROW4:HIGH --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, Low);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 2)==0)
	{
		return '6';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:HIGH  --> PTC8
	ROW3:LOW  --> PTA5,	ROW4:HIGH  --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, Low);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 2)==0)
	{
		return '9';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:HIGH  --> PTC8
	ROW3:HIGH  --> PTA5,	ROW4:Low   --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, Low);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 2)==0)
	{
		return '#';
	}
	
	/*************************************************
	************** Search In Column (4) **************
	*************************************************/
	
	/*****************************************
	ROW1:LOW  --> PTC9,	ROW2:HIGH --> PTC8
	ROW3:HIGH --> PTA5,	ROW4:HIGH --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, Low);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 1)==0)
	{
		return 'A';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:LOW  --> PTC8
	ROW3:HIGH --> PTA5,	ROW4:HIGH --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, Low);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 1)==0)
	{
		return 'B';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:HIGH  --> PTC8
	ROW3:LOW  --> PTA5,	ROW4:HIGH  --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, Low);
	DIO_DigitalWrite(PortA, 4, High);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 1)==0)
	{
		return 'C';
	}
	
	/*****************************************
	ROW1:HIGH --> PTC9,	ROW2:HIGH  --> PTC8
	ROW3:HIGH  --> PTA5,	ROW4:Low   --> PTA4
	*****************************************/
	DIO_DigitalWrite(PortC, 9, High);
	DIO_DigitalWrite(PortC, 8, High);
	DIO_DigitalWrite(PortA, 5, High);
	DIO_DigitalWrite(PortA, 4, Low);
	delay_ms(1);
	
	if(DIO_DigitalReadValue(PortA, 1)==0)
	{
		return 'D';
	}
	
	return 'N';
	
}
