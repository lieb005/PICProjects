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
extern "C" {
#endif

//#define TEMP AN0
#if 0

#if 1
//3.3k = R1, 10k = R2
#define GAIN ((double)4.0303)	// Gain Multiplier for Op-Amp (1+100/33)

#elif 1
//10k = R1, 56k = R2
#define GAIN ((double)6.6)	// Gain Multiplier for Op-Amp (1+100/33)
#else
//10k = R1, 56k = R2
// ~0-40
#define GAIN ((double)6.6)	// Gain Multiplier for Op-Amp (1+100/33)
#endif

#define STEP ((double)0.0048828125)			// 5.0/1024.0  // 5V / 1024 steps // made a const to reduce math
#define SCALE (STEP/(double)0.0195/GAIN)		//19.5mV / °C
#define OFFSET ((double)20.5128205128)			//.4/.0195  //400mV @ 0°C
#define TEMP_REAL (((double) ADRES) * SCALE - OFFSET)

#else

//R2 - feedback resistor
#define R1		((double)10.0)
#define R2		((double)56.0)
#define GAIN	(R2/R1)			// Gain Multiplier for Op-Amp (1+100/33)

#define STEPS	((double)1024.0)		// Total steps for ADC
#define VOLTS	((double)5.0)			// Total wolts for ADC
#define SCALE	((double)0.0195)		//19.5mV / °C

	// voltage divider reference
#define RPLUS	((double)12.0)			// 1.2k resistor to +
#define RNEG	((double)1.0)			// .1k resistor to -
#define R_DIV	(VOLTS/((RPLUS + RNEG)/RNEG))	// Total voltage at voltage divider

#define OFFSET	((double).4 - R_DIV)	//.4-voltage divider offset  //400mV-div @ 0°C

#define MATH_DONE (.0447144)
#if 1
#define TEMP_REAL ( ((double)ADRES) * VOLTS/STEPS / GAIN / SCALE - (OFFSET / SCALE) ) // Final thing
#else
#define TEMP_REAL (((double)ADRES) * MATH_DONE)
#endif

#endif

#define F(a) (a * 5.0 / 9.0 + 32.0)
#define C(a) (a)

void printTemp(uint8_t digits);
float getTemp();
void initTemp();

float oldTemps[] = {25f, 25f, 25f, 25f};

struct sMenu tempMenu;


#ifdef	__cplusplus
}
#endif

#endif	/* TEMP_H */

