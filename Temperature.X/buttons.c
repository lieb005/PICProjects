#include "buttons.h"
#include "defs.h"
#include "menu.h"
#include "disp.h"
#include "RTC.h"
#include "temp.h"

void setupButtons()
{
	// make them all inputs
	TRI = 0xFF;
	nRBPU = !OFF;
	/*
	 * 7	- enable
	 * 6	- 8-bit
	 * 5	- ext clock
	 * 4	- tick on high to low edge
	 * 3	- prescale bypass
	 * 2-0	- prescale 1:2^(val+1)
	 */
	tmr0BigCounts = 0;
	T0CON = 0b00000111;
	TMR0 = TMR0_RESET_VAL;
	TMR0IE = ON;
	TMR0IF = CLEAR;
	TMR0ON = ON;
}

void buttons()
{
	uint8_t cnt;
	LATA5 = 0;
	for (cnt = 0; cnt < 8; cnt++) {
		switch (PRT & (1 << cnt)) {
		case 1 << 0:
			menu.state += 1;
			screen.changed |= DIG0_7;
			break;
		case 1 << 1:
			screen.brightness = 0xF;
			screen.changed |= BRIGHTNESS;
			break;
		case 1 << 2:
			menu.state -= 1;
			screen.changed |= DIG0_7;
			break;
		case 1 << 3:
			screen.brightness = 0;
			screen.changed |= BRIGHTNESS;
			break;
		case 1 << 4:
			LATA5 = 1;
			break;
		case 1 << 5:
			LATA5 = 1;
			break;
		case 1 << 6:
			date.view = DATEVIEWS % (date.view + 1);
			screen.changed |= DIG0_7;
			break;
		case 1 << 7:
			if (menu.state) {
				printFn = &printTemp;
			} else {
				printFn = &printRTC;
			}
			break;
		default:
			break;
		}
	}
}
