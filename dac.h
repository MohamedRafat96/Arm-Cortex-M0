 /**************************************************
* @file:     dac.h
* @revision: 1.0
* @date:     13-Jan-2021
* @brief:    Global definitions for DAC module
* @Author:	 MohamedRaafat
***************************************************/

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "externs.h"

void dac_Init(void);
bool dac_Output(uint16_t value);

#endif /* _DAC_H_ */
