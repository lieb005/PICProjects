#include "menu.h"
#include "defs.h"
#include "RTC.h"
#include "temp.h"

uint8_t advState()
{
	menu->state = (menu->state + 1) % menu->num_states;
	screen.changed |= menu->digits;
	LATC = MASKN(menu->state, 0, 0) | MASKN(menu->state, 1, 1) | MASKN(menu->state, 2, 2)| MASKN(menu->state, 3, 6);
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
	clearScreen();
	screen.changed |= rtcMenu.digits | tempMenu.digits;
	LATA5 = (menu != &tempMenu);
}
