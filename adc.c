 /**************************************************
* @file:     adc.c
* @revision: 1.0
* @date:     18-Jan-2021
* @brief:    Global definitions for ADC module
* @Author:	 MohamedRaafat
***************************************************/

#include "adc.h"

/**************************************************
* @function: adc_init
* @brief:    Initialize the adc module
* @param:    none
* @return:	 none
***************************************************/
void adc_init(uint8_t res)
{
	// Enable clocks
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;	// ADC 0 clock

	// Configure ADC
	ADC0_CFG1 = 0; // Reset register

	ADC0_CFG1 |= (ADC_CFG1_MODE( res )  |  	// 16 bits mode
				  ADC_CFG1_ADICLK(0)|	// Input Bus Clock (20-25 MHz out of reset (FEI mode))
				  ADC_CFG1_ADIV(1)) ;	// Clock divide by 2 (10-12.5 MHz)
	
	ADC0_SC3 = 0; // Reset SC3

	ADC0_SC1A |= ADC_SC1_ADCH(31); // Disable module
}

/**************************************************
* @function: adc_read
* @brief:    read the adc module
* @param:    ch number of channel adc 
* @return:	 ADC0_RA the value on the channel
***************************************************/
uint16_t adc_read(uint16_t ch)
{
	ADC0_SC1A = ch & ADC_SC1_ADCH_MASK; 	//Write to SC1A to start conversion
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK); 	// Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));  // Run until the conversion is complete
	return ADC0_RA;
}
