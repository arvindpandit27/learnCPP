#include <iostream>
#include "typedefs.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "CheckUserInputs.hpp"
#include <thread>
#include "BoardGraphics.hpp"
#include "Utils.hpp"

using namespace std::literals::chrono_literals;

char keyboard_input;
int ascii_code;
bool end_game;
int NPlayers;
Player* User;

static bool Finished = false;

int rolldice()
{
	int dice_value;
	char keyboard_input;
	int ascii_code;

	cout << "Press r to roll dice" << endl;
	cin >> keyboard_input;
	ascii_code = (int)keyboard_input;

	if (ascii_code == 82 || ascii_code == 114)
	{
		dice_value = (rand() % 5) + 1;
		if (dice_value == 5)
		{
			dice_value = 8;
		}
	}
	else
	{
		cout << "r wasn't entered" << endl;
		dice_value = 0;
	}
	return dice_value;
}

void GamePlay() {
	int dice_value;
	while (!Finished)
	{
		cout << "CONSOLE UPDATE" << endl;
		std::this_thread::sleep_for(2s);
		//for (int i = 0; i < NPlayers; i++)
		//{
		//	cout << User[i].name << "'s turn" << endl;
		//	do {
		//		dice_value = rolldice();
		//		cout << dice_value << endl;
		//		User[i].Coin[0].x = 1;
		//		User[i].Coin[0].y = 3;
		//		end_game = 0;
		//	} while (dice_value == 4 || dice_value == 8 || dice_value == 0);
		//}
		//if (end_game == 1)
		//{
		//	break;
		//}
	}
}


int main(int argc, char** argv)
{
	int *coptr;
	int coll_arr[3];
	coptr = primeFactors(26);
	cout << coptr << endl;
	cout << (coptr + 1) << endl;
	coll_arr[0] = *coptr;
	coll_arr[1] = *(coptr + 1);
	coll_arr[2] = *coptr;
	cout << coll_arr[0] << endl;
	cout << coll_arr[1] << endl;
	cout << coll_arr[2] << endl;
	//coll_arr[1] = ;

	srand((unsigned)time(0));
	cout << "Enter number of players" << endl;
	cin >> NPlayers;
	Player* User;
	User = new Player[NPlayers];
	//Player User[NPlayers];
	Player PlayerA;
	Coins Coin[4];
	bool end_game;

	

	for (int i = 0; i < NPlayers; i++)
	{
		string name;
		cout << "Enter"
			<< " " << i + 1 << " "
			<< "player's name" << endl;
		cin >> name;
		User[i].name = name;
		cout << "Choose the color RED, BLUE, GREEN OR YELLOW" << endl;
		cout << "Enter"
			<< " " << i + 1 << " "
			<< " player colour" << endl;
		cin >> name;

		while (CheckColorValidity(name, i, User)) {
			cin >> name;
		}
		User[i].colourName = name;
	}

	//thread t1(BoardGraphics);
	//thread t2(GamePlay);

	//t1.join();
	//t2.join();

	return 0;
}
