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


/* Deklaration der Variablen ---------------------------------------------------------*/

#define LUT_table_size 37

const 	uint16_t LUT[151];
		uint32_t tempCRC;


/* Deklaration der Funktionen ---------------------------------------------------------*/

uint8_t GetTempCfromLUT(const uint16_t *LUT, uint16_t ntcResistance, int size);


#endif /* INC_PROCESSING_H_ */
