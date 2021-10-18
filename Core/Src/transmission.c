/*
 * transmission.c
 *
 *  Created on: Jul 6, 2021
 *      Author: johan
 */

#include "transmission.h"

/* Definition der Variablen ---------------------------------------------------------*/

uint8_t divider[1] = "*";
uint8_t ntcNumber[adcChannel] = {														// ist doch vollkommen unnötig?!
	 	 	 	 	 	 	0b000000000,
							0b000000001,
							0b000000010,
							0b000000011,
							0b000000100,
							0b000000101,
							0b000000110,
							0b000000111,
							0b000001000
						};



/* Definition der Funktionen ---------------------------------------------------------*/

/*
 * 	@brief Senden der NTC-Nummer, des Werts & eines "Stop"-Zeichens
 */

void TxUART()
{
	blankTxUART(divider);
	ntcNumberTxUART(adcChannel);
	// TempTxUART(bufferTxSize, tempC);													-> Funktion muss angepasst werden!
	CRCTxUART(tempCRC);
	blankTxUART(divider);
}



/*
 * 	@brief	Senden der gemessenen Temperatur eines NTCs
 * 	@param	Pointer zur mittels Lookup-Table ermittelten Temperatur
 */

void TempTxUART(uint16_t bufferTxSize, uint8_t *tempC)
{
	// alte Lösung -> zu ineffizient
	for(int i = 0; i < adcChannel; i++)
	{
		bufferTxSize = sprintf(bufferTx, "NTC%d, %d\r\n", i, tempC[i]);
		HAL_UART_Transmit(&huart1, (uint8_t *) bufferTx, bufferTxSize, 10);
	}

	// neue Lösung -> nur eine Temperatur übertragen
	HAL_UART_Transmit(&huart1, tempC, sizeof(tempC), 10);								// wie Timeouts sinnvoll umsetzen? (weglassen?)
}



/*
 * 	@brief	Übertragung der Nummer des zugehörigen NTCs 								-> auf Empfängerseite benennen!
 * 	@param	Pointer zum Array, der NTC-Nummern 											-> eigentlich überflüssig...
 */

void ntcNumberTxUART(uint8_t *ntcNumber)
{
	HAL_UART_Transmit(&huart1, ntcNumber, sizeof(ntcNumber), 10);
	// beim Empfang mittels Bitshift zerlegen & ablehnen, falls Bits vor der ersten 1 ungleich Null sind!
}



/*
 * 	@brief "UART-Zwischenframe"
 * 	@param	ASCII-codiertes Zeichen														-> auf Empfängerseite als "Stop" erkennen
 */

void blankTxUART(uint8_t *divider)
{
	HAL_UART_Transmit(&huart1, divider, sizeof(divider), 10);
}

void CRCTxUART(uint32_t tempCRC)
{

}
