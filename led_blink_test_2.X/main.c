/* 
 * File:   main.c
 * Author: mark
 *
 * Created on 25. Februar 2014, 15:32
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF

/*
 * 
 */
int main(int argc, char** argv)
{
	CMCON = 0x07;
	ANSEL = 0;
	TRISIO = 0b001000;
	GPIO = 0;
	while(1)
	{
		GPIO1 = ~GPIO1;		
	}
	return (EXIT_SUCCESS);
}

