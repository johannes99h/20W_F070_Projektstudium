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

		uint16_t 	ntcResistance25[adcChannel] =	{	10000,
														10000,
														10000,
														10000,
														10000,
														10000,
														10000,
														10000,
														10000
													};
const 	uint8_t 	adcSamples = 5;								// erfüllt den gleichen Zweck wie buff_length -> zsm.führen
		uint8_t 	tempC[adcChannel] = { 0 };
		uint16_t	checksum[3] = { 0 };
		uint32_t 	CRCtempC[adcChannel] = { 0 };
		uint8_t 	checksumNumber = 0;

/*
 * 		Funktionsdefinitionen
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	scheduler();
}

void scheduler()
{
	ClearADCBuffer(adcBuffer);

	GetADCMeanValue(adcVal, 5);

	GetADCResistance(adcBufferMeanValue);

	GetTempCArray(tempC, adcChannel, LUT, ntcResistance, LUToldValues);

	for(int i = 0; i < adcChannel; i++)			// auch noch in eine Funktion packen, um hier nur noch den Call stehen zu haben
	{
		CRCtempC[i] = generateCRC32(tempC[i], adcChannel);
	}

	checksumNumber = 0;
	for(int i = 0; i < 3; i++)
	{
		checksum[i] = generateChecksum(tempC, checksumNumber);
		checksumNumber++;
	}

	TxUART(adcChannel, tempC, CRCtempC, checksum, millis);		// später auch CRCtempC übergeben
}


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
		// Aufteilung der Berechnungsoperation notwendig, da keine FPU vorhanden
		uint32_t tmp = 0;
		tmp = (ntcResistance25[i] * (330 - adcVoltage[i]));
		ntcResistance[i] = (tmp / adcVoltage[i]);
	}

	return ntcResistance;

}
