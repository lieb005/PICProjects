#include "defs.h"
#include "RTC.h"

#ifdef RTC

#include "disp.h"

void initRTC()
{
	rtcMenu.digits = DIG0_7;
	rtcMenu.state = ddd_hhmm;
	rtcMenu.num_states = DATEVIEWS;
	rtcMenu.printFn = &printRTC;

	date.month = 1;
	date.day = 1;
	date.year = 2013;
	date.hour = 0;
	date.minute = 0;
	date.second = 0;

	EECON1 = EECFG;
	LATC6 = 1;
	loadTime();
	LATC6 = 0;
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
		uint8_t data = EEDATA;
		switch (cnt)
		{
		case minute:
			if (data >= 60)
				data = 0;
			newDate.minute = data;
			break;
		case hour:
			if (data >= 24)
				data = 0;
			newDate.hour = data;
			break;
		case day:
			if (data >= 31)
				data = 1;
			newDate.day = data;
			break;
		case month:
			if (data >= 12)
				data = 1;
			newDate.month = data;
			break;
		case year:
			if (data >= 21)
				data = 20;
			newDate.year = data;
			break;
		case year + 1:
			if (data >= 100)
				data = 0;
			newDate.year |= data << 8;
			break;
		}
		asm("nop");
	}
	date = newDate;
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
			LATC6 = 1;
		}
		LATC6 = 0;
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
	uint8_t save_t = false;
	uint8_t ret = 0;
	switch (val)
	{
	case second:
		date.second++;
		ret = date.second;
		if (date.second >= 60)
		{
			date.second = 0;
		case minute:
			date.minute++;
			save_t = true;
			ret = date.second;
			if (date.minute >= 60)
			{
				date.minute = 0;
			case hour:
				date.hour++;
				checkDST();
				ret = date.hour;
				if (date.hour >= 24)
				{
					date.hour = 0;
				case day:
					date.day++;
					ret = date.hour;
					if (date.day >= daysOfMonth(date.month, date.year))
					{
						date.day = 1;
					case month:
						date.month++;
						ret = date.hour;
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
	if (save_t)
	{
		saveTime(date);
	}
	return ret;
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

void printRTC(uint8_t digits)
{
	// 8 chars, X decimal points, and \0 at the end
	static char str[BUF_SIZE];
	uint8_t cnt = 0;

	uint8_t bits = countBits(digits);

	uint8_t i;

menu_loop:

	switch (bits)
	{
	case 8:
		switch (rtcMenu.state)
		{
		case ddd_hhmm:
			sprintf(str, "%s %02d.%02d", dow[date.dow], date.hour, date.minute);
			break;
		case DD_MM_YY:
			sprintf(str, "%02d-%02d-%02d", date.day, date.month, date.year % 100);
			break;
		case hhmmss:
			sprintf(str, "  %02d.%02d.%02d", date.hour, date.minute, date.second);
			break;
			/*case dd_hhmm:
				sprintf(str, " %c%c %02d.%02d", DOW(date.dow)[0], DOW(date.dow)[1], date.hour, date.minute);
				break;*/
			/*case DDMMYY:
				sprintf(str, "  %02d.%02d.%02d", date.day, date.month, date.year % 100);
				break;*/
			/*case hhmm:
				sprintf(str, "    %02d.%02d", date.hour, date.minute);
				break;
			case DDMM:
				sprintf(str, "    %02d.%02d", date.day, date.month);
				break;*/
		default:
			i = BUF_SIZE;
			while (--i)
				str[i-1] = '\0';
			break;
		}
		break;
	case 6 ... 7:
		switch (rtcMenu.state)
		{
		case hhmmss:
			sprintf(str, "%02d.%02d.%02d", date.hour, date.minute, date.second);
			break;
		case dd_hhmm:
			sprintf(str, "%c%c %02d.%02d", DOW(date.dow)[0], DOW(date.dow)[1], date.minute, date.second);
			break;
		case DDMMYY:
			sprintf(str, "%02d.%02d.%02d", date.day, date.month, date.year % 100);
			break;
			/*case hhmm:
				sprintf(str, "  %02d.%02d", date.hour, date.minute);
				break;
			case DDMM:
				sprintf(str, "  %02d.%02d", date.day, date.month);
				break;*/
		default:
			i = BUF_SIZE;
			while (--i)
				str[i - 1] = '\0';
			break;
		}
		break;
	case 4 ... 5:
		switch (rtcMenu.state)
		{
		case hhmm:
			sprintf(str, "%02d.%02d", date.hour, date.minute);
			break;
		case DDMM:
			sprintf(str, "%02d.%02d", date.day, date.month);
			break;
		default:
			i = BUF_SIZE;
			while (--i)
				str[i - 1] = '\0';
			break;
		}
		break;
	case 3:
		switch (rtcMenu.state)
		{
		case ddd:
			sprintf(str, "%02d.%02d", date.hour, date.minute);
			break;
		}
		break;
	case 2:
		switch (rtcMenu.state)
		{
		case dd:
			sprintf(str, "%c%c", date.hour, date.minute);
			break;
		default:
			i = BUF_SIZE;
			while (--i)
				str[i - 1] = '\0';
			break;
		}
		break;
	case 0 ... 1:
		sprintf(str, "    ");
		break;
	}
	if (*str == 0)
	{
		cnt++;
		advState();
		if (cnt < DATEVIEWS)
		{
			goto menu_loop;
		}
		else
		{
			sprintf(str, "ERR");
		}
	}

	writeString(digits, str);
	screen.changed |= digits;
}

#endif //ifdef RTC