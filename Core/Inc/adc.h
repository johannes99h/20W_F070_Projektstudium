/*
 * adc.h
 *
 *  Created on: Jul 6, 2021
 *      Author: johan
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stdint.h"
#include "stm32f0xx_hal.h"

extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_adc;

#define adcChannel 9
#define adcChannelSelect
#define buff_length 27

/*
 * 		Deklarationen
 */

uint16_t adcBuffer[buff_length];
uint16_t adcVal[buff_length];
uint16_t adcBufferMeanValue[adcChannel];
uint16_t adcVoltage[adcChannel];
uint16_t ntcResistance[adcChannel];
uint16_t ntcResistance25[adcChannel];
uint32_t ntcRTtoR25[adcChannel];
uint16_t tempZero;

/*
 * 		Funktionsdeklarationen
 */

uint16_t * ClearADCBuffer(uint16_t *adcBuffer);
uint32_t *GetADCResistance(uint16_t *adcBufferMeanValue);

#endif /* INC_ADC_H_ */
