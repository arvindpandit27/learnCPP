#include <iostream>
#include "typedefs.hpp"
#include <cmath>
#include "windows.h"
#include <cstdlib>
#include <ctime>

int rolldice(){
	int dice_value;
	dice_value = (rand() % 5) + 1;
	if(dice_value == 5){
		dice_value = 8;
	}
	return dice_value;
}

int main() {
	srand((unsigned) time(0));
	int NPlayers;
	cout << "Enter number of players" << endl;
	cin >> NPlayers ;
	Player User[NPlayers];
	Player PlayerA ;
	Coins Coin[4];

	for (int i = 0; i < NPlayers; i++) {
		string name;
		cout << "Enter" << " " <<  i+1 << " " << "player's name" << endl;
		cin >> name;
		User[i].name = name;
		cout << "Choose the color RED, BLUE, GREEN OR YELLOW" << endl;
		cout << "Enter" << " " << i + 1 << " " << " player colour" << endl;
		cin >> name;
		User[i].colourName = name;
	}
	
	User[0].Coin[0].x = 1;

	char keyboard_input;
	int ascii_code;
	cout << "Press r to roll dice" << endl;
	cin >> keyboard_input;
	ascii_code = (int)keyboard_input;
	if(ascii_code == 82 || ascii_code == 114){
		cout << rolldice() << endl;
	}

	return 0;
}



