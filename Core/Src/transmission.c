/*
 * transmission.c
 *
 *  Created on: Jul 6, 2021
 *      Author: johan
 */

#include "transmission.h"

/* Definition der Variablen ---------------------------------------------------------*/

uint8_t adcChannels = 9;
uint8_t howmany; 				// Anzahl der Sternchen!


/* Definition der Funktionen ---------------------------------------------------------*/

/*
 * 	@brief Senden der NTC-Nummer, der Temperatur, des zugehörigen CRCs & mehrerer "Stop"-Zeichen
 * 		***** NTC1 * 25°C * CRC1 ** NTC2 * 30°C * CRC2 ** ... **********
 */

void TxUART(uint8_t adcChannels, uint8_t *tempC)						// Parallelisierung mit Berechnung wäre irgendwie sinnvoll... -> was hab ich damit gemeint?
{
	uint8_t ntcNumber = 0;

	// HAL_UART_DMAPause(&huart1);
	// HAL_UART_DMAStop(&huart1);

	// "Header" -> sollte von auswertender Software erkannt werden
	blankTxUART(5);

	for(int j = 0; j < adcChannels; j++)
	{
		ntcNumber = j;

		ntcNumberTxUART(ntcNumber);
		blankTxUART(1);
		singleTempTxUART(ntcNumber, tempC);
		blankTxUART(1);
		// CRCTxUART(tempCRC);										// Fkt. noch nicht geschrieben
		blankTxUART(2);
	}

	// "Tail" -> sollte von auswertender Software erkannt werden (Möglichkeit, eine Plausibilitätskontrolle durch Zählen der Temp.s oder so, einzubauen
	blankTxUART(10);


	// uint8_t placeholder[1] = "_";
	// HAL_UART_Transmit_DMA(&huart1, placeholder, sizeof(placeholder));
	// HAL_UART_DMAResume(&huart1);
}


void singleTempTxUART(uint8_t ntcNumber, uint8_t *tempC)
{
	uint8_t bufferTempSize;
	char bufferTemp[3];																	// da Temp. max. dreistellig

	bufferTempSize = sprintf(bufferTemp, "%d", tempC[ntcNumber]);

	HAL_UART_Transmit(&huart1, (uint8_t *) bufferTemp, bufferTempSize, 10);
}


/*
 * 	@brief	Übertragung der Nummer des zugehörigen NTCs 								-> auf Empfängerseite benennen!
 * 	@param	Pointer zum Array, der NTC-Nummern 											-> eigentlich überflüssig...
 */

void ntcNumberTxUART(uint8_t ntcNumber)
{
	uint8_t bufferNtcNumberSize;
	char bufferNtcNumber[5];

	bufferNtcNumberSize = sprintf(bufferNtcNumber, "NTC%d", ntcNumber);


	HAL_UART_Transmit(&huart1, (uint8_t *)bufferNtcNumber, bufferNtcNumberSize, 10);
	// beim Empfang mittels Bitshift zerlegen & ablehnen, falls Bits vor der ersten 1 ungleich Null sind!
}


/*
 * 	@brief "UART-Zwischenframe"
 * 	@param	ASCII-codiertes Zeichen														-> auf Empfängerseite als "Stop" erkennen
 */

void blankTxUART(uint8_t howmany)
{
	uint8_t divider[1] = "*";

	for(int i = 0; i < howmany; i++)
	{
		HAL_UART_Transmit(&huart1, divider, sizeof(divider), 10);
	}
}

/*
 * 	@brief "UART-Zwischenframe"
 * 	@param	ASCII-codiertes Zeichen														-> auf Empfängerseite als "Stop" erkennen
 */

int CRCTxUART(uint32_t tempCRC)
{
	uint8_t bufferCrcSize;
	char bufferCrc[8];

	bufferCrcSize = sprintf(bufferCrc, "%ld", tempCRC);

	HAL_UART_Transmit(&huart1, (uint8_t *)bufferCrc, bufferCrcSize, 10);

	return 0;
}


/*
 * Einstellungen für Logic Analyzer
 * 		2400 Bit/s
 * 		7 Bits per Transfer
 * 		1 Stop Bit
 * 		Even Parity
 * 		LSB First
 */
