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

typedef struct {
	int16_t LUT_temp_C;
	uint16_t LUT_ntcRTtoR25;
} LUT_temp;

uint32_t tempCRC;

static const LUT_temp table[LUT_table_size];
//static const uint16_t table[LUT_table_size];
static const uint16_t LUT[2][37];

/* Deklaration der Funktionen ---------------------------------------------------------*/

uint8_t GetTempCfromLUT(const LUT_temp *table, uint16_t LUT_ntcRTtoR25, int size);

#endif /* INC_PROCESSING_H_ */
