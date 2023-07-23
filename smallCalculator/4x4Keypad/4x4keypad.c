/*
 * 4X4 Keypad
 *
 * Created: 7/15/2022
 * Author: Mohamed Abdulaziz
 */ 

#include "4x4keypad.h"

void keypad_init() {
	KEYPAD_DDR = 0xF0; // Rows as output, columns as input
	KEYPAD_PORT = 0xFF; // Enable internal pull-up resistors
}

char keypad_getKey() {
	char keypad[4][4] = {
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'#', '0', '=', '+'}
	};
	
	unsigned char row, col;
	while (1)
	{
		for (col = 0; col < 4; col++)
		{
			KEYPAD_DDR = (0b00010000 << col); // Set column pin as output, pull others high
			KEYPAD_PORT = (~(0b00010000 << col)); // Drive column pin low, pull others high
			_delay_ms(1); // Delay for keypad pin state stabilization
			
			for (row = 0; row < 4; row++)
			{
				if (!(KEYPAD_PIN & (0b00000001 << row)))
				{
					while (!(KEYPAD_PIN & (0b00000001 << row))); // Wait for key release
					return keypad[row][col]; // Return the key value
				}
			}
		}
	}
}