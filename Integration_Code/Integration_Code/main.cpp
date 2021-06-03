#include <iostream>
#include <thread>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "typedefs.hpp"
#include "CheckUserInputs.hpp"
#include "BoardGraphics.hpp"
#include "UserInput.hpp"
#include "Utils.hpp"


int NPlayers;
Player* User;
int repeat_dice = 0;



extern int Paths[4][25] = { {38,46,58,87,145,203,319,253,209,187,143,91,65,39,26,34,51,85,119,133,161,115,69,57,95},
	{209,187,143,91,65,39,26,34,38,46,58,87,145,203,319,253,161,115,69,57,51,85,119,133,95},
	{65,39,26,34,38,46,58,87,145,203,319,253,209,187,143,91,119,133,161,115,69,57,51,85,95},
	{145,203,319,253,209,187,143,91,65,39,26,34,38,46,58,87,69,57,51,85,119,133,161,115,95} };

int rolldice()
{
	srand((unsigned int)time(NULL));

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
	volatile uint8_t check_user_access = 0;

	board_position = User[player_number].Coin[Selected_Coin].Position;
	for (int n = 0; n < 25; n++) {
		if (board_position == Paths[player_number][n]) {
			current_position_index = n;
			break;
		}
	}

	if (User[player_number].inner_loop_access == ACCESS_GRANTED)
	{
		new_position_index = current_position_index + dice_value;
	}
	else
	{
		new_position_index = current_position_index + dice_value;
		if (new_position_index > WAIT_FOR_ACCESS_INDEX)
		{
			cout << User[player_number].name << " Doesn't have inner loop access" << endl;
			cout << "Please Kill a opponent coin to get inner loop access" << endl;
			new_position_index = current_position_index;
		}
	}

	if (new_position_index > 24) {
		cout << "Cannot Reach Centre" << endl;
	}
	else {
		board_position = Paths[player_number][new_position_index];
		if (board_position != Paths[0][0] && board_position != Paths[1][0] && board_position != Paths[2][0] && board_position != Paths[3][0] && board_position != Paths[0][24]) {
			for (int n = 0; n < NPlayers; n++) {
				//cout << User[n].Coin[Selected_Coin].Position << endl;
				if (n != player_number && board_position == User[n].Coin[Selected_Coin].Position) {
					User[n].Coin[Selected_Coin].Position = Paths[n][0];
					cout << User[n].name << "'s Coin Was Killed" << endl;
					User[n].Coin[Selected_Coin].Position = Paths[n][0];
					int kill_coll_arr[2] = { 0 };
					primeFactors(User[n].Coin[Selected_Coin].Position, kill_coll_arr);
					int kill_index[2] = { 0 };
					findXYinBoard(kill_coll_arr[0], kill_coll_arr[1], kill_index);
					User[n].Coin[Selected_Coin].xPos = kill_index[0];
					User[n].Coin[Selected_Coin].yPos = kill_index[1];
					User[player_number].inner_loop_access = ACCESS_GRANTED;
					check_user_access = User[player_number].inner_loop_access;
					cout << User[player_number].name << "'s inner loop access granted" << endl;
					repeat_dice = 1;
					cout << User[player_number].name << "'s gets another chance for killing opponent" << endl;
				}
			}
		}
		User[player_number].Coin[Selected_Coin].Position = board_position;
	}
	return board_position;
}


void GamePlay() {
	bool Finished = false;
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
				static int l = 0;
				if ((i == 0) && (l == 0))
				{
					dice_value = 1;
					l = 1;
				}
				static int k = 0;
				if ((i == 1) && ((k == 0) || (k == 1)))
				{
					dice_value = 4;
					k = k + 1;
				}
				else if ((i == 1) && (k == 2))
				{
					dice_value = 1;
				}
				selected_coin = CoinSelect();
				cout << dice_value << endl;
				repeat_dice = 0;
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
			} while (dice_value == 4 || dice_value == 8 || dice_value == 0 || repeat_dice == 1);
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
