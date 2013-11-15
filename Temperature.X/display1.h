/* 
 * File:   display1.h
 * Author: mark
 *
 * Created on 20. Oktober 2013, 10:59
 */

#ifndef DISPLAY1_C
#define	DISPLAY1_C

#ifdef	__cplusplus
extern "C"
{
#endif

#include "defs.h"

#define NEWCHAR
#define OLD_SCH

// Table with memory bit assignment for digits "0" to "9" and characters "A" to "Z"
//   A
// F   B
//   G
// E   C
//   D
const unsigned char lcd_font[] =
{
  SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F,           // Displays "0"
        SEG_B+SEG_C,                             // Displays "1"
  SEG_A+SEG_B+      SEG_D+SEG_E+      SEG_G,     // Displays "2"
  SEG_A+SEG_B+SEG_C+SEG_D+            SEG_G,     // Displays "3"
        SEG_B+SEG_C+            SEG_F+SEG_G,     // Displays "4"
  SEG_A+      SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "5"
#ifndef OLD_SCH
  SEG_A+      SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "6"
#else
	      SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "6" without seg. A
#endif
#ifndef NEW_CHAR
  SEG_A+SEG_B+SEG_C,                             // Displays "7"
#else
  SEG_A+SEG_B+SEG_C            +SEG_F     ,      // Displays "7"
#endif
  SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "8"
#ifndef OLD_SCH
  SEG_A+SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "9"
#else
  SEG_A+SEG_B+SEG_C+	        SEG_F+SEG_G,     // Displays "9" without seg. D
#endif
  0                                        ,     // Displays " " (:)
  0                                        ,     // Displays " " (;)
#ifndef NEW_CHAR
  SEG_A+                        SEG_F+SEG_G,     // Displays "<" as high c
#else
  SEG_A+                  SEG_E+SEG_F      ,     // Displays "<" as old, mirrored 7
#endif
                    SEG_D+            SEG_G,     // Displays "="
#ifndef NEW_CHAR
  0                                        ,     // Displays " " (>)
#else
        SEG_B+SEG_C+SEG_D                  ,     // Displays ">" like mirrored L
#endif
  SEG_A+SEG_B+            SEG_E+      SEG_G,     // Displays "?"
  0                                        ,     // Displays " " (@)
  SEG_A+SEG_B+SEG_C+      SEG_E+SEG_F+SEG_G,     // Displays "A"
              SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "b"
                    SEG_D+SEG_E+      SEG_G,     // Displays "c"
        SEG_B+SEG_C+SEG_D+SEG_E+      SEG_G,     // Displays "d"
  SEG_A+           +SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "E"
  SEG_A+                  SEG_E+SEG_F+SEG_G,     // Displays "f"
#ifndef NEW_CHAR
  SEG_A+SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "g" same as 9
#else
  SEG_A+     +SEG_C+SEG_D+SEG_E+SEG_F      ,     // Displays "G"
#endif
              SEG_C+      SEG_E+SEG_F+SEG_G,     // Displays "h"
                          SEG_E            ,     // Displays "i"
#ifndef NEW_CHAR
  SEG_A+SEG_B+SEG_C+SEG_D                  ,     // Displays "J"
#else
        SEG_B+SEG_C+SEG_D+SEG_E            ,     // Displays "J"
#endif
        	    SEG_D+      SEG_F+SEG_G,     // Displays "k"
                    SEG_D+SEG_E+SEG_F      ,     // Displays "L"
  SEG_A+SEG_B+SEG_C+      SEG_E+SEG_F      ,     // Displays "M"
              SEG_C+      SEG_E+      SEG_G,     // Displays "n"
              SEG_C+SEG_D+SEG_E+      SEG_G,     // Displays "o"
  SEG_A+SEG_B+            SEG_E+SEG_F+SEG_G,     // Displays "P"
  SEG_A+SEG_B+SEG_C+            SEG_F+SEG_G,     // Displays "q"
                          SEG_E+      SEG_G,     // Displays "r"
#ifndef NEW_CHAR
  SEG_A+      SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "S" same as 5
#else
  SEG_A+      SEG_C+SEG_D+      SEG_F      ,     // Displays "S"
#endif
                    SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "t"
              SEG_C+SEG_D+SEG_E            ,     // Displays "u"
#ifndef NEW_CHAR
              SEG_C+SEG_D+SEG_E            ,     // Displays "v" same as u
#else
              SEG_C+SEG_D+SEG_E+SEG_F      ,     // Displays "V"
#endif
        SEG_B+SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "W"
        SEG_B+SEG_C+     +SEG_E+SEG_F+SEG_G,     // Displays "X" as H
        SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "Y"
#ifndef NEW_CHAR
  SEG_A+SEG_B+      SEG_D+SEG_E+      SEG_G,     // Displays "Z" same as 2
#else
  SEG_A+SEG_B+      SEG_D+SEG_E            ,     // Displays "Z"
#endif
};


//extern unsigned char getFontChar(char ch)
uint8_t getFontChar(char ch)
{
	switch (ch)
	{
	case '0' ... 'Z':
		return lcd_font[ch - '0'];
	case 'a' ... 'z':
		return lcd_font[ch - ('0' + ('a' - 'A'))];
	case '-':
		return SEG_G;
	case '.':
	case ',':
		return SEG_DP;
	case '[':
		return SEG_A + SEG_D + SEG_E + SEG_F;
	case ']':
		return SEG_A + SEG_B + SEG_C + SEG_D;
	case '_':
		return SEG_D;
	case '*':
		return SEG_A + SEG_B + SEG_F + SEG_G;
	default:
		return 0;
	}
}

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY1_H */

