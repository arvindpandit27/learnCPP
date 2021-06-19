#include <iostream>
#include "typedefs.hpp"

uint8_t FindColor(int color_ascii_value) {
	if (color_ascii_value == 114 || color_ascii_value == 82) {
		return 0;
	}
	else if (color_ascii_value == 98 || color_ascii_value == 66) {
		return 1;
	}
	else if (color_ascii_value == 103 || color_ascii_value == 71) {
		return 2;
	}
	else if (color_ascii_value == 121 || color_ascii_value == 89) {
		return 3;
	}
	else {
		return 4;
	}

}

int CheckColorValidity(char color_input, int i, Player players[]) {

	int color_check_flag = 0;
	int ASCII_Value = 0;
	uint8_t color_index = 4;

	ASCII_Value = (int)color_input;

	if (i == 0) {
		color_index = FindColor(ASCII_Value);
		if (color_index == 4) {
			color_check_flag = 1;
			cout << color_input << " cannot be chosen, please choose 'r' for RED ,'b' for BLUE,'g' for GREEN or 'y' for YELLOW" << endl;
		}
		else {
			players[i].colour = (Colour_t)color_index;
			color_check_flag = 0;
		}
	}
	else {
		color_index = FindColor(ASCII_Value);
		if (color_index == 4) {
			color_check_flag = 1;
			cout << color_input << " cannot be chosen, please choose 'r' for RED ,'b' for BLUE,'g' for GREEN or 'y' for YELLOW" << endl;
		}
		else {
			players[i].colour = (Colour_t)color_index;
			color_check_flag = 0;
			for (int count = 0; count < i; count++) {
				if (players[i].colour == players[count].colour) {
					color_check_flag = 1;
					cout << color_input << " has been picked already, please choose another color" << endl;
					break;
				}
			}
		}
	}
	return color_check_flag;
}
