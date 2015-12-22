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


#define BIT0 0b1
#define BIT1 0b10
#define BIT2 0b100
#define BIT3 0b1000
#define BIT4 0b10000
#define BIT5 0b100000
#define BIT6 0b1000000
#define BIT7 0b10000000

#define LOG2 0.30102999566398119521373889472449


// Preprocessor magic
#define	CAT2(a,b)		CAT2EXP(a, b)
#define	CAT2EXP(a,b)		a ## b
#define	CAT3(a,b,c)		CAT3EXP(a, b, c)
#define	CAT3EXP(a,b,c)		a ## b ## c

//Shift a to the right i bits and then isolate the first bit
#define MASK1(a,i)               ((a)&(0b1<<(i)))
// Mask out the specified bit and shift it to bit n
#define MASKN(a,i,n)               ((MASK1(a,i)>>(i))<<n)


#define OFF	0
#define ON	1

// for interrupt priorities
#define HIGH 1
#define LOW 1

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

#define WAIT 1

extern void wait(uint32_t count);

uint8_t countBits(uint32_t num);
uint32_t hibit(uint32_t x);
uint32_t lowbit(uint32_t x);

//float log2(float num);
uint32_t log2(uint32_t num);
int32_t maxSize(uint8_t digits);



#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */

