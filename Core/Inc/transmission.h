#ifndef INC_TRANSMISSION_H_
#define INC_TRANSMISSION_H_

#include "stdio.h"
#include "stdint.h"
#include "stm32f0xx_hal.h"


/* externe Definitionen ---------------------------------------------------------*/

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_tx;


/* Deklaration der Variablen ---------------------------------------------------------*/

uint8_t 	divider[1];
uint8_t 	adcChannels;
uint8_t 	howmany;
uint32_t 	tempCRC;

/* Deklaration der Funktionen ---------------------------------------------------------*/

void	TxUART(uint8_t adcChannels, uint8_t *tempC, uint32_t *CRCtempC, uint16_t *checksum);
void	singleTempTxUART(uint8_t ntcNumber, uint8_t *transmitTemp);
void	ntcNumberTxUART(uint8_t ntcNumber);
void	blankTxUART(uint8_t howmany);
void	CRCTxUART(uint8_t ntcNumber, uint32_t *CRCtempC);
void	ChecksumTxUART(uint8_t ntcNumber, uint8_t *tempC, uint16_t *checksum);

#endif /* INC_TRANSMISSION_H_ */
