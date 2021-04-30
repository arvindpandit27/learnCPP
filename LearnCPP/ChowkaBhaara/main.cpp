#include <iostream>
#include "typedefs.hpp"
#include <cmath>
#include "windows.h"
#include <cstdlib>

int rolldice(){
	int dice_value;
	dice_value = rand() % 5;
	if(dice_value == 5){
		dice_value = 8;
	}
	return dice_value;
}

int main() {
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

	cout << "Left click to roll dice" << endl;
	if( GetAsyncKeyState(VK_LBUTTON) & 0x8000){
		// cout << rolldice() << endl;
		cout << "Left Button Clicked" << endl;
	}

	cout << rolldice() << endl;
	return 0;
}



