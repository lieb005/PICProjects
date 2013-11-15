/* 
 * File:   defs.h
 * Author: mark
 *
 * Created on 10. November 2013, 20:16
 */

#ifndef DEFS_H
#define	DEFS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <xc.h>
#include <plib.h>

#define LOG2 0.30102999566398119521373889472449


	// Preprocessor magic
#define	CAT2(a,b)		CAT2EXP(a, b)
#define	CAT2EXP(a,b)		a ## b
#define	CAT3(a,b,c)		CAT3EXP(a, b, c)
#define	CAT3EXP(a,b,c)		a ## b ## c


#define OFF	0
#define ON	1

#define OUTPUT	0
#define INPUT	1

	//up to 10^9 because 10^10 > 2^16
	const uint32_t pow10[] = {
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000
	};

#define POW10(a) (pow10[a])

#define WAIT 0

#define TMR0_RESET_VAL (65536-50356)
#define TMR0_BIG_TICKS (3+1)


	extern void wait(uint32_t count);

	uint8_t countBits(uint32_t num);
	uint32_t hibit(uint32_t x);
	uint32_t lowbit(uint32_t x);

	//double log2(double num);
	uint32_t log2(uint32_t num);
	int32_t maxSize(uint8_t digits);



#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */

