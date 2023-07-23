/*
 * 16x2 LCD Driver
 *
 * Created: 7/21/2022
 * Author: Mohamed Abdulaziz
 */ 


#ifndef _16X2LCD_H_
#define _16X2LCD_H_

//Includes===========================//
#include "../main.h"

//Definitions========================//
//#define _8BIT_MODE
#define _4BIT_MODE

#define lcd_direction DDRC
#define lcd_port	  PORTC
#define RS			  PC0

#ifdef _8BIT_MODE
#define RW			  PC1
#endif

#ifdef _4BIT_MODE
#define EN			  PC1
#define RW			  0
#elif RW
#define EN			  PC2
#endif

//Variables=========================//


//Functions Declrations==============//
//4-Bit mode functions
void lcd_4bit_init(void);
void lcd_4bit_cmnd(unsigned char command);
void lcd_4bit_char(unsigned char data);
void lcd_4bit_gotoxy(uint8_t row, uint8_t column);
void lcd_4bit_str(char *string);
void lcd_4bit_clear();

//8-Bit mode functions 
void lcd_8bit_init(void);
void lcd_8bit_cmnd(unsigned char command);
void lcd_8bit_char(unsigned char data);
void lcd_8bit_gotoxy(uint8_t row, uint8_t column);
void lcd_8bit_str(char *string);
void lcd_8bit_clear();

#endif /* _16X2LCD_H_ */

//============LCD 16x2 Commands==============//

/*
 *	Code (HEX)	  Command to LCD																				Execution Time
 *	0x01	      Clear the display screen																		1.64ms
 *	0x06	      Shift the cursor right (e.g. data gets written in an incrementing order, left to right)		40 us
 *	0x0C		  Display on, cursor off																		40 us
 *	0x0E		  Display on, cursor blinking																	40 us
 *	0x80		  Force the cursor to the beginning of the 1st line												40 us
 *	0xC0		  Force the cursor to the beginning of the 2nd line												40 us
 *	0x10		  Shift cursor position to the left																40 us
 *	0x14		  Shift cursor position to the right															40 us
 *	0x18		  Shift entire display to the left																40 us
 *	0x1C		  Shift entire display to the right																40 us
 *	0x38		  2 lines, 5x8 matrix, 8-bit mode																40 us
 *	0x28		  2 lines, 5x8 matrix,4-bit mode																40 us
 *	0x30		  1 line, 8-bit mode																			40us
 *	0x20		  1 line, 4-bit mode																			40us
 */