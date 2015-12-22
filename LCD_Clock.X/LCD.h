/* 
 * File:   LCD.h
 * Author: mark
 *
 * Created on December 21, 2015, 3:19 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
	
#define XTAL_FREQ 4000000L

#define BIT_4
	
// Big wait gap for init
#define MS_5 ((5*XTAL_FREQ)/1e3)
// Small wait gap for init
#define US_160 ((160*XTAL_FREQ)/1e6)
// Min delay between command writes
#define NS_500 ((500*XTAL_FREQ)/1e9) // At 4MHz, this should be 2

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

