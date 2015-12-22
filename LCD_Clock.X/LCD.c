/* 
 * File:   LCD.c
 * Author: mark
 *
 * Created on December 21, 2015, 3:18 PM
 */

#include "LCD.h"
#include "stdint.h"

int init()
{
	/* 
	 * Init for both 4- and 8-bit require these steps
	 * 1. Wait 15ms
	 * 2. Write 0x3 to the high nibble (in 4-bit, that's just the four we're using
	 *		in 8-bit, that's the high nibble) and wait 5ms
	 * 3. Write the 0x3 again and wait 160µs
	 * 4. Repeat step 3 (can poll the busy flag, too)
	 */
#ifdef BIT_4
	/*
	 * Init procedure for 4-bit
	 * 5. Write 0x2 to enable 2 bit mode
	 * 
	 */
#else
	
#endif
	
	return 0;
}

char getChar()
{
	char data;
	LCDcommand(1, 1, &data);
	return data;
}

void LCDcommand(char rs, char rw, char* data)
{
#ifdef BIT-4
	
#else
	
#endif
}

void timerWait()
{
	
}