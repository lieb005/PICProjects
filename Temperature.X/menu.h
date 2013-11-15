/* 
 * File:   menu.h
 * Author: mark
 *
 * Created on 11. November 2013, 10:45
 */

#ifndef MENU_H
#define	MENU_H

#ifdef	__cplusplus
extern "C" {
#endif

	struct sMenu {
		uint8_t state : 1;
	} menu;

	void (*printFn)(uint8_t digits);


#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

