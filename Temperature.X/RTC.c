#include "RTC.h"
#include "defs.h"
#include "temp.h"
#include "disp.h"

void initRTC()
{
	date.view = DD_MM_YY;
	date.month = 1;
	date.day = 1;
	date.year = 2013;

	loadTime();

	//RTC config
	T1CON = T1C;
	TMR1 = RTC_OFFSET;
	TMR1IE = ON;
	TMR1IF = CLEAR;
	TMR1ON = ON;

}

struct sDate loadTime()
{
	struct sDate newDate;
	return newDate;
}

uint8_t daysOfMonth(uint8_t month, uint16_t year)
{
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;

	case 4:
	case 6:
	case 9:
	case 11:
		return 30;

	case 2:
		if (IS_LEAP_YEAR(year))
			return 29;
		else
			return 28;
	}

	return 0;
}

void checkDST()
{
	if ((date.dst ^ (1 & DST_NOW)) && date.hour == 1) {
		date.dst = !date.dst;
		if (date.dst) {
			tick(hour);
		} else {
			if (date.hour > 0) {
				date.hour--;
			} else {
				date.hour = 0;
				date.day--;
			}
		}
	}
}

uint8_t tick(uint8_t val)
{
	switch (val) {
	case second:
		if (++date.second >= 60) {
			date.second = 0;
		case minute:
			if (++date.minute >= 60) {
				date.minute = 0;
			case hour:
				date.hour++;
				checkDST();
				if (date.hour >= 24) {
					date.hour = 0;
				case day:
					if (++date.day >= daysOfMonth(date.month, date.year)) {
						date.day = 1;
					case month:
						if (++date.month > 12) {
							date.month = 1;
						case year:
							++date.year;
						}
					}
				}
			}
		}
	}
	return 0;
}

uint8_t dayOfWeek(uint8_t year, uint8_t month, uint8_t day)
{
	/* Calculate days since 2000-01-01 */
	uint32_t tmp = (year % 200) * 365;
	tmp += (((year % 200) + 3) / 4); // leap days

	switch (month) { // using lots of drop-through!
	case 12:
		tmp += 30; /* for nov */

	case 11:
		tmp += 31; /* for oct */

	case 10:
		tmp += 30; /* for sep */

	case 9:
		tmp += 31; /* for aug */

	case 8:
		tmp += 31; /* for jul */

	case 7:
		tmp += 30; /* for jun */

	case 6:
		tmp += 31; /* for may */

	case 5:
		tmp += 30; /* for apr */

	case 4:
		tmp += 31; /* for mar */

	case 3:
		tmp += 28; /* for feb */

		if ((year % 4) == 0) {
			tmp++;
		}

	case 2:
		tmp += 31; /* for jan */

	case 1:
	default:
		/* do nothing */
		break;
	}

	tmp += day;
	tmp--; /* because day-of-month is 1-based (2000-01-01 is the ZERO day). */

	/* day zero (2000-01-01) was a Saturday. */
	return (uint8_t) ((tmp + 6) % 7);
}

void printRTC(uint8_t digits)
{
	char str[9] = "";
	switch (countBits(digits)) {
	case 0 ... 3:
		return;
	case 4 ... 5:
		switch (date.view) {
		case hhmm:
			sprintf(&str, "%02d.%02d", date.hour, date.minute);
			break;
		}
		writeString(digits, &str);
		break;
	case 6 ... 7:
		switch (date.view) {
		case hhmmss:
			sprintf(&str, "%02d.%02d.%02d", date.hour, date.minute, date.second);
			break;
		case dd_hhmm:
			sprintf(&str, "%c%c %02d.%02d", DOW(date.dow)[0], DOW(date.dow)[1], date.minute, date.second);
			break;
		case DDMMYY:
			sprintf(&str, "%02d.%02d.%02d", date.day, date.month, date.year % 100);
			break;

		}
		writeString(digits, &str);
		break;
	case 8:
		switch (date.view) {
		case ddd_hhmm:
			sprintf(&str, "%s %02d.%02d", DOW(date.dow), date.hour, date.minute);
			break;
		case DD_MM_YY:
			sprintf(&str, "%02d %02d %02d", date.day, date.month, date.year % 100);
			break;

		}
		writeString(digits, &str);
		break;
	}
}
