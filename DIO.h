/*
 * DIO.h
 *
 * Created: 12/14/2020 10:30:19 AM
 *  Author: MohamedRaafat 
 */ 
 
#include "MKL25Z4.h"

/*	System Clock Gating Control Register 5 (SIM_SCGC5)
		
		BIT  9   -------> PORT A
		BIT 10   -------> PORT B
		BIT 11   -------> PORT C
		BIT 12   -------> PORT D
		BIT 13   -------> PORT E
		
*/
#define PORTA_CLK		(1U <<  9)
#define PORTB_CLK		(1U << 10)
#define PORTC_CLK		(1U << 11)
#define PORTD_CLK		(1U << 12)
#define PORTE_CLK		(1U << 13)

#define SET_PRT_CLOCK(PORTx_CLK)					(SIM->SCGC5) |=  (PORTx_CLK)
#define CLEAR_PRT_CLOCK(PORTx_CLK)					(SIM->SCGC5) &= ~(PORTx_CLK)

#define SET_BIT_GGPIO_PORTA(PIN_ID)					(PORTA->PCR[PIN_ID]) |=  (1U<<8)
#define CLEAR_BIT_GGPIO_PORTA(PIN_ID)				(PORTA->PCR[PIN_ID]) &= ~(3U<<9)
#define SET_BIT_GGPIO_PORTB(PIN_ID)					(PORTB->PCR[PIN_ID]) |=  (1U<<8)
#define CLEAR_BIT_GGPIO_PORTB(PIN_ID)				(PORTB->PCR[PIN_ID]) &= ~(3U<<9)
#define SET_BIT_GGPIO_PORTC(PIN_ID)					(PORTC->PCR[PIN_ID]) |=  (1U<<8)
#define CLEAR_BIT_GGPIO_PORTC(PIN_ID)				(PORTC->PCR[PIN_ID]) &= ~(3U<<9)
#define SET_BIT_GGPIO_PORTD(PIN_ID)					(PORTD->PCR[PIN_ID]) |=  (1U<<8)
#define CLEAR_BIT_GGPIO_PORTD(PIN_ID)				(PORTD->PCR[PIN_ID]) &= ~(3U<<9)
#define SET_BIT_GGPIO_PORTE(PIN_ID)					(PORTE->PCR[PIN_ID]) |=  (1U<<8)
#define CLEAR_BIT_GGPIO_PORTE(PIN_ID)				(PORTE->PCR[PIN_ID]) &= ~(3U<<9)

#define SET_DATA_DIR_PORTA(PIN_ID)					(PTA->PDDR) |= ((1U<<(PIN_ID)))
#define SET_DATA_DIR_PORTB(PIN_ID)					(PTB->PDDR) |= ((1U<<(PIN_ID)))
#define SET_DATA_DIR_PORTC(PIN_ID)					(PTC->PDDR) |= ((1U<<(PIN_ID)))
#define SET_DATA_DIR_PORTD(PIN_ID)					(PTD->PDDR) |= ((1U<<(PIN_ID)))
#define SET_DATA_DIR_PORTE(PIN_ID)					(PTE->PDDR) |= ((1U<<(PIN_ID)))

#define CLEAR_DATA_DIR_PORTA(PIN_ID)				(PTA->PDDR) &= ~((1U<<(PIN_ID)))
#define CLEAR_DATA_DIR_PORTB(PIN_ID)				(PTB->PDDR) &= ~((1U<<(PIN_ID)))
#define CLEAR_DATA_DIR_PORTC(PIN_ID)				(PTC->PDDR) &= ~((1U<<(PIN_ID)))
#define CLEAR_DATA_DIR_PORTD(PIN_ID)				(PTD->PDDR) &= ~((1U<<(PIN_ID)))
#define CLEAR_DATA_DIR_PORTE(PIN_ID)				(PTE->PDDR) &= ~((1U<<(PIN_ID)))

