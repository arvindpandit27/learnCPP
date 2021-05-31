#include <iostream>
#include "typedefs.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "CheckUserInputs.hpp"
#include <thread>
#include "BoardGraphics.hpp"
#include "UserInput.hpp"
#include "Utils.hpp"

using namespace std::literals::chrono_literals;

char keyboard_input;
int ascii_code;
int NPlayers;
Player* User;

bool Finished = false;

int Paths[4][25] = { {38,46,58,87,145,203,319,253,209,187,143,91,65,39,26,34,51,85,119,133,161,115,69,57,95},
	{209,187,143,91,65,39,26,34,38,46,58,87,145,203,319,253,161,115,69,57,51,85,119,133,95},
	{65,39,26,34,38,46,58,87,145,203,319,253,209,187,143,91,119,133,161,115,69,57,51,85,95},
	{145,203,319,253,209,187,143,91,65,39,26,34,38,46,58,87,69,57,51,85,119,133,161,115,95} };

int rolldice()
{
	srand(time(NULL));

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

int MoveCoin(int Selected_Coin, int dice_value, int player_number) {
	int current_position_index = 0;
	int new_position_index = 0;
	int board_position = 0;

	board_position = User[player_number].Coin[Selected_Coin].Position;
	for (int n = 0; n < 25; n++) {
		if (board_position == Paths[player_number][n]) {
			current_position_index = n;
			break;
		}
	}

	new_position_index = current_position_index + dice_value;
	if (new_position_index > 24) {
		cout << "Cannot Reach Centre" << endl;
	}
	else {
		board_position = Paths[player_number][new_position_index];
		if (board_position != Paths[0][0] && board_position != Paths[1][0] && board_position != Paths[2][0] && board_position != Paths[3][0]) {
			for (int n = 0; n < NPlayers; n++) {
				//cout << User[n].Coin[Selected_Coin].Position << endl;
				if (n != player_number && board_position == User[n].Coin[Selected_Coin].Position) {
					User[n].Coin[Selected_Coin].Position = Paths[n][0];
					cout << User[n].name << "'s Coin Was Killed" << endl;
				}
			}
		}
		User[player_number].Coin[Selected_Coin].Position = board_position;
	}
	return board_position;
}


void GamePlay() {
	int dice_value;
	int selected_coin;

	// Initialize Coin Positions
	for (int n = 0; n < 4; n++) {
		User[0].Coin[n].Position = Paths[0][0];
		User[1].Coin[n].Position = Paths[1][0];
		User[2].Coin[n].Position = Paths[2][0];
		User[3].Coin[n].Position = Paths[3][0];
		User[0].Coin[n].xPos = 2;
		User[0].Coin[n].yPos = 0;
		User[1].Coin[n].xPos = 2;
		User[1].Coin[n].yPos = 4;
		User[2].Coin[n].xPos = 0;
		User[2].Coin[n].yPos = 2;
		User[3].Coin[n].xPos = 4;
		User[3].Coin[n].yPos = 2;
	}
	while (!Finished)
	{
		for (int i = 0; i < NPlayers; i++)
		{
			cout << User[i].name << "'s turn" << endl;
			do {
				dice_value = rolldice();
				selected_coin = CoinSelect();
				User[i].Coin[selected_coin].Position = MoveCoin(selected_coin, dice_value, i);

				int coll_arr[2] = { 0 };
				primeFactors(User[i].Coin[selected_coin].Position, coll_arr);
				int index[2] = { 0 };
				findXYinBoard(coll_arr[0], coll_arr[1], index);
				User[i].Coin[selected_coin].xPos = index[0];
				User[i].Coin[selected_coin].yPos = index[1];

				if (User[i].Coin[selected_coin].Position == 95) {
					cout << User[i].name << " is the Winner" << endl;
					Finished = true;
					break;
				}
			} while (dice_value == 4 || dice_value == 8 || dice_value == 0);
			if (Finished == true)
				break;
		}
	}
}

int main(int argc, char** argv)
{
	cout << "Enter number of players" << endl;
	cin >> NPlayers;
	User = new Player[NPlayers];

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

	thread t1(BoardGraphics,User,NPlayers);
	thread t2(GamePlay);

	t1.join();
	t2.join();

	return 0;
}
