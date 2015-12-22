#include "defs.h"
#include "temp.h"

#ifdef TEMP

#include "disp.h"

float temp = 0;

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
	// Need ~728kHz for TACQ ~ 1.37µs
	//// TAQC = 1.29MHz; Aqct = 2 Tad
	// Fosc = 16MHz; AD CS = Fosc/16
	ADCON2 = 0b10110101;
	TRISA0 = INPUT;

	tempMenu.digits = DIG0_4;
	tempMenu.state = 0;
	tempMenu.num_states = 2;
	tempMenu.printFn = &printTemp;
}

float getTemp()
{
	float oldTempsTemp[3];
	uint8_t cnt;
	for (cnt = 3; cnt > 0; cnt--)
	{
		oldTempsTemp[cnt - 1] = oldTemps[cnt];
	}
	GO = ON;
	while (GO);
	float tmp;

	tmp = OFFSET;
	tmp = (ADRES * VOLTS) / STEPS;
	tmp = ADRES;
	if (tempMenu.state == 0)
	{
		tmp = C(TEMP_REAL);
	}
	else
	{
		tmp = F(TEMP_REAL);
	}
	float total = tmp;
	oldTemps[3] = tmp;
	for (cnt = 0; cnt < 3; cnt++)
	{
		oldTemps[cnt] = oldTempsTemp[cnt];
		total += oldTemps[cnt];
	}

	temp = total / 4;
	return temp;
}

void printTemp(uint8_t digits)
{
	uint8_t units = 0;
	units |= lowbit(digits);
	units |= lowbit(digits & (~lowbit(digits)));
	digits &= ~units;
	if (tempMenu.state == 0)
	{
		writeString(units, (char*) "*C");
	}
	else
	{
		writeString(units, (char*) "*F");
	}
	char str[BUF_SIZE];
	//temp = 35.4;
	uint8_t bits = countBits(digits);
	temp *= POW10(bits - 2);
	temp = (int32_t) temp;
	temp /= POW10(bits - 2);

	sprintf(str, "%*f", bits, temp);
	writeString(digits, str);
}

#endif //endif TEMP