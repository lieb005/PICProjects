/* 
 * File:   disp.h
 * Author: mark
 *
 * Created on 7. Oktober 2013, 01:42
 */

#ifndef DISP_H
#define	DISP_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "defs.h"

#define DIG0_0 0b00000001
#define DIG0_1 0b00000011
#define DIG0_2 0b00000111
#define DIG0_3 0b00001111
#define DIG0_4 0b00011111
#define DIG0_5 0b00111111
#define DIG0_6 0b01111111
#define DIG0_7 0b11111111

#define DIG1_7 0b11111110
#define DIG2_7 0b11111100
#define DIG3_7 0b11111000
#define DIG4_7 0b11110000
#define DIG5_7 0b11100000
#define DIG6_7 0b11000000
#define DIG7_7 0b10000000

#define DIG0 0b00000001
#define DIG1 0b00000010
#define DIG2 0b00000100
#define DIG3 0b00001000
#define DIG4 0b00010000
#define DIG5 0b00100000
#define DIG6 0b01000000
#define DIG7 0b10000000


#define SEG_A  0b00000001
#define SEG_B  0b00000010
#define SEG_C  0b00000100
#define SEG_D  0b00001000
#define SEG_E  0b00010000
#define SEG_F  0b00100000
#define SEG_G  0b01000000
#define SEG_DP 0b10000000



#define PORT		A
#define MOSI_PIN	1
#define MISO_PIN	2
#define SCK_PIN		3
#define CS_PIN		4

#define MOSI	CAT3(LAT, PORT, MOSI_PIN)
#define MISO	CAT3(LAT, PORT, MISO_PIN)
#define SCK		CAT3(LAT, PORT, SCK_PIN)
#define CS		CAT3(LAT, PORT, CS_PIN)

#define MOSI_TRIS	CAT3(TRIS, PORT, MOSI_PIN)
#define MISO_TRIS	CAT3(TRIS, PORT, MISO_PIN)
#define SCK_TRIS	CAT3(TRIS, PORT, SCK_PIN)
#define CS_TRIS		CAT3(TRIS, PORT, CS_PIN)

#if 0
#define FLOATF(a, b) (floatf[a][b])
#define FLOATG(a) (floatg[a])

static const char* floatf[8][8] = {
	{"%0.0f", "%0.1f", "%0.2f", "%0.3f", "%0.4f", "%0.5f", "%0.6f", "%0.7f"},
	{"%1.0f", "%1.1f", "%1.2f", "%1.3f", "%1.4f", "%1.5f", "%1.6f", "%1.7f"},
	{"%2.0f", "%2.1f", "%2.2f", "%2.3f", "%2.4f", "%2.5f", "%2.6f", "%2.7f"},
	{"%3.0f", "%3.1f", "%3.2f", "%3.3f", "%3.4f", "%3.5f", "%3.6f", "%3.7f"},
	{"%4.0f", "%4.1f", "%4.2f", "%4.3f", "%4.4f", "%4.5f", "%4.6f", "%4.7f"},
	{"%5.0f", "%5.1f", "%5.2f", "%5.3f", "%5.4f", "%5.5f", "%5.6f", "%5.7f"},
	{"%6.0f", "%6.1f", "%6.2f", "%6.3f", "%6.4f", "%6.5f", "%6.6f", "%6.7f"},
	{"%7.0f", "%7.1f", "%7.2f", "%7.3f", "%7.4f", "%7.5f", "%7.6f", "%7.7f"},
};

static const char* floatg[8] = {
	"%1g", "%2g", "%3g", "%4g", "%5g", "%6g", "%7g", "%8g"
};
#endif
void startDisp();

void update();

void spi(uint8_t addr, uint8_t data);

void setBrightness(uint8_t bright);
void setTest(bool state);

void writeDigit(uint8_t digit, uint8_t segs);
void writeChar(uint8_t digit, char num);

void writeLong(uint8_t digits, int32_t num);
void writeFloat(uint8_t digits, float num);
void writeString(uint8_t digits, char* num);

uint8_t rotate(uint8_t seg);

#define DECODE (1 << 9)
#define BRIGHTNESS (1 << 10)
#define SCAN (1 << 11)
#define TEST (1 << 12)
#define SHUTDOWN (1 << 13)

union uDigit
{

	struct digit_segs
	{
		uint8_t seg_a : 1;
		uint8_t seg_b : 1;
		uint8_t seg_c : 1;
		uint8_t seg_d : 1;
		uint8_t seg_e : 1;
		uint8_t seg_f : 1;
		uint8_t seg_g : 1;
		uint8_t seg_dp : 1;
	} segs;
	uint8_t bits;
};

struct sScreen
{

	union uScreen_data
	{
		union uDigit screen[8];

		uint32_t bits[2];

	} digits;
	uint8_t decode : 8;
	uint8_t brightness : 4;
	uint8_t scan : 3;
	uint8_t test : 1;
	uint8_t shutdown : 1;

	// can be DIG0, DIG1, ..., DIG7, DECODE, BRIGHTNESS, SCAN, TEST, SHUTDOWN
	uint16_t changed;
} screen;
#ifdef	__cplusplus
}
#endif

#endif	/* DISP_H */

