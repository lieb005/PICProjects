/* 
 * File:   LC_main.c
 * Author: mark
 *
 * Created on 14. Dezember 2013, 18:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "disp.h"
#include "defs.h"

#ifdef DBG
#pragma config DEBUG =	ON
#pragma config MCLRE =	ON
#pragma config WDT	 =	OFF
#pragma config LVP	 =	ON
#else
#pragma config DEBUG =	OFF
#pragma config MCLRE =	ON
#pragma config WDT	 =	ON
#pragma config LVP	 =	OFF
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
	return (EXIT_SUCCESS);
}

void setup()
{
	GIEH = 1;
	GIEL = 1;
	IPEN = 1;
}

void high_priority interrupt isr_high()
{

}

void low_priority interrupt isr_low()
{

}