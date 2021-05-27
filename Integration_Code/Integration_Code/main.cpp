#include <iostream>
#include "typedefs.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "CheckUserInputs.hpp"
#include <thread>
#include "BoardGraphics.hpp"
#include "UserInput.hpp"

using namespace std::literals::chrono_literals;

char keyboard_input;
int ascii_code;
int NPlayers;
Player* User;

static bool Finished = false;

int Paths[4][25] = { {46,58,62,93,155,217,341,319,253,187,143,91,65,39,26,34,51,85,119,161,203,145,87,69,115},
	{253,187,143,91,65,39,26,34,46,58,62,93,155,217,341,319,203,145,87,69,51,85,119,161,115},
	{65,39,26,34,46,58,62,93,155,217,341,319,253,187,143,91,119,161,203,145,87,69,51,85,115},
	{155,217,341,319,253,187,143,91,65,39,26,34,46,58,62,93,87,69,51,85,119,161,203,145,115}};

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

int MoveCoin(int Selected_Coin, int dice_value,int player_number) {
	int current_position_index = 0;
	for (int n = 0; n < 25; n++) {
		if (User[player_number].Coin[Selected_Coin].Position == Paths[player_number][n]) {
			current_position_index = n;
			break;
		}
	}
	if ((current_position_index + dice_value) > 24) {
		cout << "Cannot Reach Centre" << endl;
		return User[player_number].Coin[Selected_Coin].Position;
	}
	else {
		User[player_number].Coin[Selected_Coin].Position = Paths[player_number][current_position_index + dice_value];
		return User[player_number].Coin[Selected_Coin].Position;
	}
}
	

void GamePlay() {
	int dice_value;
	int selected_coin;
	int board_position = 0;

	for (int n = 0; n < 4; n++) {
		User[0].Coin[n].Position = 46;
		User[1].Coin[n].Position = 253;
		User[2].Coin[n].Position = 65;
		User[2].Coin[n].Position = 155;
	}
	while (!Finished)
	{
		for (int i = 0; i < NPlayers; i++)
		{
			cout << User[i].name << "'s turn" << endl;
			do {
				dice_value = rolldice();
				cout << dice_value << endl;
				selected_coin = CoinSelect();
				board_position = MoveCoin(selected_coin, dice_value,i);
				cout << board_position << endl;
				if (board_position == 115) {
					cout << User[i].name << " is the Winner" << endl;
					Finished = true;
					break;
				}
			} while (dice_value == 4 || dice_value == 8 || dice_value == 0);
		}
	}
}

int main(int argc, char** argv)
{
	srand((unsigned)time(0));
	cout << "Enter number of players" << endl;
	cin >> NPlayers;
	User = new Player[NPlayers];
	Player PlayerA;
	Coins Coin[4];

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

	thread t1(BoardGraphics);
	thread t2(GamePlay);

	t1.join();
	t2.join();

	return 0;
}
