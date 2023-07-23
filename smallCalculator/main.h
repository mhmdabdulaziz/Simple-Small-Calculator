/*
 * Simple Small Calculator
 *
 * Created: 7/21/2022
 * Author: Mohamed Abdulaziz
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL //MCU Frequency

//Includes===========================//
//Libraries Definitions
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//Files Definitions
#include "16x2LCD/16x2lcd.h"
#include "4x4Keypad/4x4keypad.h"

//Functions Decleration==============//
void read_equation(char* equation);
uint8_t is_operator(char c);
int get_precedence(char c);
int apply_operator(int a, int b, char op);
int evaluate_expression(const char* expression);

#endif /* MAIN_H_ */