/* 
 * File:   temp.h
 * Author: mark
 *
 * Created on 11. November 2013, 09:55
 */

#ifndef TEMP_H
#define	TEMP_H

#include "menu.h"
#include "defs.h"
#include "temp_main.h"

#ifdef	__cplusplus
extern "C"
{
#endif

//#define TEMP AN0
#define GAIN (4.03030303030303030303030303)	// Gain Multiplier for Op-Amp (1+100/33)
#define STEPS (0.0048828125)			// 5.0/1024.0  // 5V / 1024 steps // made a const to reduce math
#define SCALE (STEPS/0.0195/GAIN)		//19.5mV / °C
#define OFFSET (20.5128205128)			//.4/.0195  //400mV @ 0°C

#define F(a) (a * 5 / 9 + 32)
#define C(a) (a)

void* printTemp(uint8_t digits);
float getTemp();
void initTemp();

float oldTemps[4];

struct sMenu tempMenu;


#ifdef	__cplusplus
}
#endif

#endif	/* TEMP_H */

