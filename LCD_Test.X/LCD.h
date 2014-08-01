/* 
 * File:   LCD.h
 * Author: mark
 *
 * Created on 15. April 2014, 11:57
 */

#ifndef LCD_H
#define	LCD_H

#include "defs.h"

#ifdef	__cplusplus
extern "C"
{
#endif

#define XTAL_FREQ 16000000L

#define LCD_PORT B
#define TRISLCD CAT2(TRIS,LCD_PORT)
#define LATLCD CAT2(LAT,LCD_PORT)
#define LCDPIN(a) CAT3(LAT,LCD_PORT,#a)

#define LCD_RS LCDPIN(0)
#define LCD_RW LCDPIN(1)
#define LCD_E  LCDPIN(2)
#define LCD_D4 LCDPIN(3)
#define LCD_D5 LCDPIN(4)
#define LCD_D6 LCDPIN(5)
#define LCD_D7 LCDPIN(6)

#define CLK_E LCD_E=0;waitUSec(160);LCD_E=1;waitUSec(160);LCD_E=0;

union ulcdData
{
	char wholeLCD[16][2];

	struct slcdlines
	{
		char line1[16];
		char line2[16];
	} lineLCD;
};

union ulcdData lcdBuffer;
union ulcdData lcdCurrent;

void writeWholeLCD(char[16][2]);
void writeLocLCD(uint8_t col, uint8_t line, char* str, uint8_t len);
char** readWholeLCD();
char* readLocLCD(uint8_t col, uint8_t line, uint8_t len);
// Writes a byte and returns the next byte
uint8_t writeData(uint8_t data, bool rs, bool rw);

// returns the difference between the characters in the LCD and the buffer
uint8_t** updateLCD();
uint8_t** updateLocLCD(uint8_t col, uint8_t line, uint8_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

