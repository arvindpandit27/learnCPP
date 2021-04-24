#include <iostream>
#include "typedefs.hpp"
#include <cmath>


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
	return 0;
}