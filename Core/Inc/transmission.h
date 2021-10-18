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

#define adcChannel 9

/* Deklaration der Variablen ---------------------------------------------------------*/

// alt
char bufferTx[50];				// char nicht unbed. nötig, auch mit uint8_t-Array lösbar -> stdio.h nicht notwendig
uint16_t bufferTxSize;

// neu
uint8_t divider[1];
uint8_t ntcNumber[9];																	// äquivalent zu adcChannel!
uint32_t tempCRC;

/* Deklaration der Funktionen ---------------------------------------------------------*/

void TxUART();
void TempTxUART(uint16_t bufferTxSize, uint8_t *tempC);
void ntcNumberTxUART();
void blankTxUART(uint8_t *divider);
void CRCTxUART(uint32_t tempCRC);

#endif /* INC_TRANSMISSION_H_ */
