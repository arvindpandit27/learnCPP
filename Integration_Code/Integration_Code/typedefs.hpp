#include <iostream>
using namespace std;

#define NCOINS  4
#define NO_ACCESS 0
#define ACCESS_GRANTED 1
#define WAIT_FOR_ACCESS_INDEX 15
#define REPEAT 1
#define NO_REPEAT 2
#define NONE 0
#define START 0
#define FINISH 1
#define NO_REQ 0
#define YES_CHANGE 1
#define ROLL_DONE 1


#define MOVE_KILL_COIN 4 //Put this value if computer can kill the coin
#define MOVE_FINISH_COIN 3
#define MOVE_CENTER_COIN 2 //Put this value if computer can make it to center
#define MOVE_JUST_COIN 1 //Put this value if computer doesn't have inner loop access and just make a move
#define NO_MOVE_COIN 0 //If you don't wanna move this coin


typedef enum {
	RED = 0,
	BLUE = 1,
	GREEN = 2,
	YELLOW = 3,
	UNASSIGNED = 4
}Colour_t;

class Coins {
public:
	int Position;
	int xPos;
	int yPos;
	int DrawPosition = 0;
	int SoloCoinFlag = 0;
	uint8_t Finish_flag = START;
	uint8_t Select_Other_Coin = YES_CHANGE;
	uint8_t computer_move_value = 0;
};

class Player {
public:
	string name;
	Colour_t colour = UNASSIGNED;
	Coins Coin[4];
	uint8_t inner_loop_access = NO_ACCESS;
	uint8_t check_to_repat = NONE;
	uint8_t roll_dice_value = 0;
	uint8_t roll_dice_flag = NONE;
};



