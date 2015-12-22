/* 
 * File:   menu.h
 * Author: mark
 *
 * Created on 11. November 2013, 10:45
 */

#ifndef MENU_H
#define	MENU_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "defs.h"
#include "temp_main.h"

#define MENU_SIZE 2

struct sMenu
{
	uint8_t state;
	uint8_t digits;
	uint8_t num_states;
	void (*printFn)(uint8_t digits);
};

struct sMenu* menu;

uint8_t advState();
void advMenu();

#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

