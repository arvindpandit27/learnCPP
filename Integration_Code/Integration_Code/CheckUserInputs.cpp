
#include <iostream>
#include "typedefs.hpp"
int CheckColorValidity(const std::string& input, int i, Player players[]) {

	int color_check_flag = 1;
	for (int count = 0; count < i; count++) {
		if (input == players[count].colourName) {
			color_check_flag = 0;
		}
	}
	return color_check_flag;
}
