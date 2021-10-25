/*
 * transmission.h
 *
 *  Created on: Jul 6, 2021
 *      Author: johan
 */

#ifndef INC_TRANSMISSION_H_
#define INC_TRANSMISSION_H_

#include "stdio.h"
#include "stdint.h"
#include "stm32f0xx_hal.h"


/* externe Definitionen ---------------------------------------------------------*/

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_tx;


/* Deklaration der Variablen ---------------------------------------------------------*/

// alt
char bufferTx[25];				// char nicht unbed. nötig, auch mit uint8_t-Array lösbar -> stdio.h nicht notwendig
uint16_t bufferTxSize;

// neu
uint8_t divider[1];
uint32_t tempCRC;
uint8_t adcChannels;

/* Deklaration der Funktionen ---------------------------------------------------------*/

void 	TxUART(uint8_t adcChannels, uint8_t *tempC);
void 	singleTempTxUART(uint8_t ntcNumber, uint8_t *tempC);
void 	TempTxUART(uint16_t bufferTxSize, uint8_t *tempC, uint8_t adcChannels);
void 	ntcNumberTxUART(uint8_t ntcNumber);
int 	blankTxUART();
int	 	CRCTxUART(uint32_t tempCRC);

#endif /* INC_TRANSMISSION_H_ */
