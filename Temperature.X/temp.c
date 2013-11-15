#include "defs.h"
#include "temp.h"
#include "disp.h"
#include "RTC.h"

void initTemp()
{
	//AD Config
	/*
	 * 7-6	- unused
	 * 5-2	- choose AN in (0000 = 0, 0001 = 1, ...)
	 * 1	- GO (1 = go, 0 = idle)
	 * 0	- Enable
	 */
	ADCON0 = 0b00000001;
	/*
	 * 7-6	- unused
	 * 5	- neg ref
	 * 4	- pos ref
	 * 3-0	- AN/DIG set (1111 = all DIG, 1110 = AN1, 1101 = AN1 AN2, ...
	 */
	ADCON1 = 0b00001110;
	/*
	 * 7	- justify (1 = right, 0 = left)
	 * 6	- unused
	 * 5-3	- Acquisition time
	 * 2-0	- conversion clock setting
	 */
	// TAQC = 1.29MHz; Aqct = 2 Tad
	// Fosc = 16MHz; AD CS = Fosc/16
	ADCON2 = 0b10001101;
}

double getTemp()
{
	double oldTempsTemp[3];
	uint8_t cnt;
	for (cnt = 3;cnt > 0;cnt--)
	{
		oldTempsTemp[cnt-1] = oldTemps[cnt];
	}
	GO = 1;
	while (GO);
	double temp = C(((double)ADRES) * SCALE - OFFSET);
	double total = temp;
	for (cnt = 0;cnt < 3;cnt++)
	{
		oldTemps[cnt] = oldTempsTemp[cnt];
		total += oldTemps[cnt];
	}
	oldTemps[3] = temp;

	return total/4;
}

void printTemp(uint8_t digits)
{
	uint8_t units = 0;
	units |= lowbit(digits);
	units |= lowbit(digits &= (~lowbit(digits)));
	digits &= ~units;

	writeString(units, (char*) "*C");
	
	writeFloat(digits, getTemp());
}