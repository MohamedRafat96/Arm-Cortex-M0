 /**************************************************
* @file:     dac.c
* @revision: 1.0
* @date:     13-Jan-2021
* @brief:    Global definitions for Keypad module
* @Author:	 MohamedRaafat
***************************************************/

#include "externs.h"

/**************************************************
* @function: dac_Init
* @brief:    Initialize the dac module
* @param:    none
* @return:	 none
***************************************************/
void dac_Init(void)
{
	// DAC0 clock enabled
	SIM_SCGC6 |= SIM_SCGC6_DAC0_MASK;

	// Clear status register
	DAC0_SR = 0x00;

	// The DAC system is enabled
	DAC0_C0 = DAC_C0_DACEN_MASK ;
}

/**************************************************
* @function: dac_Output
* @brief:    Initialize the dac module
* @param:    value input value
		 msb Least Significant Bit
		 lsb most Significant Bit
* @return:	 true if value 2^12 -1
		 false
***************************************************/
bool dac_Output(uint16_t value)
{
	uint8_t msb = 0;
	uint8_t lsb = 0;

    if(value < 4095)
    {
    	msb = (uint8_t)(value >> 8);
    	lsb = (uint8_t)(value);

    	DAC0_DAT0L = lsb;
    	DAC0_DAT0H = msb;
    	return true;
    }
    else return false;
}
