/* 
 * File:   main.c
 * Author: mark
 *
 * Created on 7. Oktober 2013, 01:41
 */

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <htc.h>
#include <xc.h>

//#define EEPROM

// 46 HRs
//#define START_TIME	(65536-61184)
//#define BIG_TIME	(1+315856L)

//1 Sec
//#define START_TIME	(65536-59464)
//#define BIG_TIME	(1+1)

//Fast
#define START_TIME	(65536-65535)
#define BIG_TIME	(1+0)

#define OFF 0
#define ON 1
#define DISABLE 0
#define ENABLE 1
#define UNSET 0
#define SET 1
#define OUTPUT 0
#define INPUT 1

uint32_t time;
uint8_t blink;

void setup()
{
    asm("nop");
	// Disable Analog Inputs
	ANSEL = 0;
	//GPIO's
	TRISIO = 0b000000;
	//GPIO = 0b000000;
	//nGPPU = !ON;
	//TRISIO2 = INPUT;
	GPIO0 = ON;
	while(1);


	//Interrupts
	GIE = ENABLE;
	PEIE = ENABLE;

	//TMR1
	T1CON = 0b00110000;
	TMR1 = START_TIME;
	time = BIG_TIME;
	TMR1IE = ENABLE;
	TMR1IF = UNSET;

	//INT0
	INTE = ENABLE;
	INTF = UNSET;
	INTEDG = 1;

	//load EEPROM
#ifdef EEPROM
	EEADR = 0;
	RD = 1;
	time = EEDATA;
	EEADR = 1;
	RD = 1;
	time |= EEDATA << 8;
#endif
}

/*
 * 
 */
int main(int argc, char** argv)
{
	setup();
	//return;
	while (1)
	{

		TMR1ON = ON;

		GPIO1 = ON;
		while (time);
		GPIO1 = OFF;

		TMR1ON = OFF;
		TMR1 = START_TIME;
		time = BIG_TIME;

		INTE = ENABLE;
		blink = 1;
		GPIO0 = ON;
		while (blink)
		{
			GPIO1 = ~GPIO1;
			uint32_t cnt = 500000;
			while (cnt-- );
			GPIO0 = ~GPIO0;
		}
	}
	return (EXIT_SUCCESS);
}

void interrupt isr()
{
	GIE = DISABLE;
	if (TMR1IE && TMR1IF)
	{
		TMR1IF = UNSET;
		TMR1 = 0;
		time--;
		GPIO1 = ~GPIO1;
#ifdef EEPROM

		EEDATA = time & 0xFF;
		EEADR = 0;
		WREN = 1;
		EECON2 = 0x55;
		EECON2 = 0xAA;
		WR = 1;
		while (WR == 1);
		WREN = 0;

		EEDATA = (time >> 8) & 0xFF;
		EEADR = 1;
		WREN = 1;
		EECON2 = 0x55;
		EECON2 = 0xAA;
		WR = 1;
		while (WR == 1);
		WREN = 0;
#endif
	}
	if (INTE && INTF)
	{
		INTF = UNSET;
		blink = 0;
		INTE = DISABLE;
	}
	GIE = ENABLE;
}
