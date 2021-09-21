 /**************************************************
* @file:     adc.h
* @revision: 1.0
* @date:     18-Jan-2021
* @brief:    Global definitions for ADC module
* @Author:	 MohamedRaafat
***************************************************/

#ifndef SOURCES_ADC_H_
#define SOURCES_ADC_H_

#include "externs.h"

#define ADC_0	0	//  PTE20
#define ADC_1	4	//  PTE21
#define ADC_2	3	//  PTE22
#define ADC_3	7	//  PTE23
#define ADC_4	8	//  PTB0
#define ADC_5	9	//  PTB1
#define ADC_6	12	//  PTB2
#define ADC_7	13	//  PTB3
#define ADC_8	14	//  PTC0
#define ADC_9	15	//  PTC1
#define ADC_10 	11	//  PTC2
#define ADC_11 	5	//  PTD1   

#define _8BIT  0
#define _10BIT 1
#define _12BIT 2
#define _16BIT 3

void adc_init(uint8_t res);
uint16_t adc_read(uint16_t ch);

#endif /* SOURCES_ADC_H_ */
