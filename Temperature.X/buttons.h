/* 
 * File:   buttons.h
 * Author: mark
 *
 * Created on 11. November 2013, 10:32
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#include "defs.h"

#ifdef	__cplusplus
extern "C" {
#endif

	void setupButtons();
	void buttons();

	uint32_t tmr0BigCounts;
#define PRT LATB
#define TRI TRISB


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

