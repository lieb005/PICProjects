/* 
 * File:   doorbell.c
 * Author: talia
 *
 * Created on May 3, 2016, 9:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#define _XTAL_FREQ 4000000 //oscillator frequency for delays.

// Config Bits
#pragma config PWRTE = ON
#pragma config WDTE = OFF
#pragma config MCLRE = OFF
#pragma config FOSC = INTRCIO

#define CAT(a,b) (a##b)

#define CHIME1 0
#define CHIME4 1
#define FRONT  2
#define BACK   3
#define CHIME5 4
#define CHIME6 5

#define Fosc4 (1000000L)

// Prototypes
void config();
void ring(char front);
// Chime is 1, 4, 5, 6, where 1 is lowest and # is interval from #1
void ding(char chime);
void sleep_ms(long duration);

/*
 * 
 */
int main(void)
{
	config();
	while (1)
	{
		GPIO=~GPIO;
		__delay_ms(500);
	}
	return (EXIT_SUCCESS);
}

// "front" tells it to ring either front or back things
// Possible values: FRONT, BACK

void ring(char front)
{
	if (front == FRONT) {
		// Ring for Front
		ding(CHIME6);
		ding(CHIME4);
	} else if (front == BACK) {
		ding(CHIME5);
		ding(CHIME1);
	}
	SLEEP();
}

// Ding a chime

void ding(char chime)
{
	char i = 1;
	do {
		switch (chime) {
		case CHIME1:
			GPIO0 = i;
			break;
		case CHIME4:
			GPIO1 = i;
			break;
		case CHIME5:
			GPIO4 = i;
			break;
		case CHIME6:
			GPIO5 = i;
			break;
		}
		__delay_ms(100);

	} while (i--);
}

void config()
{
	// Interrupts
	// Global
	GIE = 0;
	// Peripheral
	PEIE = 1;
	// GPIOs
	GPIE = 1;
	IOC = 0b001100;

	// Config IO
	TRISIO = 0b001100;
	IOC = 0b001100;
	// all ADC pins set to digital I/O
	ANSEL = 0;
}

void interrupt ISR()
{
	if (GPIE && GPIF) {
		// Logic inverted because pull ups
		if (!GP2)
			ring(FRONT);
		if (!GP3)
			ring(BACK);
		GPIF = 0;
	}
}

