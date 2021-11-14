/*
 * processing.h
 *
 *  Created on: Jul 6, 2021
 *      Author: johan
 */

#ifndef INC_PROCESSING_H_
#define INC_PROCESSING_H_

#include "stdint.h"
#include "stm32f0xx_hal.h"

extern 	CRC_HandleTypeDef hcrc;

/* Deklaration der Variablen ---------------------------------------------------------*/

const 	uint16_t LUT[151];
		uint32_t tempCRC;


/* Deklaration der Funktionen ---------------------------------------------------------*/

uint8_t 	GetTempCfromLUT(const uint16_t *LUT, uint16_t ntcResistance);
uint16_t 	generateChecksum(uint8_t *tempC, uint8_t checksumNumber);
uint32_t 	generateCRC32(uint8_t tempC, uint8_t adcChannel);


#endif /* INC_PROCESSING_H_ */
