/* 
 * File:   main.c
 * Author: mark
 *
 * Created on 7. Oktober 2013, 01:41
 */

#include "disp.h"
#include "RTC.h"
#include "defs.h"
#include "temp.h"
#include "menu.h"
#include "buttons.h"

//#define DBG
#ifdef DBG
#pragma config DEBUG =	ON
#pragma config MCLRE =	ON
#pragma config WDT	 =	OFF
#endif

#pragma config FOSC =	HS
#pragma config PWRT =	ON
#pragma config PBADEN =	OFF
#pragma config CPUDIV =	OSC3_PLL4
#pragma config PLLDIV =	4
#pragma config USBDIV =	2

void setup();

/*
 *
 */
int main(int argc, char** argv)
{
	setup();
	uint32_t cnt = 0;
	while (true) {
		if (cnt > 200L) {
			cnt = 0;
			//printFn(DIG0_6);
			//update();
		}
		cnt++;
		//LATA5 = ~LATA5;
	}
	return (EXIT_FAILURE);
}

void setup()
{
	//Interrupts
	GIE = ON;
	PEIE = ON;

	startDisp();
	initRTC();
	//LATA5 = ON;

	initTemp();
	setupButtons();

	printFn = &printTemp;
	//printFn = &printRTC;

	//Status LED Config
	TRISA5 = 0;
	//LATA5 = 1;
}

void interrupt high_isr(void)
{
	if (TMR1IE && TMR1IF) {
		TMR1ON = OFF;
		TMR1IF = CLEAR;
		TMR1 = 0;
		if (++rtc_big_ticks > RTC_TICKS) {
			rtc_big_ticks = 0;
			TMR1 = RTC_OFFSET;
			tick(second);
			if (printFn == &printTemp) {

				printFn(DIG0_4);
			} else if (printFn == &printRTC) {
				printFn(DIG0_7);
			}


			update();
		}
		TMR1ON = ON;
	}
	if (TMR0IE && TMR0IF) {
		TMR0IF = CLEAR;
		TMR0ON = OFF;
		TMR0 = 0;
		if (++tmr0BigCounts > TMR0_BIG_TICKS) {
			buttons();
			TMR0 = TMR0_RESET_VAL;
			tmr0BigCounts = 0;
		}
		TMR0ON = ON;
	}
}
#if 0

void low_priority interrupt low_isr(void)
{
}
#endif