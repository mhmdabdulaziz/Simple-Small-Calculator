/*
 * 16x2 LCD Driver
 *
 * Created: 7/21/2022
 * Author: Mohamed Abdulaziz
 */ 

//Includes===========================//
#include "16x2lcd.h"

//Functions Initialization===========//
//4-Bit mode functions
void lcd_4bit_init(void) {
	lcd_direction = 0xFF;   // Make LCD port direction as o/p 
	_delay_ms(20);		    // LCD Power ON delay always >15ms 
		
	lcd_4bit_cmnd(0x33);
	lcd_4bit_cmnd(0x32);	// Send for 4 bit initialization of LCD  
	lcd_4bit_cmnd(0x28);	// 2 line, 5*7 matrix in 4-bit mode 
	lcd_4bit_cmnd(0x0E);	// Display on cursor on
	//lcd_4bit_cmnd(0x0c);	// Display on cursor off
	lcd_4bit_cmnd(0x06);	// Increment cursor (shift cursor to right) 
	lcd_4bit_cmnd(0x01);	// Clear display screen 
}

void lcd_4bit_cmnd(unsigned char command) {
	lcd_port = (lcd_port & 0x0F) | (command & 0xF0); // Sending upper nibble 
	lcd_port &= ~(1 << RS);							 // RS=0, command reg. 
	lcd_port |= (1 << EN);								 // Enable pulse 
	_delay_us(1);
	lcd_port &= ~(1 << EN);
	_delay_us(200);
	lcd_port = (lcd_port & 0x0F) | (command << 4);	 // Sending lower nibble 
	lcd_port |= (1 << EN);
	_delay_us(1);
	lcd_port &= ~(1 << EN);
	_delay_ms(2);
}

void lcd_4bit_char(unsigned char data) {
	lcd_port = (lcd_port & 0x0F) | (data & 0xF0);	 // Sending upper nibble 
	lcd_port |= (1 << RS);						     // RS=1, data reg. 
	lcd_port|= (1 << EN);
	_delay_us(1);
	lcd_port &= ~(1 << EN);
	_delay_us(200);
	lcd_port = (lcd_port & 0x0F) | (data << 4);      // Sending lower nibble 
	lcd_port |= (1 << EN);
	_delay_us(1);
	lcd_port &= ~(1 << EN);
	_delay_ms(2);
}

void lcd_4bit_gotoxy(uint8_t row, uint8_t column) {
	uint8_t offset = (row == 0) ? 0x00 : 0x40;
	lcd_4bit_cmnd(0x80 | (column + offset));
}

void lcd_4bit_str(char *string) {
		int i;
		for(i = 0; string[i] != 0; i++)		// Send each char of string till the NULL 
		{
			lcd_4bit_char(string[i]);
		}
}

void lcd_4bit_clear() {
	lcd_4bit_cmnd(0x01);		// Clear display
	_delay_ms(2);
	lcd_4bit_cmnd(0x80);		// Cursor at home position
}

//8-Bit mode functions
void lcd_8bit_init(void) {
	lcd_direction = 0xFF;	// Make LCD command port direction as o/p 
	_delay_ms(20);			// LCD Power ON delay always >s 

	lcd_8bit_cmnd (0x38);	// Initialization of 16X2 LCD in 8bit mode 
	lcd_8bit_cmnd (0x0C);	// Display ON Cursor OFF 
	lcd_8bit_cmnd (0x06);	// Auto Increment cursor 
	lcd_8bit_cmnd (0x01);	// clear display 
	lcd_8bit_cmnd (0x80);	// cursor at home position 
}

void lcd_8bit_cmnd(unsigned char command) {
	lcd_port= command;
	lcd_port &= ~(1 << RS);	// RS=0 command reg. 
	lcd_port &= ~(1 << RW);	// RW=0 Write operation 
	lcd_port |= (1 << EN);	// Enable pulse 
	_delay_us(1);
	lcd_port &= ~(1 << EN);
	_delay_ms(3);
}

void lcd_8bit_char(unsigned char data) {
	lcd_port = data;
	lcd_port |= (1 << RS);	// RS=1 Data reg. 
	lcd_port &= ~(1 << RW);	// RW=0 write operation 
	lcd_port |= (1 << EN);	// Enable Pulse 
	_delay_us(1);
	lcd_port &= ~(1 << EN);
	_delay_ms(1);
}

void lcd_8bit_gotoxy(uint8_t row, uint8_t column) {
	uint8_t offset = (row == 0) ? 0x00 : 0x40;
	lcd_8bit_cmnd(0x80 | (column + offset));
}

void lcd_8bit_str(char *string) {
	int i;
	for(i = 0; string[i] != 0; i++)  // send each char of string till the NULL 
	{
		lcd_8bit_char(string[i]);	 // call LCD data write 
	}
}

void lcd_8bit_clear() {
	lcd_8bit_cmnd(0x01);		// Clear display 
	_delay_ms(2);
	lcd_8bit_cmnd(0x80);		// Cursor at home position 
}