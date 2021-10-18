/*
 * processing.c
 *
 *  Created on: Jul 6, 2021
 *      Author: johan
 */

#include "processing.h"

/* Definition der Variablen ---------------------------------------------------------*/


static const LUT_temp table[LUT_table_size] = {											// richtige NTCs & erweitern
		{ .LUT_temp_C =   0 , .LUT_ntcRTtoR25 = 29287 },
		{ .LUT_temp_C =   5 , .LUT_ntcRTtoR25 = 23311 },
		{ .LUT_temp_C =  10 , .LUT_ntcRTtoR25 = 18684 },
		{ .LUT_temp_C =  15 , .LUT_ntcRTtoR25 = 15075 },
		{ .LUT_temp_C =  20 , .LUT_ntcRTtoR25 = 12240 },
		{ .LUT_temp_C =  25 , .LUT_ntcRTtoR25 = 10000 },
		{ .LUT_temp_C =  30 , .LUT_ntcRTtoR25 =  8218 },
		{ .LUT_temp_C =  35 , .LUT_ntcRTtoR25 =  6791 },
		{ .LUT_temp_C =  40 , .LUT_ntcRTtoR25 =  5642 },
		{ .LUT_temp_C =  45 , .LUT_ntcRTtoR25 =  4712 },
		{ .LUT_temp_C =  50 , .LUT_ntcRTtoR25 =  3955 },
		{ .LUT_temp_C =  55 , .LUT_ntcRTtoR25 =  3336 },
		{ .LUT_temp_C =  60 , .LUT_ntcRTtoR25 =  2826 },
		{ .LUT_temp_C =  65 , .LUT_ntcRTtoR25 =  2405 },
		{ .LUT_temp_C =  70 , .LUT_ntcRTtoR25 =  2055 },
		{ .LUT_temp_C =  75 , .LUT_ntcRTtoR25 =  1764 },
		{ .LUT_temp_C =  80 , .LUT_ntcRTtoR25 =  1520 },
		{ .LUT_temp_C =  85 , .LUT_ntcRTtoR25 =  1314 },
		{ .LUT_temp_C =  90 , .LUT_ntcRTtoR25 =  1141 },
		{ .LUT_temp_C =  95 , .LUT_ntcRTtoR25 =   993 },
		{ .LUT_temp_C = 100 , .LUT_ntcRTtoR25 =   868 },
		{ .LUT_temp_C = 105 , .LUT_ntcRTtoR25 =   761 },
		{ .LUT_temp_C = 110 , .LUT_ntcRTtoR25 =   669 },
		{ .LUT_temp_C = 115 , .LUT_ntcRTtoR25 =   591 },
		{ .LUT_temp_C = 120 , .LUT_ntcRTtoR25 =   523 },
		{ .LUT_temp_C = 125 , .LUT_ntcRTtoR25 =   464 },
		{ .LUT_temp_C = 130 , .LUT_ntcRTtoR25 =   413 },
		{ .LUT_temp_C = 135 , .LUT_ntcRTtoR25 =   368 },
		{ .LUT_temp_C = 140 , .LUT_ntcRTtoR25 =   330 },
		{ .LUT_temp_C = 145 , .LUT_ntcRTtoR25 =   295 },
		{ .LUT_temp_C = 150 , .LUT_ntcRTtoR25 =   266 },
		{ .LUT_temp_C = 155 , .LUT_ntcRTtoR25 =   240 },
		{ .LUT_temp_C = 160 , .LUT_ntcRTtoR25 =   217 },
		{ .LUT_temp_C = 165 , .LUT_ntcRTtoR25 =   196 },
		{ .LUT_temp_C = 170 , .LUT_ntcRTtoR25 =   178 },
		{ .LUT_temp_C = 175 , .LUT_ntcRTtoR25 =   162 },
		{ .LUT_temp_C = 180 , .LUT_ntcRTtoR25 =   147 },
};



/* Definition der Funktionen ---------------------------------------------------------*/

/*
 * 	@brief	Temperaturermittlung durch Abgleich von Verhältnis zwischen gemessenem und normalem NTC-Widerstand (298K)
 * 	@param	Pointer zum Lookup-Table
 * 	@param	???																			-> sollte hier nicht der NTC-Wert übergeben werden?
 * 	@param	???
 * 	@ret	Integer
 */

uint8_t GetTempCfromLUT(const LUT_temp *table, uint16_t ntcRTtoR25, int size)
{
	//int i = 0;
	int j = 0;
	uint16_t t;


	// mit Näherungsformel berechnete Widerstandswerte in 1-Grad-Schritten für Murata NXFT15XH103-NTCs
    static const uint16_t LUT[151] = {
										28224, 	26978, 	25796, 	24674, 	23608, 	22595, 	21632, 	20717, 	19847, 	19019,
										18231, 	17481, 	16767, 	16087, 	15438, 	14820, 	14231, 	13669, 	13133, 	12622,
										12133, 	11667, 	11221, 	10796, 	10389, 	10000, 	9628, 	9272, 	8932, 	8606,
										8295,	7996,	7710,	7436,	7174,	6922,	6681,	6449, 	6227,	6014,
										5810,	5614,	5425,	5244,	5070,	4903,	4743,	4589,	4440,	4297,
										4160,	4028,	3901,	3779,	3661,	3547,	3438,	3333,	3231,	3133,
										3039,	2948,	2861,	2776,	2695,	2616,	2540,	2467,	2396,	2327,
										2261,	2197,	2136,	2076,	2019,	1963,	1909,	1857,	1807,	1758,
										1711,	1665,	1621,	1578,	1537,	1497,	1458,	1420,	1384,	1349,
										1315,	1281,	1249,	1218,	1188,	1158,	1130,	1102,	1076,	1050,
										1024,	1000,	976,	953,	930,	909,	888,	867,	847,	828,
										809,	790,	772,	755,	738,	722,	706,	690,	675,	660,
										646,	632,	619,	605,	593,	580,	568,	556,	544,	533,
										522,	511,	501,	491,	481,	471,	462,	452,	443,	435,
										426,	418,	410,	402,	394,	386,	379,	372,	365,	358,
										351
    								};


	while(ntcRTtoR25 < LUT[j])
	{
		j++;
	}

	t = j;

	/*
	while((i < size) && (ntcRTtoR25 < table[i].LUT_ntcRTtoR25))
	{
		i++;
	}

	if(i == size)
	{
		return table[i-1].LUT_temp_C;
	}

	if(i == 0)
	{
		return table[i].LUT_temp_C;
	}

	m = (table[i].LUT_temp_C - table[i-1].LUT_temp_C) / (table[i].LUT_ntcRTtoR25 - table[i-1].LUT_ntcRTtoR25);
	t = m * (ntcRTtoR25 - table[i].LUT_ntcRTtoR25) + table[i].LUT_temp_C;	//interpolation doesn't work properly
	*/

	return t;
}

uint32_t generateCRC32(uint8_t temp)
{
	return 0;
}
