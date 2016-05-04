#if 0
/* 
 * File:   main.c
 * Author: mark
 *
 * Created on 30. November 2013, 15:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

// should be ~.5 second phases
#define RESET_TMR1 40000

#pragma config FOSC = INTRCIO
#pragma config MCLRE = ON
#pragma config BOREN = OFF
#pragma config WDTE = OFF
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config CP = OFF
#pragma config CPD = OFF

//void delay_s(float t);

/*
 * 
 */
int main(int argc, char** argv) {
    //CMCON = 0b111;
    //ANSEL = 0x0C;
    //	TRISIO = 0;
    //	GPIO = ~0;

    //	TRISIO0 = TRISIO1 = TRISIO2 = TRISIO4 = TRISIO5 = 0;
    //	GPIO0 = GPIO1 = GPIO2 = GPIO4 = GPIO5 = 1;
    //GP1 = 0;
    //	while(1);
    //
    //	T1CON = 0b00110000;
    //	TMR1 = 0;
    //
    //	GIE = 1;
    //	PEIE = 1;
    //	TMR1IF = 0;
    //	TMR1IE = 1;
    //
    //	TMR1ON = 1;
    //
    //	long i = 500;
    //
    //	while (i--);
    //	while (1)
    //	{
    //		i = 500;
    //		while (i--)
    //		{
    //			GP4 = ~GP4;
    //		}
    //		GP0 = ~GP0;
    //		GP1 = ~GP1;
    //	}

    TRISIO = 0;

    int i = 5000;
    while (1) { // infinite loop

        GPIO = 0b111111;
        while (i--);
        i = 5000;
        //delay_s(.200);

        GPIO = 0;
        while (i--);
        i = 5000;
        //		delay_s(.200);
    }
    return (EXIT_SUCCESS);
}
/*
void delay_s(float t)
{
        unsigned long time = (int)(t * (((float)125000) / (float)65536));
        unsigned int bigCounts = (time >> 8) >> 8;
        unsigned int smallCounts = time & 0xFF;

        TMR1 = 65536 - smallCounts;
        T1CON = 0b00110000;
        TMR1IE = 1;
        TMR1IF = 0;
        TMR1ON = 1;

        while (bigCounts--)
        {
                while (!TMR1IF);
                TMR1ON = 0;
                TMR1 = 0;
                TMR1IF = 0;
                TMR1ON = 1;
        }
}*/
//
//void interrupt isr()
//{
//	//GP1 = ~GP1;
//	if (TMR1IE && TMR1IF)
//	{
//		TMR1ON = 0;
//		TMR1 = RESET_TMR1;
//		TMR1IF = 0;
//		GPIO5 = ~GPIO5;
//		GPIO4 = ~GPIO4;
//		//GPIO0 = 0;
//		//		GPIO1 = 0;
//		//		GPIO = ~GPIO;
//		TMR1ON = 1;
//	}
//	GIE = 1;
//	PEIE = 1;
//}
//



#elif 0



//******************************************************************************
// HARDWARE MAKERS
//
// www.hwmakers.eu
//
//******************************************************************************

#include <xc.h>

#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
//#pragma config IESO = OFF
//#pragma config FCMEN = OFF

#define LED1 GP2
#define LED2 GP1
#define LED3 GP0

volatile char counter1 = 0;
volatile char counter2 = 0;
volatile char counter3 = 0;

void main(void) {
    LED1 = 1;
    LED2 = LED3 = 0;
    PSA = 0;
    PS2 = 1;
    PS1 = 1;
    PS0 = 1;
    T0CS = 0;
    T0SE = 0;
    LED2 = 1;

    T0IE = 1;
    T0IF = 0;
    GIE = 1;

    TRISIO = 0b11001010;

    LED1 = 1;
    LED2 = 1;
    LED3 = 1;

    while (1) {
        if (counter1 == 1) {
            LED1 = 0;
        }
        if (counter1 == 2) {
            LED1 = 1;
        }
        if (counter2 == 1) {
            LED2 = 0;
        }
        if (counter2 == 2) {
            LED2 = 1;
        }
        if (counter3 == 1) {
            LED3 = 0;
        }
        if (counter3 == 2) {
            LED3 = 1;
        }
    }
}

void interrupt timeroverflow() {
    if (T0IF && T0IE) {
        T0IF = 0;
        counter1++;
        counter2++;
        counter3++;
        if (counter1 == 3) {
            counter1 = 1;
        }
        if (counter2 == 6) {
            counter2 = 1;
        }
        if (counter3 == 5) {
            counter3 = 1;
        }
    }
}

#elif 1

#include <xc.h>
#include <stdio.h>

#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config MCLRE = OFF

int main (int argc, char** argv)
{
	GPIO = 0xff;
	ANSEL = 0;
	TRISIO = 0;
	while(1);
}

#endif