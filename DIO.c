#include <string.h>
#include "DIO.h"

void DIO_ClockEnable(DIO_PORT PORT)
{
	
		switch(PORT)
		{
			case PortA: SET_PRT_CLOCK(PORTA_CLK);break; // Enable Clock PORT A
			case PortB: SET_PRT_CLOCK(PORTB_CLK);break;	// Enable Clock PORT B
			case PortC: SET_PRT_CLOCK(PORTC_CLK);break;	// Enable Clock PORT C
			case PortD: SET_PRT_CLOCK(PORTD_CLK);break;	// Enable Clock PORT D
			case PortE: SET_PRT_CLOCK(PORTE_CLK);break;	// Enable Clock PORT E
		}
	
}

void DIO_ClockDisable(DIO_PORT PORT)
{
	  switch(PORT)
		{
			case PortA: CLEAR_PRT_CLOCK(PORTA_CLK);break; 	// Disable Clock PORT A
			case PortB: CLEAR_PRT_CLOCK(PORTB_CLK);break;	// Disable Clock PORT B
			case PortC: CLEAR_PRT_CLOCK(PORTC_CLK);break;	// Disable Clock PORT C
			case PortD: CLEAR_PRT_CLOCK(PORTD_CLK);break;	// Disable Clock PORT D
			case PortE: CLEAR_PRT_CLOCK(PORTE_CLK);break;	// Disable Clock PORT E
		}
}
/* Alternative to GPIO */
/* Pin Mux Control*/
void DIO_SetGPIO_PIN(DIO_PORT PORT ,DIO_PIN PIN)
{
	switch(PORT)
		{
			case PortA: 
				SET_BIT_GGPIO_PORTA(PIN);	// Set 1 in 8 bit 
				CLEAR_BIT_GGPIO_PORTA(PIN);	// set 0 in bit 9 and 10
				break;
			case PortB: 
				SET_BIT_GGPIO_PORTB(PIN);	// Set 1 in 8 bit 
				CLEAR_BIT_GGPIO_PORTB(PIN);	// set 0 in bit 9 and 10
				break;
			case PortC:
				SET_BIT_GGPIO_PORTC(PIN);	// Set 1 in 8 bit 
				CLEAR_BIT_GGPIO_PORTC(PIN);	// set 0 in bit 9 and 10
				break;
			case PortD:
				SET_BIT_GGPIO_PORTD(PIN);	// Set 1 in 8 bit 
				CLEAR_BIT_GGPIO_PORTD(PIN);	// set 0 in bit 9 and 10
				break;
			case PortE:
				SET_BIT_GGPIO_PORTE(PIN);	// Set 1 in 8 bit 
				CLEAR_BIT_GGPIO_PORTE(PIN);	// set 0 in bit 9 and 10
				break;
		}

}

void DIO_PinMode(DIO_PORT PORT, DIO_PIN PIN, DIO_DIRECTION Direction)
{
	
	
	if(Direction == Output)
	{
		DIO_ClockEnable(PORT);
		DIO_SetGPIO_PIN(PORT , PIN);
		switch(PORT)
		{
			case PortA: SET_DATA_DIR_PORTA(PIN);break;
			case PortB: SET_DATA_DIR_PORTB(PIN);break;
			case PortC: SET_DATA_DIR_PORTC(PIN);break;
			case PortD: SET_DATA_DIR_PORTD(PIN);break;
			case PortE: SET_DATA_DIR_PORTE(PIN);break;
		}
	}
	else if (Direction == Input)
	{
		DIO_ClockEnable(PORT);
		DIO_SetGPIO_PIN(PORT , PIN);
		switch(PORT)
		{
			case PortA: CLEAR_DATA_DIR_PORTA(PIN);break;
			case PortB: CLEAR_DATA_DIR_PORTA(PIN);break;
			case PortC: CLEAR_DATA_DIR_PORTA(PIN);break;
			case PortD: CLEAR_DATA_DIR_PORTA(PIN);break;
			case PortE: CLEAR_DATA_DIR_PORTA(PIN);break;
		}
	}
	
}

void DIO_DigitalWrite(DIO_PORT PORT, DIO_PIN PIN, DIO_Value Value)
{
	if(Value == High)
	{
		switch(PORT)
		{
			case PortA: SET_PIN_VALUE_PORTA(PIN);break;
			case PortB: SET_PIN_VALUE_PORTB(PIN);break;
			case PortC: SET_PIN_VALUE_PORTC(PIN);break;
			case PortD: SET_PIN_VALUE_PORTD(PIN);break;
			case PortE: SET_PIN_VALUE_PORTE(PIN);break;
		}
	}
	else if(Value == Low)
	{
		switch(PORT)
		{
			case PortA: CLEAR_PIN_VALUE_PORTA(PIN);break;
			case PortB: CLEAR_PIN_VALUE_PORTB(PIN);break;
			case PortC: CLEAR_PIN_VALUE_PORTC(PIN);break;
			case PortD: CLEAR_PIN_VALUE_PORTD(PIN);break;
			case PortE: CLEAR_PIN_VALUE_PORTE(PIN);break;
		}
	}
}
void Delay_ms(uint32_t delay_ms)
{
	SystemCoreClockUpdate();
	uint32_t volatile count,i;
//	for(count=0; count<delay_ms; count++)
//	{
//		for( i=0; i<((SystemCoreClock/1000)/12); i++){}
//	}
	for(i=0; i<delay_ms; i++)
		for(count=0; count<922; count++);	//922 because 0 to 922 take 1ms to execute 
}

DIO_Value DIO_DigitalReadValue(DIO_PORT PORT, DIO_PIN PIN)
{
	DIO_Value	PinValue=Low;
	switch(PORT)
	{
		case PortA: PinValue = GET_PIN_VALUE_PORTA(PIN);break;
		case PortB: PinValue = GET_PIN_VALUE_PORTB(PIN);break;
		case PortC: PinValue = GET_PIN_VALUE_PORTC(PIN);break;
		case PortD: PinValue = GET_PIN_VALUE_PORTD(PIN);break;
		case PortE: PinValue = GET_PIN_VALUE_PORTE(PIN);break;
	}
	return(PinValue);
}
