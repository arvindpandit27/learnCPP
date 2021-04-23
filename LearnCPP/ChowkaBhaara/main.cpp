#include <iostream>
#include "typedefs.hpp"
#include <cmath>


int main() {
	int NPlayers;
	cin >> NPlayers ;
	Player Player[NPlayers];

	for (int i = 0; i < NPlayers; i++) {
		string name;
		string colourname;
		cout << "Enter" << " " <<  i+1 << " " << "player's name" << endl;
		cin >> name;
		Player[i].name = name;
		cout << "Choose the color RED, BLUE, GREEN OR YELLOW" << endl;
		cout << "Enter" << " " << i + 1 << " " << " player colour" << endl;
		cin >> name;
		Player[i].colourName = name;
	}
	
	return 0;
}