#define SET_PIN_VALUE_PORTA(PIN_ID)					(PTA->PDOR) |= (1U<<(PIN_ID))
#define SET_PIN_VALUE_PORTB(PIN_ID)					(PTB->PDOR) |= (1U<<(PIN_ID))
#define SET_PIN_VALUE_PORTC(PIN_ID)					(PTC->PDOR) |= (1U<<(PIN_ID))
#define SET_PIN_VALUE_PORTD(PIN_ID)					(PTD->PDOR) |= (1U<<(PIN_ID))
#define SET_PIN_VALUE_PORTE(PIN_ID)					(PTE->PDOR) |= (1U<<(PIN_ID))

#define CLEAR_PIN_VALUE_PORTA(PIN_ID)				(PTA->PDOR) &= ~(1U<<(PIN_ID))
#define CLEAR_PIN_VALUE_PORTB(PIN_ID)				(PTB->PDOR) &= ~(1U<<(PIN_ID))
#define CLEAR_PIN_VALUE_PORTC(PIN_ID)				(PTC->PDOR) &= ~(1U<<(PIN_ID))
#define CLEAR_PIN_VALUE_PORTD(PIN_ID)				(PTD->PDOR) &= ~(1U<<(PIN_ID))
#define CLEAR_PIN_VALUE_PORTE(PIN_ID)				(PTE->PDOR) &= ~(1U<<(PIN_ID))


/************************* Pull Down Resistor ********************************************************/
/*
IN Pull Down Resistor Circit
When Press In Push Button Will give High Voltage
*/
#define GET_PIN_VALUE_PORTA(PIN_ID)					( ((PTA->PDIR) >> (PIN_ID)) & 0x01 )
#define GET_PIN_VALUE_PORTB(PIN_ID)					( ((PTB->PDIR) >> (PIN_ID)) & 0x01 )
#define GET_PIN_VALUE_PORTC(PIN_ID)					( ((PTC->PDIR) >> (PIN_ID)) & 0x01 )
#define GET_PIN_VALUE_PORTD(PIN_ID)					( ((PTD->PDIR) >> (PIN_ID)) & 0x01 )
#define GET_PIN_VALUE_PORTE(PIN_ID)					( ((PTE->PDIR) >> (PIN_ID)) & 0x01 )
/*****************************************************************************************************/

typedef enum{Input, Output} DIO_DIRECTION;										
typedef enum{PortA, PortB, PortC, PortD, PortE} DIO_PORT;						
typedef enum{Low, High} DIO_Value;
typedef enum{PIN0,  PIN1,  PIN2,  PIN3,  PIN4, PIN5, 
		 PIN6,  PIN7,  PIN8,  PIN9,  PIN10,
		 PIN11, PIN12, PIN13, PIN14, PIN15,
		 PIN16, PIN17, PIN18, PIN19, PIN20,
		 PIN21, PIN22, PIN23, PIN24, PIN25,
		 PIN26, PIN27, PIN28, PIN29, PIN30,PIN31} DIO_PIN;


void DIO_ClockEnable(DIO_PORT PORT); 				                    	// Function To Enable CLK For PORTS
void DIO_ClockDisable(DIO_PORT PORT); 				                    	// Function To Disable CLK For PORTS
void DIO_SetGPIO_PIN(DIO_PORT PORT ,DIO_PIN PIN);	              	        	// Alternative PINS to GPIO
		 
void DIO_PinMode(DIO_PORT PORT, DIO_PIN PIN, DIO_DIRECTION Direction);   		// Configures individual port pins for input or output.
void DIO_DigitalWrite(DIO_PORT PORT, DIO_PIN PIN, DIO_Value Value); 		  	// Set logical Level 0 to GUN and Logical Level 1 to 3.3v
		 
DIO_Value DIO_DigitalReadValue(DIO_PORT PORT, DIO_PIN PIN);					// Get Value of PIN

void Delay_ms(uint32_t delay_ms);
