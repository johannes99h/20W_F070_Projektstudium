/*
 * transmission.c
 *
 *  Created on: Jul 6, 2021
 *      Author: johan
 */

#include "transmission.h"

/* Definition der Variablen ---------------------------------------------------------*/

uint8_t adcChannels = 9;


/* Definition der Funktionen ---------------------------------------------------------*/

/*
 * 	@brief Senden der NTC-Nummer, der Temperatur, des zugehörigen CRCs & mehrerer "Stop"-Zeichen
 * 		***** NTC1 * 25°C * CRC1 ** NTC2 * 30°C * CRC2 ** ... **********
 */

void TxUART(uint8_t adcChannels, uint8_t *tempC)						// Parallelisierung mit Berechnung wäre irgendwie sinnvoll...
{
	uint8_t ntcNumber = 0;

	for(int i = 0; i < 5; i++)
	{
		blankTxUART();
	}

	for(int j = 0; j < adcChannels; j++)
	{
		ntcNumber = j;

		ntcNumberTxUART(ntcNumber);
		blankTxUART();
		// TempTxUART(bufferTxSize, tempC);													// -> Funktion muss angepasst werden!
		singleTempTxUART(ntcNumber, tempC);
		blankTxUART();
		// CRCTxUART(tempCRC);
		for(int k = 0; k < 2; k++)
		{
			blankTxUART();
		}
	}

	for(int l = 0; l < 10; l++)
	{
		blankTxUART();
	}
}


void singleTempTxUART(uint8_t ntcNumber, uint8_t *tempC)
{
	uint8_t *transmitTemp;

	transmitTemp = tempC[ntcNumber];
	HAL_UART_Transmit(&huart1, transmitTemp, sizeof(transmitTemp), 10);
}


/*
 * 	@brief	Senden der gemessenen Temperatur eines NTCs
 * 	@param	Pointer zur mittels Lookup-Table ermittelten Temperatur
 */

void TempTxUART(uint16_t bufferTxSize, uint8_t *tempC, uint8_t adcChannels)			// bufferTxSize kann vmtl. auch weg
{
	//alte Lösung -> zu ineffizient, funktioniert aber!
	for(int i = 0; i < adcChannels; i++)
	{
		bufferTxSize = sprintf(bufferTx, "%d", tempC[i]);
		HAL_UART_Transmit(&huart1, (uint8_t *) bufferTx, bufferTxSize, 10);
		blankTxUART();
	}


	// neue Lösung -> nur eine Temperatur übertragen
	// HAL_UART_Transmit(&huart1, tempToTransmit, sizeof(tempToTransmit), 10);								// wie Timeouts sinnvoll umsetzen? (weglassen?)
}


/*
 * 	@brief	Übertragung der Nummer des zugehörigen NTCs 								-> auf Empfängerseite benennen!
 * 	@param	Pointer zum Array, der NTC-Nummern 											-> eigentlich überflüssig...
 */

void ntcNumberTxUART(uint8_t ntcNumber)
{
	HAL_UART_Transmit(&huart1, ntcNumber, sizeof(ntcNumber), 10);
	// beim Empfang mittels Bitshift zerlegen & ablehnen, falls Bits vor der ersten 1 ungleich Null sind!
}


/*
 * 	@brief "UART-Zwischenframe"
 * 	@param	ASCII-codiertes Zeichen														-> auf Empfängerseite als "Stop" erkennen
 */

int blankTxUART()
{
	uint8_t divider[1] = "*";				// sehe (gerade) keinen Grund für eine globale Variable

	HAL_UART_Transmit(&huart1, divider, sizeof(divider), 10);

	return 0;
}

/*
 * 	@brief "UART-Zwischenframe"
 * 	@param	ASCII-codiertes Zeichen														-> auf Empfängerseite als "Stop" erkennen
 */

int CRCTxUART(uint32_t tempCRC)				// in TempTxUART() integrieren? sollte ja eigentlich direkt danach ausgeführt werden...
{
	HAL_UART_Transmit(&huart1, tempCRC, sizeof(tempCRC), 10);

	return 0;
}
