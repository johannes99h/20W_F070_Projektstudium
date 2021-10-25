/*
 * adc.c
 *
 *  Created on: Jul 6, 2021
 *      Author: johan
 */

#include "adc.h"

/*
 * 		Definition der Variablen
 */

uint16_t ntcResistance25[adcChannel] =	{	10000,
											10000,
											10000,
											10000,
											10000,
											10000,
											10000,
											10000,
											10000
										};
uint8_t adcSamples = 5;								// erfüllt den gleichen Zweck wie buff_length -> zsm.führen

/*
 * 		Funktionsdefinitionen
 */

uint16_t *ClearADCBuffer(uint16_t *adcBuffer)
{
	for(int i = 0; i < (adcChannel * adcSamples); i++)
	{
		// Übertragung des Werts vom Buffer auf ein weiteres Array
		adcVal[i] = adcBuffer[i];

		// Nullsetzung der Position des übertragenen Buffereintrags
		adcBuffer[i] = 0;
	}

	return adcVal;
}


uint16_t *GetADCMeanValue(uint16_t *adcVal, uint8_t adcSamples)
{
	int k = 0;

	// Aufaddieren der Samples pro Channel
	for(int i = 0; i < adcChannel; i++)
	{
		for(int i = 0; i < adcChannel; i++)
		{
			for(int j = 0; j < adcSamples; j++)
			{
				k = i + j * adcSamples;

				adcBufferMeanValue[i] = adcVal[k];
			}
		}

		// Mittelwertbildung durch Teilen der Summe durch die Sample-Zahl
		adcBufferMeanValue[i] = adcBufferMeanValue[i] / adcSamples;
	}

	return adcBufferMeanValue;
}


uint16_t *GetADCResistance(uint16_t *adcBufferMeanValue)
{
	// Berechnung der Spannung an den NTCs
	for(int i = 0; i < adcChannel; i++)
	{
		adcVoltage[i] = 33 * (adcBufferMeanValue[i] * 10) / 4095;
	}

	// Berechnung der einzelnen NTC-Widerstände
	for(int i = 0; i < adcChannel; i++)
	{
		ntcResistance[i] = (adcVoltage[i] * ntcResistance25[i]) / (330 - adcVoltage[i]);
	}

	return ntcResistance;

}
