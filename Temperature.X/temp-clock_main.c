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

#define DBG

#ifdef DBG
#pragma config DEBUG =	ON
#pragma config MCLRE =	ON
#pragma config WDT	 =	OFF
#pragma config LVP	 =	OFF
#else
#pragma config DEBUG =	OFF
#pragma config MCLRE =	OFF
#pragma config WDT	 =	OFF
#pragma config WDTPS =  32768
#pragma config LVP	 =	ON
#endif

#pragma config PWRT =	ON
#pragma config PBADEN =	OFF
#pragma config FOSC =	HS
#pragma config CPUDIV =	OSC1_PLL2
#pragma config PLLDIV =	4
#pragma config USBDIV =	2

// With 16MHz Crystal, runs at 4MHz

// 500KHz / 256 / 1000 = approx. .5 seconds
#define UPDATE_TIME_BIG 100
// will run at 500KHz hopefully
#define T2CFG 0b00000011
int tmr2_count = 0;

void setup();

/*
 *
 */
int main(int argc, char** argv)
{
	setup();
	uint32_t cnt = 0;
	while (true)
	{
		if (cnt++ > 20L)
		{
			cnt = 0;
			//menu->printFn(menu->digits);
			//writeLong(DIG0_7, 28572043L);
			//writeString(DIG0_7, "6geolote");
			//update();
			//clearScreen();
		}
		//LATA5 = ~LATA5;
	}
	return (EXIT_SUCCESS);
}

void setup()
{
	//Set all pins as outs and drive them low.  We will configure ins later
	TRISA = 0;
	TRISB = 0;
	TRISC = 0;
	LATA = 0;
	LATB = 0;
	// set LATC to reflect cause of reset
	//LATC = (RCON & 0b1)>> 0 | (RCON & 0b10) >> 0 | (RCON & 0b100) >> 0 | (RCON & 0b1000) >> 2 | (RCON & 0b100000) >> 2;
	//LATC = MASKN(RCON, 0, 0) | MASKN(RCON, 1, 1) | MASKN(RCON, 2, 2) | MASKN(RCON, 4, 3) | MASKN(RCON, 6, 4);
	//Status LED Config
	LATA5 = 1;

	//while (1);

	//Interrupts
	GIE = ON;
	PEIE = ON;
	IPEN = OFF;

	startDisp();
	LATC0 = ON;
#ifdef RTC
	initRTC();
#endif
	LATC0 = OFF;
#ifdef TEMP
	initTemp();
#endif
	setupButtons();

#if DEFAULT==TEMP
	menu = &tempMenu;
#elif DEFAULT==RTC
	menu = &rtcMenu;
#endif
	//printFn = &printRTC;

	LATA5 = 0;

	//Timer0 Config
	tmr0BigCounts = 0;
	T0CON = TMR0_CFG;
	TMR0 = TMR0_RESET_VAL;
	TMR0IF = CLEAR;
	TMR0IE = ON;
	TMR0ON = ON;

	// Timer1 Config
	T1CON = T1CFG;
	TMR1 = RTC_OFFSET;
	TMR1IF = CLEAR;
	TMR1IE = ON;
	TMR1ON = ON;

	// Config Timer 2 for updating the screen
	T2CON = T2CFG;
	TMR2 = 0;
	TMR2IF = CLEAR;
	TMR2IE = ON;
	TMR2ON = ON;
}

void interrupt isr(void)
{
	if (TMR1IE && TMR1IF)
	{
		TMR1IF = CLEAR;
		TMR1ON = OFF;
		TMR1 = 0;
		if (++rtc_big_ticks > RTC_TICKS)
		{
			rtc_big_ticks = 0;
			TMR1 = RTC_OFFSET;
			TMR1ON = ON;
#ifdef RTC
			tick(second);
#endif
			//menu->printFn(menu->digits);
			LATC7 = ~LATC7;
			//printRTC(rtcMenu.digits);
		}
		//asm ("CLRWDT");
		TMR1ON = ON;
	}

	if (TMR2IE && TMR2IF)
	{
		TMR2IF = CLEAR;
		TMR2 = 0;
		if (tmr2_count++ > UPDATE_TIME_BIG)
		{
			tmr2_count = 0;
			update();
			//LATC7 = ~LATC7;
		}
	}

	if (TMR0IE && TMR0IF)
	{
		TMR0IF = CLEAR;
		TMR0ON = OFF;
		TMR0 = 0;
		if (++tmr0BigCounts > TMR0_BIG_TICKS)
		{
			tmr0BigCounts = 0;
			TMR0 = TMR0_RESET_VAL;
			TMR0ON = ON;

			buttons();
#ifdef TEMP
			getTemp();
#endif
			menu->printFn(menu->digits);
			//LATC0 = ~LATC0;
		}
		TMR0ON = ON;
	}
	GIE = ON;
}
