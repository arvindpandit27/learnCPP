#include <iostream>
using namespace std;

#define NCOINS  4

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
	int Kill_Pos;
};

class Player {
public:
	string name;
	string colourName;
	Colour_t colour = RED;
	Coins Coin[4];
};



