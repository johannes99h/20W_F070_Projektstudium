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
 * 	@brief Senden der NTC-Nummer, des Werts & eines "Stop"-Zeichens
 */

void TxUART()
{
	// blankTxUART(divider);
	ntcNumberTxUART(adcChannels);
	// TempTxUART(bufferTxSize, tempC);													-> Funktion muss angepasst werden!
	// CRCTxUART(tempCRC);
	//if(blankTxUART(divider) != 0)
	// {
		// eigene Error-Handler-Funktion, vlt. Senden dass in der Funktion was schief gelaufen ist?
	// }
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

void ntcNumberTxUART(uint8_t adcChannels)
{
	HAL_UART_Transmit(&huart1, adcChannels, sizeof(adcChannels), 10);
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
