#include "buttons.h"
#include "defs.h"
#include "menu.h"
#include "disp.h"
#include "RTC.h"
#include "temp.h"

uint8_t oldLATB = 0;
uint32_t waitCnt[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint32_t waitcnt = 0;

void setupButtons()
{
	LATC = 0;
	LATB = 0;

	// make them all inputs
	TRS = 0b11111111;

	nRBPU = !OFF;
}

void buttons()
{
	waitcnt++;
	//LATA5 = 0;
	LATC2 = 0;
	if (((INV PRT) & BIT0) && ((int32_t) (waitCnt[0] - waitcnt) <= 0))
	{
		waitCnt[0] = waitcnt + WAITCNT;
		LATC2 = advState();
	}
	if (((INV PRT) & BIT1) && ((int32_t) (waitCnt[1] - waitcnt) <= 0))
	{
		waitCnt[1] = waitcnt + WAITCNT;
		screen.brightness++;
		screen.changed |= BRIGHTNESS;
	}
	if (((INV PRT) & BIT2) && ((int32_t) (waitCnt[2] - waitcnt) <= 0))
	{
		waitCnt[2] = waitcnt + WAITCNT;
		advMenu();
	}
	if (((INV PRT) & BIT3) && ((int32_t) (waitCnt[3] - waitcnt) <= 0))
	{
		waitCnt[3] = waitcnt + WAITCNT;
		screen.brightness--;
		screen.changed |= BRIGHTNESS;
	}
	LATC0 = OFF;
	if (((INV PRT) & BIT4) && ((int32_t) (waitCnt[4] - waitcnt) <= 0))
	{
		waitCnt[4] = waitcnt + WAITCNT;
		LATC0 = ON;
	}
	if (((INV PRT) & BIT5) && ((int32_t) (waitCnt[5] - waitcnt) <= 0))
	{
		waitCnt[5] = waitcnt + WAITCNT;
	}
	if (((INV PRT) & BIT6) && ((int32_t) (waitCnt[6] - waitcnt) <= 0))
	{
		waitCnt[6] = waitcnt + WAITCNT;
	}
	if (((INV PRT) & BIT7) && ((int32_t) (waitCnt[7] - waitcnt) <= 0))
	{
		waitCnt[7] = waitcnt + WAITCNT;
	}
	LATC2 = 0;
	if (INV PRT)
	{
		//LATC2 = 1;
		update();
	}
	if (!INV PRT)
	{
		waitCnt[0] = 0;
		waitCnt[1] = 0;
		waitCnt[2] = 0;
		waitCnt[3] = 0;
		waitCnt[4] = 0;
		waitCnt[5] = 0;
		waitCnt[6] = 0;
		waitCnt[7] = 0;
	}
}
