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
	int Position; // product prime
	int xPos;
	int yPos;
};

class Player {
public:
	string name = "AP";
	string colourName;
	Colour_t colour = RED;
	Coins Coin[4];
};



