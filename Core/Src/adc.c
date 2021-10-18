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
uint16_t tempZero = 298;

/*
 * 		Funktionsdefinitionen
 */

uint16_t *ClearADCBuffer(uint16_t *adcBuffer)
{
	for(int i = 0; i < adcChannel; i++)
	{
		adcVal[i] = adcBuffer[i];
	}

	//assign buffer values to the different NTCs (experimental - is there a better way to do that?)
	adcBufferMeanValue[0] = adcVal[0] + adcVal[3] + adcVal[6];				// FOR
	adcBufferMeanValue[1] = adcVal[1] + adcVal[4] + adcVal[7];				// SCHLEIFE
	adcBufferMeanValue[2] = adcVal[3] + adcVal[5] + adcVal[8];				// EINBAUEN

	for(int i = 0; i < adcChannel; i++)
	{
		adcBufferMeanValue[i] = adcBufferMeanValue[i] / 3;					// divide by adcChannel
	}

	return adcBufferMeanValue;
}

uint32_t *GetADCResistance(uint16_t *adcBufferMeanValue)
{
	//voltage at the NTCs
	for(int i = 0; i < adcChannel; i++)
	{
		adcVoltage[i] = 33 * (adcBufferMeanValue[i] * 10) / 4095;
	}

	//calculate related NTC-resistance
	for(int i = 0; i < adcChannel; i++)
	{
		ntcResistance[i] = (adcVoltage[i] * ntcResistance25[i]) / (330 - adcVoltage[i]);
	}

	return ntcResistance;

}
