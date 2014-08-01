/* 
 * File:   LCD.c
 * Author: mark
 *
 * Created on 15. April 2014, 11:57
 */

#include "LCD.h"
#include "defs.h"

void waitUSec(uint32_t time);
void writeData(uint8_t data);

void initLCD()
{
	waitUSec(15000);
	writeData(0x03);

}

void writeData(uint8_t data, bool rs, bool rw)
{
	LCD_RS = rs;
	LCD_RW = rw;
	LCD_D4 = (data << 7) & BIT0;
	LCD_D5 = (data << 6) & BIT0;
	LCD_D6 = (data << 5) & BIT0;
	LCD_D7 = (data << 4) & BIT0;
	CLK_E;

	LCD_D4 = (data << 3) & BIT0;
	LCD_D5 = (data << 2) & BIT0;
	LCD_D6 = (data << 1) & BIT0;
	LCD_D7 = (data << 0) & BIT0;
	CLK_E;

}

void writeLocLCD(uint8_t col, uint8_t line, char* str, uint8_t len)
{
	waitUSec(34);
}

void waitUSec(uint32_t time)
{
	// use internal clock, stopped, 16-bit, prescale = 1:1
	T0CON = 0b00001000;
	time = time * XTAL_FREQ / 1000000;
	uint24_t bigCounts = time / 65536;
	TMR0 = time % 65536;
	TMR0IF = CLEAR;
	TMR0IE = OFF;
	TMR0ON = ON;
	while (bigCounts > 0 && TMR0ON)
	{
		if (TMR0IF)
		{
			TMR0IF = CLEAR;
			TMR0 = 0;
			bigCounts--;
		}
	}
}