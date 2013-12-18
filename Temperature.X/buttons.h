/* 
 * File:   buttons.h
 * Author: mark
 *
 * Created on 11. November 2013, 10:32
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#include "defs.h"
#include "temp_main.h"

#ifdef	__cplusplus
extern "C"
{
#endif

/*
 * 7	- enable
 * 6	- 8-bit
 * 5	- ext clock
 * 4	- tick on high to low edge
 * 3	- prescale bypass
 * 2-0	- prescale 1:2^(val+1)
 */
// No prescale, FOSC/4, every .05 sec
#define TMR0_CFG		(0b00001000)
//#define TMR0_RESET_VAL	(65536-46080)
//#define TMR0_BIG_TICKS	(1+1220)
#define TMR0_RESET_VAL	(65536-32767)
#define TMR0_BIG_TICKS	(0)


void setupButtons();
void buttons();

uint32_t tmr0BigCounts;
//#define PRT (((LATC & 0b11110000) >> 4) | ((LATB & 0b00001111) << 4))
#define PRT PORTB
#define TRS	TRISB

#define WAITCNT 15

#define INV 

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

