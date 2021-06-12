#include <iostream>
#include "typedefs.hpp"
int CheckColorValidity(const std::string& input, int i, Player players[]) {

	int color_check_flag = 0;
	if (input == "RED" || input == "BLUE" || input == "GREEN" || input == "YELLOW") {
		color_check_flag = 0;
	}
	else {
		color_check_flag = 1;
		cout << input << " cannot be chosen, please choose RED , BLUE, GREEN or YELLOW" << endl;
	}
	if (i != 0) {
		for (int count = 0; count < i; count++) {
			if (input == players[count].colourName) {
				color_check_flag = 1;
				cout << input << " has been picked already, please choose another color" << endl;
				break;
			}
		}
	}
	return color_check_flag;
}
