#include "menu.h"
#include "defs.h"
#include "RTC.h"
#include "temp.h"

uint8_t advState()
{
	menu->state = menu->num_states % (menu->state + 1);
	screen.changed |= menu->digits;
	return menu->state;
}

void advMenu()
{
	if (menu == &rtcMenu)
	{
		menu = &tempMenu;
	}
	else if (menu == &tempMenu)
	{
		menu = &rtcMenu;
	}
	screen.changed |= rtcMenu.digits | tempMenu.digits;
	LATA5 = (menu == &tempMenu) ? OFF : ON;
}
