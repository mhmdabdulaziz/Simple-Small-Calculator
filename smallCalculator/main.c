/*
 * Simple Small Calculator
 *
 * Created: 7/21/2022
 * Author : Mohamed Abdulaziz
 */ 

//Includes===========================//
#include "main.h"	

//Macros=============================//
#define MAX_INPUT_LENGTH 16

//The main program===================//
int main(void)
{
	//Modules Initialization
    lcd_4bit_init();
	keypad_init();
	
	//Welcoming screen 
	lcd_4bit_gotoxy(0, 5);
	lcd_4bit_str("Welcome");
	
	//Wait for one second to start 
	_delay_ms(1000);
	lcd_4bit_clear();
	
	//Variables to store user input and result
	char equation[MAX_INPUT_LENGTH];
	int result = 0;
	char buffer[10];
	
	//Main loop
    while (1) 
    {
		//Cursor at home screen
		lcd_4bit_clear();
		lcd_4bit_gotoxy(0, 0);
		
		// Read the full equation from the user
		read_equation(equation);

		// Evaluate the equation
		result = evaluate_expression(equation);
		
		//Convert the result from (int) to (char*) and store it in buffer variable
		sprintf(buffer, "%d", result);
	
		//Display the result 
		lcd_4bit_gotoxy(1, (MAX_INPUT_LENGTH - strlen(buffer)));
		lcd_4bit_str(buffer);
		
		//Waiting till clear button pressed
		char key = keypad_getKey();
		while(key != '#');
		_delay_ms(100);
		
    }
}

// Function to read the full equation from the keypad
void read_equation(char* equation) {
	// Variables to track the current index and maximum allowed input length
	int current_index = 0;
	const int max_input_length = MAX_INPUT_LENGTH - 1; // Leave space for the null terminator

	// Clear the equation buffer and the LCD
	memset(equation, 0, MAX_INPUT_LENGTH);
	lcd_4bit_clear();

	while (1) {
		// Read the keypad
		char key = keypad_getKey();

		// Check for numerical or operator keys
		if ((key >= '0' && key <= '9') || key == '+' || key == '-' || key == '*' || key == '/' || key == '(' || key == ')') {
			// Append the key to the equation string
			if (current_index < max_input_length) {
				equation[current_index++] = key;
				equation[current_index] = '\0'; // Null-terminate the string
				lcd_4bit_gotoxy(0, 0);
				lcd_4bit_str(equation);
			}
			} else if (key == '=') {
			// If the user presses '=', exit the loop and finish input
			break;
			} else if (key == '#') {
			// If the user presses '#', clear the input and start over
			current_index = 0;
			memset(equation, 0, MAX_INPUT_LENGTH);
			lcd_4bit_clear();
		}

		// You may want to add a small delay here to prevent rapid input processing
		_delay_ms(100);
	}
}

// Function to check if a character is an operator (+, -, *, /)
uint8_t is_operator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get the precedence of an operator
int get_precedence(char c) {
	if (c == '+' || c == '-')
	return 1;
	else if (c == '*' || c == '/')
	return 2;
	return 0;
}

// Function to apply the operator to the operands
int apply_operator(int a, int b, char op) {
	switch (op) {
		case '+':
		return a + b;
		case '-':
		return a - b;
		case '*':
		return a * b;
		case '/':
		if (b != 0)
		return a / b;
		// Handle division by zero error
		return 0;
		default:
		return 0; // Handle invalid operator
	}
}

// Function to evaluate the expression using operator precedence and BODMAS/BIDMAS
int evaluate_expression(const char* expression) {
	int operand_stack[32];
	char operator_stack[32];
	int operand_top = -1;
	int operator_top = -1;

	// Loop through the expression character by character
	for (int i = 0; expression[i] != '\0'; i++) {
		char current_char = expression[i];

		// If the current character is a space, skip it
		if (current_char == ' ')
		continue;

		// If the current character is a digit, extract the whole number
		if (isdigit(current_char)) {
			operand_top++;
			// Convert the substring of digits to an integer using the 'atoi' function
			operand_stack[operand_top] = atoi(&expression[i]);
			// Update the index 'i' to the end of the current number
			while (isdigit(expression[i]))
			i++;
			i--; // To offset the loop's increment, so it doesn't skip the next character
			} else if (is_operator(current_char)) {
			// While there are operators on the top of the stack with higher or equal precedence,
			// apply the operators and operands on the stack
			while (operator_top >= 0 && is_operator(operator_stack[operator_top]) &&
			get_precedence(operator_stack[operator_top]) >= get_precedence(current_char)) {
				int b = operand_stack[operand_top];
				operand_top--;
				int a = operand_stack[operand_top];
				operand_top--;
				char op = operator_stack[operator_top];
				operator_top--;
				// Apply the operator and push the result back to the operand stack
				int result = apply_operator(a, b, op);
				operand_top++;
				operand_stack[operand_top] = result;
			}
			// Push the current operator onto the operator stack
			operator_top++;
			operator_stack[operator_top] = current_char;
			} else if (current_char == '(') {
			// Push the opening parenthesis onto the operator stack
			operator_top++;
			operator_stack[operator_top] = current_char;
			} else if (current_char == ')') {
			// While the top of the operator stack is not an opening parenthesis,
			// apply operators and operands to the result stack
			while (operator_top >= 0 && operator_stack[operator_top] != '(') {
				int b = operand_stack[operand_top];
				operand_top--;
				int a = operand_stack[operand_top];
				operand_top--;
				char op = operator_stack[operator_top];
				operator_top--;
				// Apply the operator and push the result back to the operand stack
				int result = apply_operator(a, b, op);
				operand_top++;
				operand_stack[operand_top] = result;
			}
			// Pop the opening parenthesis from the operator stack
			operator_top--;
		}
	}

	// While there are operators on the top of the operator stack,
	// apply the operators and operands to the result stack
	while (operator_top >= 0) {
		int b = operand_stack[operand_top];
		operand_top--;
		int a = operand_stack[operand_top];
		operand_top--;
		char op = operator_stack[operator_top];
		operator_top--;
		// Apply the operator and push the result back to the operand stack
		int result = apply_operator(a, b, op);
		operand_top++;
		operand_stack[operand_top] = result;
	}

	// The final result will be on the top of the operand stack
	return operand_stack[operand_top];
}
