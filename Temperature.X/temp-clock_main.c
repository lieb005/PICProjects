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
#pragma config LVP	 =	OFF
#else
#pragma config DEBUG =	OFF
#pragma config MCLRE =	ON
#pragma config WDT	 =	OFF
#pragma config LVP	 =	ON
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
	while (true)
	{
		if (cnt > 20L)
		{
			cnt = 0;
			//menu->printFn(menu->digits);
			//writeLong(DIG0_7, 28572043L);
			update();
			//LATA5 = ~LATA5;
		}
		cnt++;
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
	LATC = (RCON & 0b1)>> 0 | (RCON & 0b10) >> 0 | (RCON & 0b100) >> 0 | (RCON & 0b1000) >> 2 | (RCON & 0b100000) >> 2;
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
	T1CON = T1C;
	TMR1 = RTC_OFFSET;
	TMR1IF = CLEAR;
	TMR1IE = ON;
	TMR1ON = ON;
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
#ifdef TEMP
			getTemp();
#endif
			menu->printFn(menu->digits);
			LATA5 = ~LATA5;
			//printRTC(rtcMenu.digits);
		}
		asm ("CLRWDT");
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
		}
	}
	GIE = ON;
}
