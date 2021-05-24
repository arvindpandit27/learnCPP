using namespace std;

#define NCOINS  4

void BoardGraphics(void);
void GamePlay();


typedef enum {
	RED = 0,
	BLUE = 1,
	GREEN = 2,
	YELLOW = 3
}Colour_t;

class Coins {
public:
	int x;
	int y;
	string colour;
};

class Player {
public:
	string name;
	string colourName;
	Colour_t colour;
	Coins Coin[4];
};





