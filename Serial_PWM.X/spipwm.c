/* 
 * File:   i2cpwm.c
 * Author: mark
 *
 * Created on 14. Oktober 2013, 18:39
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#pragma config FOSC = INTRCIO
#pragma config MCLRE = OFF

unsigned char r = 0;
unsigned char g = 0;
unsigned char b = 0;

#define R GPIO0
#define G GPIO1
#define B GPIO2
#define CS GPIO3
#define CLK GPIO4
#define MOSI GPIO5

void readSPI()
{
	int tmp;
	while (!CS)
	{
		if (CLK)
		{
			tmp = (tmp << 1) | MOSI;
			while (CLK);
		}
	}
	r = (tmp >> 4) & 0xFF;
	g = (tmp >> 2) & 0xFF;
	b = (tmp >> 0) & 0xFF;
}

/*
 * 
 */
int
main(int argc, char** argv)
{
	ANSEL = 0;
	TRISIO0 = 0;
	TRISIO1 = 0;
	TRISIO2 = 0;
	TRISIO3 = 1;
	TRISIO4 = 1;
	TRISIO5 = 1;

	T0CS = 0;
	T0IE = 1;
	T0IF = 0;
	TMR0 = 0;

	GIE = 1;
	IOC3 = 1;
	GPIF = 0;

	PSA = 1;

	while (true)
	{
		if (TMR0 >= r)
		{
			R = 0;
		}
		if (TMR0 >= g)
		{
			G = 0;
		}
		if (TMR0 >= b)
		{
			B = 0;
		}
	}
	return (EXIT_SUCCESS);
}

interrupt void
ISA()
{
	if (IOC3 && GPIF)
	{
		GPIF = 0;
		if (!CS)
		{
			readSPI();
		}
	}
	if (T0IE && T0IF)
	{
		T0IF = 0;
		R = (r > 0);
		G = (g > 0);
		B = (b > 0);
		TMR0 = 0;
	}
}