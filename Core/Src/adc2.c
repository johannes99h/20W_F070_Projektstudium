/*
 * adc2.c
 *
 *  Created on: 25.10.2021
 *      Author: johan
 */


// #define buffLength 10

/*
 * 		Deklarationen
 */


/*
uint8_t adcSamples;
uint16_t adcBuffer[buffLength];
uint16_t adcVal[buffLength];
uint16_t adcBufferMeanValue[adcChannel];
uint16_t adcVoltage[adcChannel];
uint16_t ntcResistance[adcChannel];
*/


/*
 * 		Funktionsdefinitionen
 */

/*
uint16_t *ClearADCBuffer(uint16_t *adcBuffer, uint8_t adcChannel)
{
	for(int i = 0; i < adcChannel; i++)
	{
		// Übertragung des Werts vom Buffer auf ein weiteres Array
		adcVal[i] = adcBuffer[i];

		// Nullsetzung des übertragenen Buffereintrags
		adcBuffer[i] = 0;
	}

	return adcVal;
}


uint16_t GetADCMeanValue(uint16_t *adcVal, uint8_t adcSamples)	// buffLength == adcSamples? -> ja
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

*/
