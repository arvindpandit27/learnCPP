#include <iostream>
using namespace std;

#define NCOINS  4
#define NO_ACCESS 0
#define ACCESS_GRANTED 1
#define WAIT_FOR_ACCESS_INDEX 15
#define REPEAT 1
#define NO_REPEAT 2
#define NONE 0


typedef enum {
	RED = 0,
	BLUE = 1,
	GREEN = 2,
	YELLOW = 3
}Colour_t;

class Coins {
public:
	int Position;
	int xPos;
	int yPos;
	int DrawPosition = 0;
	int SoloCoinFlag = 0;
};

class Player {
public:
	string name;
	string colourName;
	Colour_t colour;
	Coins Coin[4];
	uint8_t inner_loop_access = NO_ACCESS;
	uint8_t check_to_repat = NONE;
};



