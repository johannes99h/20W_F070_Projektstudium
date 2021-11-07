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

#include "processing.h"
#include "transmission.h"

extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_adc;

#define channelAdc 	9
#define buffLength	45

/*
 * 		Deklarationen
 */

const 	uint8_t 	adcSamples;
		uint16_t 	adcBuffer[buffLength];
		uint16_t 	adcVal[buffLength];
		uint16_t 	adcBufferMeanValue[channelAdc];
		uint16_t 	adcVoltage[channelAdc];
		uint16_t 	ntcResistance[channelAdc];
		uint8_t		tempC[channelAdc];
		uint32_t 	CRCtempC[channelAdc];

/*
 * 		Funktionsdeklarationen
 */

void		scheduler();
uint16_t 	*ClearADCBuffer(uint16_t *adcBuffer);
uint16_t 	*GetADCMeanValue(uint16_t *adcVal, uint8_t adcSamples);
uint16_t 	*GetADCResistance(uint16_t *adcBufferMeanValue);

#endif /* INC_ADC_H_ */
