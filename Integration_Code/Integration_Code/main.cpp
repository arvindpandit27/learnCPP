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
#include <SFML\Graphics.hpp>

using namespace sf;
int NPlayers = 0;
Player* User;
uint8_t Current_Play_number = 5;
uint8_t Computer_player_enable = 0;
Clock comp_clock;
//#define TEST_CODE

// Stores an array of traceable path which contains prime product indices 

int Paths[4][25] = { {38,46,58,87,145,203,319,253,209,187,143,91,65,39,26,34,51,85,119,133,161,115,69,57,95},
	{209,187,143,91,65,39,26,34,38,46,58,87,145,203,319,253,161,115,69,57,51,85,119,133,95},
	{65,39,26,34,38,46,58,87,145,203,319,253,209,187,143,91,119,133,161,115,69,57,51,85,95},
	{145,203,319,253,209,187,143,91,65,39,26,34,38,46,58,87,69,57,51,85,119,133,161,115,95} };

int CoinCountInPosition[25] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

void init_coin_center_flag()
{
	for (int a = 0; a < 4; a = a + 1)
	{
		for (int b = 0; b < 4; b = b + 1)
		{
			User[a].Coin[b].Select_Other_Coin = YES_CHANGE;
		}
	}
}

int rolldice()
{
	// Input: void
	// Output: Dice value from 1 to 8
	// Purpose : Function to return a dice value to move coins
	srand((unsigned int)time(NULL));
	int dice_value;
	char keyboard_input;
	int ascii_code;

	if ((Current_Play_number == 1) && (Computer_player_enable == 1))
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(1, 50);
		dice_value = distrib(gen);
		if ((dice_value) >= 1 && (dice_value < 7))
			dice_value = 1;
		else if ((dice_value >= 7) & (dice_value < 19))
			dice_value = 2;
		else if ((dice_value >= 19) & (dice_value < 33))
			dice_value = 3;
		else if ((dice_value >= 33) & (dice_value < 41))
			dice_value = 4;
		else if ((dice_value >= 41) & (dice_value <= 50))
			dice_value = 8;
		return dice_value;
	}
	else
	{
		cout << "Press r to roll dice" << endl;
		cin >> keyboard_input;
		ascii_code = (int)keyboard_input;
		if (ascii_code == 82 || ascii_code == 114)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distrib(1, 50);
			dice_value = distrib(gen);
			if ((dice_value) >= 1 && (dice_value < 7))
				dice_value = 1;
			else if ((dice_value >= 7) & (dice_value < 19))
				dice_value = 2;
			else if ((dice_value >= 19) & (dice_value < 33))
				dice_value = 3;
			else if ((dice_value >= 33) & (dice_value < 41))
				dice_value = 4;
			else if ((dice_value >= 41) & (dice_value <= 50))
				dice_value = 8;
		}
		else
		{
			cout << "r wasn't entered" << endl;
			dice_value = 0;
		}
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

int FindIndex(int board_position, int player_number) {
	int ping_index = 0;
	for (int n = 0; n < 25; n++) {
		if (board_position == Paths[player_number][n]) {
			ping_index = n;
			break;
		}
	}
	return ping_index;
}


void computer_move_coin(uint8_t dice_value, int player_number, uint8_t dice_number)
{
	int current_position_index = 0;
	int new_position_index = 0;
	int board_position = 0;
	volatile uint8_t check_comp_access = 0;

	board_position = User[player_number].Coin[dice_number].Position;
	current_position_index = FindIndex(board_position, player_number);

	new_position_index = current_position_index + dice_value;
	//Check if it can kill opponent coin
	board_position = Paths[player_number][new_position_index];

	if (User[player_number].inner_loop_access == ACCESS_GRANTED)
	{
		User[player_number].Coin[dice_number].computer_move_value = MOVE_CENTER_COIN;
	}
	else
	{
		User[player_number].Coin[dice_number].computer_move_value = MOVE_MOVE_COIN;
	}

	if (board_position != Paths[0][0] && board_position != Paths[1][0] && board_position != Paths[2][0] && board_position != Paths[3][0] && board_position != Paths[0][24])
	{
		for (int n = 0; n < NPlayers; n++)
		{
			for (int k = 0; k < 4; k++)
			{
				//cout << User[n].Coin[Selected_Coin].Position << endl;
				if (n != player_number && board_position == User[n].Coin[k].Position)
				{
					User[player_number].Coin[dice_number].computer_move_value = MOVE_KILL_COIN;
				}
			}
		}
	}
}



