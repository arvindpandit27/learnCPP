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
#include <random>

int NPlayers;
Player* User;
//#define TEST_CODE

// Stores an array of traceable path which contains prime product indices 

int Paths[4][25] = { {38,46,58,87,145,203,319,253,209,187,143,91,65,39,26,34,51,85,119,133,161,115,69,57,95},	
	{209,187,143,91,65,39,26,34,38,46,58,87,145,203,319,253,161,115,69,57,51,85,119,133,95},
	{65,39,26,34,38,46,58,87,145,203,319,253,209,187,143,91,119,133,161,115,69,57,51,85,95},
	{145,203,319,253,209,187,143,91,65,39,26,34,38,46,58,87,69,57,51,85,119,133,161,115,95} };

int CoinCountInPosition[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int rolldice(void)
{
	// Input: void
	// Output: Dice value from 1 to 8
	// Purpose : Function to return a dice value to move coins
	srand((unsigned int)time(NULL));

	int dice_value;
	char keyboard_input;
	int ascii_code;

	cout << "Press r to roll dice" << endl;
	cin >> keyboard_input;
	ascii_code = (int)keyboard_input;

	if (ascii_code == 82 || ascii_code == 114)
	{
		std::random_device rd; 
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> distrib(1, 50);
		dice_value = distrib(gen);
		if (  (dice_value) >= 1 && (dice_value < 7)  ) 
			dice_value = 1;
		else if ( (dice_value >= 7) & (dice_value < 19) ) 
			dice_value = 2;
		else if (  (dice_value >= 19) & (dice_value < 33)  ) 
			dice_value = 3;
		else if (  (dice_value >= 33) & (dice_value < 41)  ) 
			dice_value = 4;
		else if (  (dice_value >= 41) & (dice_value <= 50) ) 
			dice_value = 8;
	}
	else
	{
		cout << "r wasn't entered" << endl;
		dice_value = 0;
	}
	return dice_value;
}

void AdjustCoinCount() {
	// Purpose : Determine the number of coins in a given position
	int ref_player;
	int ref_coin;
	for (int n = 0; n < sizeof(CoinCountInPosition) / sizeof(CoinCountInPosition[0]); n++) {
		CoinCountInPosition[n] = 0;
		for (int np = 0; np < NPlayers; np++) {
			for (int nc = 0; nc < 4; nc++) {
				if (User[np].Coin[nc].Position == Paths[0][n]) { 
					User[np].Coin[nc].DrawPosition = CoinCountInPosition[n];
					CoinCountInPosition[n]++; 
					ref_player = np;
					ref_coin = nc;
					User[np].Coin[nc].SoloCoinFlag = 0;
				}
			}
		}
		if (CoinCountInPosition[n] == 1) User[ref_player].Coin[ref_coin].SoloCoinFlag = 1;
	}
}

int MoveCoin(int Selected_Coin, int dice_value, int player_number) {
	// Input: Select a coin out of 4 coins, Dice value returned by roll dice, Player
	// Output: Board position after dice roll (in terms of prime product)
	// Purpose: Update position on board of a coin
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
			if ((dice_value == 4) || (dice_value == 8))
			{
				cout << "No use of giving another chance" << endl;
				User[player_number].check_to_repat = NO_REPEAT;
			}

		}
	}

	if (new_position_index > 24) {
		cout << "Cannot Reach Centre" << endl;
		User[player_number].Coin[Selected_Coin].Select_Other_Coin = YES_CHANGE;
	}
	else {
		board_position = Paths[player_number][new_position_index];
		if (board_position != Paths[0][0] && board_position != Paths[1][0] && board_position != Paths[2][0] && board_position != Paths[3][0] && board_position != Paths[0][24]) {
			for (int n = 0; n < NPlayers; n++) 
			{
				for (int k = 0; k < 4; k++)
				{
					//cout << User[n].Coin[Selected_Coin].Position << endl;
					if (n != player_number && board_position == User[n].Coin[k].Position)
					{
						cout << User[n].name << "'s Coin Was Killed" << endl;
						User[n].Coin[k].Position = Paths[n][0];
						int kill_coll_arr[2] = { 0 };
						primeFactors(User[n].Coin[k].Position, kill_coll_arr);
						int kill_index[2] = { 0 };
						findXYinBoard(kill_coll_arr[0], kill_coll_arr[1], kill_index);
						User[n].Coin[k].xPos = kill_index[0];
						User[n].Coin[k].yPos = kill_index[1];
						User[player_number].inner_loop_access = ACCESS_GRANTED;
						check_user_access = User[player_number].inner_loop_access;
						cout << User[player_number].name << "'s inner loop access granted" << endl;
						User[player_number].check_to_repat = REPEAT;
						cout << User[player_number].name << "'s gets another chance for killing opponent" << endl;
					}
				}
			}
		}
		User[player_number].Coin[Selected_Coin].Position = board_position;
		AdjustCoinCount();
	}
	return board_position;
}


void GamePlay(void) {

	// Input: void
	// Output: Get row number and column number
	// Purpose: Function comprising main gameplay and interfaces with board graphics
	bool Finished = false;
	int dice_value;
	int selected_coin;
	static int count_finish = 0;

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
	AdjustCoinCount();

	while (!Finished)
	{
		for (int i = 0; i < NPlayers; i++)
		{
			cout << User[i].name << "'s turn" << endl;
			do {
				dice_value = rolldice();
#ifdef TEST_CODE
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
#endif // TEST_CODE
				cout << dice_value << endl;
				cout << "Select the" << User[i].name << "coin" << endl;
				selected_coin = CoinSelect();
				cin >> selected_coin;
				//repeat_dice = 0;
				User[i].check_to_repat = NONE;
				User[i].Coin[selected_coin].Select_Other_Coin = NO_REQ;
				User[i].Coin[selected_coin].Position = MoveCoin(selected_coin, dice_value, i);
				while (User[i].Coin[selected_coin].Select_Other_Coin == YES_CHANGE)
				{
					cout << "Please select coin other then coin  " << selected_coin << endl;
					cin >> selected_coin;
					User[i].Coin[selected_coin].Select_Other_Coin = NO_REQ;
					User[i].Coin[selected_coin].Position = MoveCoin(selected_coin, dice_value, i);
				}
				int coll_arr[2] = { 0 };
				primeFactors(User[i].Coin[selected_coin].Position, coll_arr);
				int index[2] = { 0 };
				findXYinBoard(coll_arr[0], coll_arr[1], index);
				User[i].Coin[selected_coin].xPos = index[0];
				User[i].Coin[selected_coin].yPos = index[1];

				for (int k = 0; k < 4; k++)
				{
					if (User[i].Coin[k].Position == 95)
					{
						User[i].Coin[k].Finish_flag = FINISH;
						if ((User[i].Coin[0].Finish_flag == FINISH) && (User[i].Coin[1].Finish_flag == FINISH) && (User[i].Coin[2].Finish_flag == FINISH) && (User[i].Coin[3].Finish_flag == FINISH))
						{
							cout << User[i].name << " is the Winner" << endl;
							Finished = true;
							break;
						}
					}
				}
			} while ((((dice_value == 4) || (dice_value == 8)) && (User[i].check_to_repat != NO_REPEAT)) || dice_value == 0 || User[i].check_to_repat == REPEAT);
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
