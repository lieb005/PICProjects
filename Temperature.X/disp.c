/* 
 * File:   dinp.c
 * Author: mark
 *
 * Created on 7. Oktober 2013, 01:42
 */

#include "defs.h"
#include "disp.h"
#include "display1.h"

void update()
{
	if (!screen.changed)
	{
		return;
	}
	int8_t cnt;
	for (cnt = 15; cnt >= 0; cnt--)
	{
		switch (1 << cnt & screen.changed)
		{
		case DIG0 ... DIG7:
			writeDigit(1 << cnt, screen.digits.screen[cnt].bits);
			break;
		case DECODE:
			spi(0b1001, screen.decode);
			break;
		case BRIGHTNESS:
			spi(0b1010, screen.brightness);
			break;
		case SCAN:
			spi(0b1011, screen.scan);
			break;
		case TEST:
			spi(0b1111, screen.test);
			break;
		case SHUTDOWN:
			spi(0b1100, !screen.shutdown);
			break;
		default:
			break;
		}
		screen.changed &= ~(1 << cnt);
	}
}

void setBrightness(uint8_t bright)
{
	screen.brightness = bright;
	screen.changed |= BRIGHTNESS;

}

void setTest(bool state)
{
	screen.test = state;
	screen.changed |= TEST;
}

void startDisp()
{

	MOSI_TRIS = OUTPUT;
	SCK_TRIS = OUTPUT;
	CS_TRIS = OUTPUT;
	MISO_TRIS = INPUT;

	// clear screen
	screen.digits.bits[0] = 0;
	screen.digits.bits[1] = 0;
	// set brightness to ~50%
	setBrightness(0b1111);
	// No Decode
	screen.decode = 0;
	// set scan limit to 8 digits
	screen.scan = 0b111;
	// take out of test mode
	setTest(OFF);
	// take out of shutdown
	screen.shutdown = OFF;

	screen.changed = 0xFFFF;
}

void spi(uint8_t addr, uint8_t data)
{
	uint16_t send = (addr << 8) | data;
	CS = OFF;
	MOSI = OFF;
	SCK = OFF;
	int8_t cnt;
	for (cnt = 15; cnt >= 0; cnt--)
	{
		MOSI = 0x1 & (send >> cnt);
		wait(WAIT);
		SCK = ON;
		wait(WAIT);
		SCK = OFF;
		MOSI = OFF;
	}
	CS = ON;
	SCK = OFF;
	MOSI = OFF;
	wait(WAIT);
}

void writeDigit(uint8_t digit, uint8_t segs)
{
	uint8_t dig = (uint8_t) log2(digit);
	screen.digits.screen[dig].bits = segs;

	//cycle segs A-DP
	int8_t cnt;
	for (cnt = 7; cnt >= 0; cnt--)
	{
		// use Seg as Address and digit mask as data
		spi(cnt + 1, rotate(cnt));
	}
}

void writeChar(uint8_t digit, char ch)
{
	uint8_t dig = (uint8_t) log2(digit);
	screen.digits.screen[dig].bits = getFontChar(ch);
	screen.changed |= digit;
}

void writeLong(uint8_t digits, int32_t num)
{


#if 0
	uint8_t bits = countBits(digits);
	int8_t cnt = 0, i = 0;
	num %= maxSize(digits)*10;
	bool first = true;
	bits += 1;
	for (cnt = log2(lowbit(digits)); --bits; cnt++)
	{
		if (0x1 & (digits >> cnt))
		{
			if (first && num < 0)
			{
				writeChar(hibit(digits), '-');
				num *= -1;
				cnt--;
				continue;
			}
			uint8_t print = num % POW10(i + 1) / POW10(i);
			writeChar(1 << cnt, '0' + print);
			//num /= 10;
			first = false;
			i++;
		}
	}
#else
	char str[9] = "00000000";
	sprintf(&str, "%*li", countBits(digits), num);
	writeString(digits, str);
#endif
}

void writeFloat(uint8_t digits, double num)
{
	char str[9] = "";
	uint8_t bits = countBits(digits);
	sprintf(&str, "%.*f", bits, num);

	writeString(digits, str);
}

void writeString(uint8_t digits, char* string)
{
	/*char str[9] = "";
	sprintf(&str, "%-s", string);
	string = str;*/

	int8_t cnt = 0, i = 0;
	uint8_t bits = countBits(digits);

	bits += 1;
	for (cnt = log2(hibit(digits)); --bits; cnt--)
	{
		if (0x1 & (digits >> cnt))
		{
			if (string[i] == '\0')
			{
				break;
			}
			if (string[i] == '.')
			{
				screen.digits.screen[cnt + 1].bits |= SEG_DP;
				screen.changed |= 1 << (cnt + 1);
				bits++;
				i++;
			}
			if (getFontChar(string[i]) || string[i] == ' ')
			{
				writeChar(1 << cnt, string[i]);
			}
			i++;
		}
	}
}

uint8_t rotate(uint8_t seg)
{
	uint8_t ret = 0;
	int8_t cnt;
	for (cnt = 7; cnt >= 0; cnt--)
	{
		ret |= ((screen.digits.screen[cnt].bits >> seg) & 1) << cnt;
	}
	return ret;
}