#include "defs.h"
#include "RTC.h"

#ifdef RTC

#include "disp.h"

void initRTC()
{
	rtcMenu.state = hhmmss;
	rtcMenu.digits = DIG0_6;
	rtcMenu.num_states = DATEVIEWS;
	rtcMenu.printFn = &printRTC;

	date.month = 1;
	date.day = 1;
	date.year = 2013;

	EECON1 = EECFG;
	LATC1 = 1;
	loadTime();
	LATC1 = 0;

	//RTC config
	T1CON = T1C;
	TMR1 = RTC_OFFSET;
	TMR1IE = ON;
	TMR1IF = CLEAR;
	TMR1IP = HIGH;
	TMR1ON = ON;

}

struct sDate loadTime()
{
	struct sDate newDate;
	uint8_t cnt;
	//should be 9
	for (cnt = 1; cnt < 7; cnt++)
	{
		EEADR = EESTARTADDR + cnt;
		RD = 1;
		switch (cnt)
		{
		case minute:
			newDate.minute = EEDATA;
			break;
		case hour:
			newDate.hour = EEDATA;
			break;
		case day:
			newDate.day = EEDATA;
			break;
		case month:
			newDate.month = EEDATA;
			break;
		case year:
			newDate.year = EEDATA;
			break;
		case year + 1:
			newDate.year |= EEDATA << 8;
			break;
		}
	}
	return newDate;
}

void saveTime(struct sDate date)
{
	WREN = 1;
	uint8_t cnt;
	//should be 9
	for (cnt = 1; cnt < 7; cnt++)
	{
		EEADR = EESTARTADDR + cnt;
		switch (cnt)
		{
		case minute:
			EEDATA = date.minute;
			break;
		case hour:
			EEDATA = date.hour;
			break;
		case day:
			EEDATA = date.day;
			break;
		case month:
			EEDATA = date.month;
			break;
		case year:
			EEDATA = date.year;
			break;
		case year + 1:
			EEDATA = date.year;
			break;
		}
		EECON2 = EECON2_1;
		EECON2 = EECON2_2;
		WR = 1;
		while (WR)
		{
			LATC2 = 1;
		}
		LATC2 = 0;
	}
}

uint8_t daysOfMonth(uint8_t month, uint16_t year)
{
	switch (month)
	{
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
	if ((date.dst ^ (1 & DST_NOW)) && date.hour == 1)
	{
		date.dst = !date.dst;
		if (date.dst)
		{
			tick(hour);
		}
		else
		{
			if (date.hour > 0)
			{
				date.hour--;
			}
			else
			{
				date.hour = 0;
				date.day--;
			}
		}
	}
}

uint8_t tick(uint8_t val)
{
	switch (val)
	{
	case second:
		if (++date.second >= 60)
		{
			date.second = 0;
		case minute:
			saveTime(date);
			if (++date.minute >= 60)
			{
				date.minute = 0;
			case hour:
				date.hour++;
				checkDST();
				if (date.hour >= 24)
				{
					date.hour = 0;
				case day:
					if (++date.day >= daysOfMonth(date.month, date.year))
					{
						date.day = 1;
					case month:
						if (++date.month > 12)
						{
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

	switch (month)
	{ // using lots of drop-through!
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

		if ((year % 4) == 0)
		{
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

void* printRTC(uint8_t digits)
{
	char str[12] = "";
	uint8_t cnt;
	bool first = 1;
	for (cnt = rtcMenu.state; cnt != rtcMenu.state && !first; cnt++)
	{
		if (cnt == 0)
		{
			first = false;
		}
		switch (countBits(digits))
		{
		case 8:
			switch (cnt)
			{
			case ddd_hhmm:
				sprintf(&str, "%s %02d.%02d", DOW(date.dow), date.hour, date.minute);
				break;
			case DD_MM_YY:
				sprintf(&str, "%02d %02d %02d", date.day, date.month, date.year % 100);
				break;
			case hhmmss:
				sprintf(&str, "  %02d.%02d.%02d", date.hour, date.minute, date.second);
				break;
			case dd_hhmm:
				sprintf(&str, " %c%c %02d.%02d", DOW(date.dow)[0], DOW(date.dow)[1], date.minute, date.second);
				break;
			case DDMMYY:
				sprintf(&str, "  %02d.%02d.%02d", date.day, date.month, date.year % 100);
				break;
			case hhmm:
				sprintf(&str, "    %02d.%02d", date.hour, date.minute);
				break;
			case DDMM:
				sprintf(&str, "    %02d.%02d", date.day, date.month);
				break;
			}
		case 6 ... 7:
			switch (cnt)
			{
			case hhmmss:
				sprintf(&str, "%02d.%02d.%02d", date.hour, date.minute, date.second);
				break;
			case dd_hhmm:
				sprintf(&str, "%c%c %02d.%02d", DOW(date.dow)[0], DOW(date.dow)[1], date.minute, date.second);
				break;
			case DDMMYY:
				sprintf(&str, "%02d.%02d.%02d", date.day, date.month, date.year % 100);
				break;
			case hhmm:
				sprintf(&str, "  %02d.%02d", date.hour, date.minute);
				break;
			case DDMM:
				sprintf(&str, "  %02d.%02d", date.day, date.month);
				break;
			default:
				continue;
			}
		case 4 ... 5:
			switch (cnt)
			{
			case hhmm:
				sprintf(&str, "%02d.%02d", date.hour, date.minute);
				break;
			case DDMM:
				sprintf(&str, "%02d.%02d", date.day, date.month);
				break;
			default:
				continue;
			}
		case 0 ... 3:
			sprintf(&str, "    ");
			break;
		}
	}
	rtcMenu.state = cnt;
	writeString(digits, &str);
	screen.changed |= digits;
	LATC1 = ~LATC1;
	return NULL;
}

#endif //ifdef RTC