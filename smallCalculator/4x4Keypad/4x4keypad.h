/*
 * 4X4 Keypad
 *
 * Created: 7/15/2022
 * Author: Mohamed Abdulaziz
 */ 


#ifndef _4X4KEYPAD_H_
#define _4X4KEYPAD_H_

#include "../main.h"

// Keypad Connections
#define KEYPAD_PORT PORTD
#define KEYPAD_PIN PIND
#define KEYPAD_DDR DDRD

// Function Prototypes
void keypad_init();
char keypad_getKey();


#endif /* 4X4KEYPAD_H_ */