uint8_t computer_coin_selection(uint8_t dice_output)
{
	static uint8_t max_num = 0, max_num_nc = 0;
	for (int nc = 0; nc < 4; nc++)
	{
		if (User[Current_Play_number].Coin[nc].Select_Other_Coin == YES_CHANGE)
		{
			User[Current_Play_number].Coin[nc].computer_move_value = NO_MOVE_COIN;
		}
		else
		{
			computer_move_coin(dice_output, Current_Play_number, nc);
		}
		if (User[Current_Play_number].Coin[nc].computer_move_value > max_num)
		{
			max_num = User[Current_Play_number].Coin[nc].computer_move_value;
			max_num_nc = nc;
		}
	}
	return max_num_nc;
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
	current_position_index = FindIndex(board_position, player_number);

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

//This function selects which coin out of four coins have access to move based on dice value
void HighlightCoins(int dice_value, int player_number) {
	int current_position_index = 0;
	int new_position_index = 0;
	for (int np = 0; np < NPlayers; np++) {
		for (int nc = 0; nc < 4; nc++) {
			User[np].Coin[nc].Select_Other_Coin = YES_CHANGE;
			if (player_number == np) {
				current_position_index = FindIndex(User[np].Coin[nc].Position, np);
				new_position_index = current_position_index + dice_value;
				if (new_position_index > 24 || (User[np].inner_loop_access == NO_ACCESS && new_position_index > WAIT_FOR_ACCESS_INDEX))
					User[np].Coin[nc].Select_Other_Coin = YES_CHANGE;
				else
					User[np].Coin[nc].Select_Other_Coin = NO_REQ;
			}
		}
	}
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
		for (uint8_t i = 0; i < NPlayers; i++)
		{
			cout << User[i].name << "'s turn" << endl;
			do {
				Current_Play_number = i;
				if ((i == 1) && (Computer_player_enable == 1))
				{
					User[i].roll_dice_flag = NONE;
					dice_value = rolldice();
					User[i].roll_dice_value = dice_value;
					User[i].roll_dice_flag = ROLL_DONE;
					
				}
				else
				{
					User[i].roll_dice_flag = NONE;
					dice_value = rolldice();
					User[i].roll_dice_value = dice_value;
					User[i].roll_dice_flag = ROLL_DONE;
					
				}
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
				HighlightCoins(dice_value, i);

				if (User[i].Coin[0].Select_Other_Coin == YES_CHANGE && User[i].Coin[1].Select_Other_Coin == YES_CHANGE && User[i].Coin[2].Select_Other_Coin == YES_CHANGE && User[i].Coin[3].Select_Other_Coin == YES_CHANGE) {
					cout << "No coin can be moved, switching to next player" << endl; // Inform current player that a move isn't possible
					break; // Switch to next player
				}

				if ((i == 1) && (Computer_player_enable == 1))
				{
					
					while ((comp_clock.getElapsedTime().asSeconds() < 3.0f))
					{
						;	//do nothing
					}
					selected_coin = computer_coin_selection(dice_value);
					
				}
				else
				{
					cout << "Select the" << User[i].name << "coin" << endl;
					selected_coin = CoinSelect();
					cin >> selected_coin;

				}
				comp_clock.restart();
				//repeat_dice = 0;
				User[i].check_to_repat = NONE;
				User[i].Coin[selected_coin].Position = MoveCoin(selected_coin, dice_value, i);
				int coll_arr[2] = { 0 };
				primeFactors(User[i].Coin[selected_coin].Position, coll_arr);
				int index[2] = { 0 };
				findXYinBoard(coll_arr[0], coll_arr[1], index);
				User[i].Coin[selected_coin].xPos = index[0];
				User[i].Coin[selected_coin].yPos = index[1];
				init_coin_center_flag();
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
	while (NPlayers < 1 || NPlayers > 4) {
		cout << "Enter number of players, minimum 1 and maximum 4" << endl;
		cin >> NPlayers;
	}
	if (NPlayers == 1)
	{
		Computer_player_enable = 1;
		NPlayers = 2;
	}

	User = new Player[NPlayers];

	for (int i = 0; i < NPlayers; i++)
	{
		if ((i == 1) && (Computer_player_enable == 1))
		{
			string intel_colour;
			string name_comp = "Intelligence";
			if (User[0].colour == RED)
			{
				User[1].colour = BLUE;
				intel_colour = "BLUE";
			}
			else if (User[0].colour == BLUE)
			{
				User[1].colour = GREEN;
				intel_colour = "GREEN";
			}
			else if (User[0].colour == GREEN)
			{
				User[1].colour = YELLOW;
				intel_colour = "YELLOW";
			}
			else if (User[0].colour == YELLOW)
			{
				User[1].colour = RED;
				intel_colour = "RED";
			}
			cout << "Computer will play against you, and it's name is " << name_comp << endl;
			cout << "Computer's color is " << intel_colour << endl;
		}
		else
		{
			string name;
			char color_input;
			cout << "Enter"
				<< " " << i + 1 << " "
				<< "player's name" << endl;
			cin >> name;
			User[i].name = name;
			cout << "Enter 'r' for RED, 'b' for BLUE, 'g' for GREEN OR 'y' for YELLOW" << endl;
			cout << "Enter"
				<< " " << i + 1 << " "
				<< " player colour" << endl;
			cin >> color_input;

			while (CheckColorValidity(color_input, i, User) == 1) {
				cin >> color_input;
			}
		}
	}

	
	//RenderWindow window(VideoMode(800, 800), "Dice Sheet");
	//RectangleShape player(Vector2f(500.0f, 500.0f));
	//player.setPosition(206.0f, 206.0f);
	//Texture playerTexture; 
	//playerTexture.loadFromFile("tux_from_linux.png");
	//player.setTexture(&playerTexture);

	//while (window.isOpen())
	//{
	//	Event event; 
	//	while (window.pollEvent(event));
	//	{
	//		switch (event.type)
	//		{
	//		case :: Event ::Closed:
	//			window.close();
	//			break;
	//		}
	//	}
	//	window.clear();
	//	window.draw(player);
	//	window.display();
	//}
	thread t1(BoardGraphics, User, NPlayers);
	thread t2(GamePlay);

	t1.join();
	t2.join();

	return 0;
}
