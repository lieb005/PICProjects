/* 
 * File:   RTC.h
 * Author: mark
 *
 * Created on 10. November 2013, 20:05
 */

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "defs.h"
#include "menu.h"
#include "disp.h"
#include "temp_main.h"

//TMR1
/*
 * 7	- Read 16 bit result
 * 6	- using T1OSC
 * 5-4	- prescale 1:2^val (00 = 1:1, 01 = 1:2, ...)
 * 3	- T1OSC Enable
 * 2	- Async with ext clock
 * 1	- Ext clock
 * 0	- on/off
 */

#if 0
// doesn't work, needs 32.768kHz Crystal
//runs at 512kHz (4.096MHz/prescale)
//512000Hz
// 3; 59392
#define RTC_OFFSET	(65536-53248)
#define RTC_TICKS	7
#define T1C 0b11111110
#else
//runs at 500kHz (16MHz/4/prescale)
//500.000Hz
//15; 16960
#define RTC_OFFSET	(65536-16960)
#define RTC_TICKS	(15+1)
//#define RTC_OFFSET	(65536-63765)
//#define RTC_TICKS	(1+1)
#define T1C 0b10110000

#endif

/*
 * 7	- Flash (or EEPROM)
 * 6	- Read/write Config Registers
 * 4	- Flash Row Erase Enable (FREE)
 * 3	- WRite ERRor
 * 2	- WRite ENable
 * 1	- WRite
 * 0	- ReaD
 */
#define EECFG	0b0000000
// used for write
#define EECON2_1 0x55
#define EECON2_2 0xAA
	
#define EESTARTADDR	0

#define IS_LEAP_YEAR(Y) (((Y)%4 == 0) && (((Y)%100 != 0) || ((Y)%400 == 0)))

/* compute number of leap years since BASE_YEAR */
#define BASE_YEAR 1984 /* not a leap year, so no need to add 1 */
#define LEAPS_SINCE_YEAR(Y) (((Y) - BASE_YEAR) + ((Y) - BASE_YEAR) / 4);

/* "private" defines */
#define N_SUN_OF_MON(n,mon,year) (((n)*7)-dayOfWeek((year),(mon),((n)*7)))
#define LAST_SUN_OF_MON(mon,days,year) ((days)-dayOfWeek((year),(mon),(days)))
#define DSTNUM(x,y,z) (((uint16_t)(x)*1000)+(uint16_t)(y*10)+(uint16_t)(z))
#define IN_DST(day, mon, year) ()

// DST in US/Canada: 2nd Sun in Mar to 1st Sun in Nov.

#define DST_START_MO		3
#define DST_START_DAY(year)	(N_SUN_OF_MON(2, 3, year))
#define DST_END_MO			11
#define DST_END_DAY(year)	(N_SUN_OF_MON(1, 11, year))
#define DST_NOW				((date.day >= DST_START_DAY(date.year) && date.month >= DST_START_MO) && \
								(date.day < DST_END_DAY(date.year) && date.month < DST_END_MO))

#define DOW(a) (dow[a])

enum inc
{
	second = 0,
	minute,
	hour,
	day,
	month,
	year
};


enum views
{
	//Times
	hhmm = 0,
	hhmmss,
	ddd_hhmm,
	dd_hhmm,
	//Dates
	dd,
	ddd,
	DDMM,
	DD_MM,
	DDMMYY,
	DD_MM_YY
};

#define DATEVIEWS	10

struct sDate
{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	// day is 1-31, check if it passes 31 (>=32)
	uint8_t day;
	// day of week (0 = sn)
	uint8_t dow;
	// 1-12
	uint8_t month;
	uint16_t year;
	//1 = dst, 0 = regular
	uint8_t dst;
} date;

uint16_t rtc_big_ticks;
uint16_t rtc_small_ticks;

const char dow[7][4] = {
	"Son", "Mon", "Dei", "Mit", "Don", "Fri", "Sam"
};

struct sMenu rtcMenu;

void initRTC();
uint8_t dayOfWeek(uint8_t yr, uint8_t mo, uint8_t dy);
uint8_t daysOfMonth(uint8_t month, uint16_t year);
uint8_t tick(uint8_t val);
void checkDST();
void* printRTC(uint8_t digits);
struct sDate loadTime();
void saveTime(struct sDate date);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

